#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QVector>
#include "serverworker.h"

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QVector<ServerWorker*> m_clients;

signals:
    void logMessage(const QString &msg); // 日志信号

public slots:
    void jsonReceived(ServerWorker *sender, const QJsonObject &docObj);
    void userDisconnected(ServerWorker *sender);
    void broadcast(const QJsonObject &message, ServerWorker *exclude = nullptr);
};

#endif // CHATSERVER_H
