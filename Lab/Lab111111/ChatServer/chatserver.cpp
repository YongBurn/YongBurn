#include "chatserver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
{
}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker = new ServerWorker(this);
    if (!worker->setSocketDescriptor(socketDescriptor)) {
        delete worker;
        return;
    }

    // 修正：信号槽参数不匹配问题（用lambda中转传递worker参数）
    connect(worker, &ServerWorker::jsonReceived, this, &ChatServer::jsonReceived);
    // 原错误绑定 → 修正为lambda表达式，手动传递worker给userDisconnected槽
    connect(worker, &ServerWorker::disconnectedFromClient, this, [=]() {
        this->userDisconnected(worker);
    });
    connect(worker, &ServerWorker::logMessage, this, &ChatServer::logMessage);

    m_clients.append(worker);
    emit logMessage("新客户端连接：" + QString::number(socketDescriptor));
    qDebug() << "新客户端连接：" << socketDescriptor;
}

void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &docObj)
{
    QString type = docObj["type"].toString();
    if (type == "login") {
        QString user = docObj["username"].toString();
        sender->setUserName(user);
        // 广播上线通知
        QJsonObject notify;
        notify["type"] = "notification";
        notify["message"] = user + " 加入了聊天室";
        notify["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
        broadcast(notify, sender);
        emit logMessage(user + " 加入了聊天室");
    } else if (type == "message") {
        // 群聊消息
        QJsonObject msg = docObj;
        msg["from"] = sender->userName();
        msg["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
        broadcast(msg);
        emit logMessage(sender->userName() + " 发送消息：" + docObj["content"].toString());
    }
}

void ChatServer::userDisconnected(ServerWorker *sender)
{
    m_clients.removeAll(sender);
    QString user = sender->userName();
    if (!user.isEmpty()) {
        QJsonObject notify;
        notify["type"] = "notification";
        notify["message"] = user + " 离开了聊天室";
        notify["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
        broadcast(notify);
        emit logMessage(user + " 离开了聊天室");
    }
    sender->deleteLater();
}

void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    QByteArray data = QJsonDocument(message).toJson(QJsonDocument::Compact);
    for (ServerWorker *worker : m_clients) {
        if (worker != exclude && !worker->userName().isEmpty()) {
            worker->sendJson(message);
        }
    }
}
