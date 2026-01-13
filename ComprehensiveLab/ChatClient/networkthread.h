#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>

class NetworkThread : public QObject
{
    Q_OBJECT
public:
    explicit NetworkThread(QObject *parent = nullptr);
    ~NetworkThread();

    void connectToServer(const QString &address, quint16 port);
    void disconnectFromServer();
    void sendMessage(const QJsonObject &message);
    void sendHeartbeat();

    bool isConnected() const;
    QString connectionState() const;

    void startWorker();
    void stopWorker();

signals:
    void connected();
    void disconnected();
    void connectionError(const QString &error);
    void messageReceived(const QJsonObject &message);
    void heartbeatTimeout();
    void reconnectionAttempt(int attempt);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError error);
    void onHeartbeatTimeout();
    void onReconnectionTimeout();
    void processSendQueue();

private:
    QString m_serverAddress;
    quint16 m_serverPort;
    QTcpSocket *m_socket;
    QTimer *m_heartbeatTimer;
    QTimer *m_reconnectTimer;
    QTimer *m_processTimer;
    
    QQueue<QJsonObject> m_sendQueue;
    QMutex m_queueMutex;
    QWaitCondition m_queueCondition;

    bool m_shouldStop;
    bool m_isConnected;
    int m_reconnectAttempts;
    int m_maxReconnectAttempts;
    int m_reconnectInterval;

    QDataStream *m_stream;
    QThread *m_workerThread;

    void handleReconnection();
    void resetConnection();
    QString socketErrorToString(QAbstractSocket::SocketError error) const;
};

#endif // NETWORKTHREAD_H