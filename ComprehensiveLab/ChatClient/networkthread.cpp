#include "networkthread.h"
#include <QDebug>
#include <QHostAddress>

NetworkThread::NetworkThread(QObject *parent)
    : QObject(parent)
    , m_socket(nullptr)
    , m_heartbeatTimer(nullptr)
    , m_reconnectTimer(nullptr)
    , m_processTimer(nullptr)
    , m_shouldStop(false)
    , m_isConnected(false)
    , m_reconnectAttempts(0)
    , m_maxReconnectAttempts(5)
    , m_reconnectInterval(3000) // 3秒
    , m_stream(nullptr)
    , m_workerThread(nullptr)
{
}

NetworkThread::~NetworkThread()
{
    stopWorker();
}

void NetworkThread::startWorker()
{
    if (m_workerThread) return;
    
    m_workerThread = new QThread(this);
    connect(m_workerThread, &QThread::started, this, &NetworkThread::processSendQueue);
    connect(m_workerThread, &QThread::finished, this, &QObject::deleteLater);
    
    // 创建工作线程中的对象
    m_workerThread->start();
}

void NetworkThread::stopWorker()
{
    m_shouldStop = true;
    
    if (m_reconnectTimer) {
        QMetaObject::invokeMethod(m_reconnectTimer, "stop", Qt::QueuedConnection);
    }
    if (m_heartbeatTimer) {
        QMetaObject::invokeMethod(m_heartbeatTimer, "stop", Qt::QueuedConnection);
    }
    if (m_processTimer) {
        QMetaObject::invokeMethod(m_processTimer, "stop", Qt::QueuedConnection);
    }
    
    if (m_socket) {
        // 直接调用disconnectFromHost，不需要invokeMethod
        m_socket->disconnectFromHost();
    }
    
    m_queueCondition.wakeAll();
    
    if (m_workerThread) {
        m_workerThread->quit();
        m_workerThread->wait();
        m_workerThread->deleteLater();
        m_workerThread = nullptr;
    }
}

void NetworkThread::connectToServer(const QString &address, quint16 port)
{
    QMutexLocker locker(&m_queueMutex);
    m_serverAddress = address;
    m_serverPort = port;
    m_reconnectAttempts = 0;
    m_shouldStop = false;
    
    // 确保工作线程已启动
    if (!m_workerThread) {
        startWorker();
    }
    
    // 在主线程中创建socket和定时器
    if (!m_socket) {
        m_socket = new QTcpSocket(this);  // 使用this作为父对象，属于主线程
        connect(m_socket, &QTcpSocket::connected, this, &NetworkThread::onConnected);
        connect(m_socket, &QTcpSocket::disconnected, this, &NetworkThread::onDisconnected);
        connect(m_socket, &QTcpSocket::readyRead, this, &NetworkThread::onReadyRead);
        connect(m_socket, &QTcpSocket::errorOccurred, this, &NetworkThread::onError);
    }
    
    if (!m_heartbeatTimer) {
        m_heartbeatTimer = new QTimer(this);
        m_heartbeatTimer->setInterval(30000); // 30秒心跳
        m_heartbeatTimer->setSingleShot(false);
        connect(m_heartbeatTimer, &QTimer::timeout, this, &NetworkThread::onHeartbeatTimeout);
    }
    
    if (!m_reconnectTimer) {
        m_reconnectTimer = new QTimer(this);
        m_reconnectTimer->setInterval(m_reconnectInterval);
        m_reconnectTimer->setSingleShot(true);
        connect(m_reconnectTimer, &QTimer::timeout, this, &NetworkThread::onReconnectionTimeout);
    }
    
    if (!m_processTimer) {
        m_processTimer = new QTimer(this);
        m_processTimer->setInterval(100); // 100ms处理间隔
        m_processTimer->setSingleShot(false);
        connect(m_processTimer, &QTimer::timeout, this, &NetworkThread::processSendQueue);
    }
    
    // 延迟连接，确保事件循环已启动
    QMetaObject::invokeMethod(this, [this]() {
        if (m_socket && m_socket->state() != QAbstractSocket::ConnectedState && 
            m_socket->state() != QAbstractSocket::ConnectingState) {
            m_socket->connectToHost(m_serverAddress, m_serverPort);
        }
    }, Qt::QueuedConnection);
}

void NetworkThread::disconnectFromServer()
{
    m_shouldStop = true;
    m_queueCondition.wakeAll();
    
    QMetaObject::invokeMethod(this, [this]() {
        if (m_socket) {
            m_socket->disconnectFromHost();
        }
        if (m_heartbeatTimer) {
            m_heartbeatTimer->stop();
        }
        if (m_reconnectTimer) {
            m_reconnectTimer->stop();
        }
        if (m_processTimer) {
            m_processTimer->stop();
        }
    }, Qt::QueuedConnection);
}

void NetworkThread::sendMessage(const QJsonObject &message)
{
    QMutexLocker locker(&m_queueMutex);
    m_sendQueue.enqueue(message);
    m_queueCondition.wakeOne();
}

