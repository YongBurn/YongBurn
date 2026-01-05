#include "serverworker.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

ServerWorker::ServerWorker(QObject *parent)
    : QObject(parent)
{
}

bool ServerWorker::setSocketDescriptor(qintptr socketDescriptor)
{
    m_socket = new QTcpSocket(this);
    if (!m_socket->setSocketDescriptor(socketDescriptor)) {
        emit logMessage("套接字描述符设置失败");
        return false;
    }
    connect(m_socket, &QTcpSocket::readyRead, this, &ServerWorker::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &ServerWorker::onDisconnected);
    emit logMessage("套接字描述符设置成功");
    return true;
}

void ServerWorker::onReadyRead()
{
    m_buffer += m_socket->readAll();
    int pos;
    while ((pos = m_buffer.indexOf('\n')) != -1) {
        QByteArray line = m_buffer.left(pos);
        m_buffer = m_buffer.mid(pos + 1);

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(line, &error);
        if (error.error == QJsonParseError::NoError && doc.isObject()) {
            emit jsonReceived(this, doc.object());
        }
    }
}

void ServerWorker::onDisconnected()
{
    emit disconnectedFromClient();
    emit logMessage("客户端断开连接");
}

// 补充sendJson实现
void ServerWorker::sendJson(const QJsonObject &json)
{
    if (m_socket && m_socket->state() == QTcpSocket::ConnectedState) {
        QByteArray data = QJsonDocument(json).toJson(QJsonDocument::Compact) + '\n';
        m_socket->write(data);
    }
}
