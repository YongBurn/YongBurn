#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QObject>
#include <QTimer>
#include "serverworker.h"

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
    QVector<ServerWorker*>m_clients;

    void broadcast(const QJsonObject &message,ServerWorker *exclude);

private:
    void sendPrivateMessage(const QJsonObject &message, ServerWorker *sender);
    void checkHeartbeat();
    
    // 联系人相关功能
    void handleAddContactRequest(const QJsonObject &docObj, ServerWorker *sender);
    void handleAddContactResponse(const QJsonObject &docObj, ServerWorker *sender);
    bool extractContactRequestFields(const QJsonObject &docObj, QString &senderName, QString &receiverName, QString &message);
    bool extractContactResponseFields(const QJsonObject &docObj, QString &senderName, QString &receiverName, QString &status, QString &message);
    QJsonObject createContactRequestMessage(const QString &senderName, const QString &message);
    QJsonObject createContactResponseMessage(const QString &senderName, const QString &status, const QString &message);
    ServerWorker* findWorkerByUserName(const QString &userName);
    void sendContactErrorResponse(const QString &senderName, const QString &receiverName, const QString &errorMessage, ServerWorker *sender);

signals:
    void logMessage(const QString &msg);

public slots:
    void stopServer();
    void jsonReceived(ServerWorker *sender,const QJsonObject &docObj);
    void userDisconnected(ServerWorker *sender);
};

#endif // CHATSERVER_H