void NetworkThread::sendHeartbeat()
{
    QJsonObject heartbeat;
    heartbeat["type"] = "heartbeat";
    heartbeat["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    sendMessage(heartbeat);
}

bool NetworkThread::isConnected() const
{
    return m_isConnected;
}

QString NetworkThread::connectionState() const
{
    if (m_isConnected) {
        return "已连接";
    } else if (m_reconnectAttempts > 0) {
        return QString("重连中(%1/%2)").arg(m_reconnectAttempts).arg(m_maxReconnectAttempts);
    } else {
        return "未连接";
    }
}

void NetworkThread::onConnected()
{
    qDebug() << "NetworkThread: Connected to server";
    m_isConnected = true;
    m_reconnectAttempts = 0;
    
    if (m_heartbeatTimer) {
        m_heartbeatTimer->start();
    }
    if (m_processTimer) {
        m_processTimer->start();
    }
    
    emit connected();
}

void NetworkThread::onDisconnected()
{
    qDebug() << "NetworkThread: Disconnected from server";
    m_isConnected = false;
    
    if (m_heartbeatTimer) {
        m_heartbeatTimer->stop();
    }
    if (m_processTimer) {
        m_processTimer->stop();
    }
    
    emit disconnected();
    
    // 如果不是主动断开，开始重连
    if (!m_shouldStop && m_reconnectAttempts < m_maxReconnectAttempts) {
        handleReconnection();
    }
}

void NetworkThread::onReadyRead()
{
    if (!m_socket) return;
    
    while (m_socket->bytesAvailable() > 0) {
        QByteArray jsonData;
        if (!m_stream) {
            m_stream = new QDataStream(m_socket);
            m_stream->setVersion(QDataStream::Qt_6_5);
        }
        
        *m_stream >> jsonData;
        
        QJsonParseError parseError;
        const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
        
        if (parseError.error == QJsonParseError::NoError && jsonDoc.isObject()) {
            QJsonObject message = jsonDoc.object();
            
            // 处理心跳响应
            if (message["type"].toString() == "heartbeat") {
                qDebug() << "Heartbeat response received";
                continue;
            }
            
            emit messageReceived(message);
        } else {
            qWarning() << "JSON parse error:" << parseError.errorString();
        }
    }
}

void NetworkThread::onError(QAbstractSocket::SocketError error)
{
    QString errorStr = socketErrorToString(error);
    qWarning() << "NetworkThread: Socket error:" << errorStr;
    emit connectionError(errorStr);
    
    if (!m_shouldStop && m_reconnectAttempts < m_maxReconnectAttempts) {
        handleReconnection();
    }
}

void NetworkThread::onHeartbeatTimeout()
{
    if (m_isConnected) {
        sendHeartbeat();
    }
}

void NetworkThread::onReconnectionTimeout()
{
    if (!m_shouldStop && m_reconnectAttempts < m_maxReconnectAttempts) {
        m_reconnectAttempts++;
        emit reconnectionAttempt(m_reconnectAttempts);
        
        if (m_socket && m_socket->state() != QAbstractSocket::ConnectedState && 
            m_socket->state() != QAbstractSocket::ConnectingState) {
            m_socket->connectToHost(m_serverAddress, m_serverPort);
        }
    }
}

void NetworkThread::processSendQueue()
{
    QMutexLocker locker(&m_queueMutex);
    
    while (!m_sendQueue.isEmpty() && m_isConnected) {
        QJsonObject message = m_sendQueue.dequeue();
        
        if (m_socket && m_socket->state() == QAbstractSocket::ConnectedState) {
            QByteArray jsonData = QJsonDocument(message).toJson(QJsonDocument::Compact);
            
            if (!m_stream) {
                m_stream = new QDataStream(m_socket);
                m_stream->setVersion(QDataStream::Qt_6_5);
            }
            
            *m_stream << jsonData;
            
            if (!m_socket->waitForBytesWritten(1000)) {
                qWarning() << "Failed to send message";
                m_sendQueue.prepend(message); // 重新加入队列
                break;
            }
        } else {
            m_sendQueue.prepend(message); // 重新加入队列
            break;
        }
    }
}

void NetworkThread::handleReconnection()
{
    if (m_reconnectTimer && !m_reconnectTimer->isActive()) {
        qDebug() << "Starting reconnection attempt" << m_reconnectAttempts + 1;
        m_reconnectTimer->start();
    }
}

QString NetworkThread::socketErrorToString(QAbstractSocket::SocketError error) const
{
    switch (error) {
    case QAbstractSocket::ConnectionRefusedError:
        return "连接被拒绝";
    case QAbstractSocket::RemoteHostClosedError:
        return "远程主机关闭了连接";
    case QAbstractSocket::HostNotFoundError:
        return "主机未找到";
    case QAbstractSocket::SocketAccessError:
        return "套接字访问错误";
    case QAbstractSocket::SocketResourceError:
        return "套接字资源错误";
    case QAbstractSocket::SocketTimeoutError:
        return "连接超时";
    case QAbstractSocket::DatagramTooLargeError:
        return "数据报太大";
    case QAbstractSocket::NetworkError:
        return "网络错误";
    case QAbstractSocket::AddressInUseError:
        return "地址正在使用";
    case QAbstractSocket::SocketAddressNotAvailableError:
        return "套接字地址不可用";
    case QAbstractSocket::UnsupportedSocketOperationError:
        return "不支持的套接字操作";
    case QAbstractSocket::UnfinishedSocketOperationError:
        return "未完成的套接字操作";
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        return "代理需要认证";
    case QAbstractSocket::SslHandshakeFailedError:
        return "SSL握手失败";
    case QAbstractSocket::ProxyConnectionRefusedError:
        return "代理连接被拒绝";
    case QAbstractSocket::ProxyConnectionClosedError:
        return "代理连接已关闭";
    case QAbstractSocket::ProxyConnectionTimeoutError:
        return "代理连接超时";
    case QAbstractSocket::ProxyNotFoundError:
        return "代理未找到";
    case QAbstractSocket::ProxyProtocolError:
        return "代理协议错误";
    case QAbstractSocket::OperationError:
        return "操作错误";
    default:
        return "未知错误";
    }
}