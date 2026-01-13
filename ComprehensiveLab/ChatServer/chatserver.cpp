#include "chatserver.h"
#include <QDebug>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>

ChatServer::ChatServer(QObject *parent):
    QTcpServer(parent)
{
    // 启动心跳检测定时器
    QTimer *heartbeatTimer = new QTimer(this);
    connect(heartbeatTimer, &QTimer::timeout, this, &ChatServer::checkHeartbeat);
    heartbeatTimer->start(60000); // 每分钟检查一次心跳
}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker= new ServerWorker(this);
    if(!worker->setSocketDescriptor(socketDescriptor)){
        worker->deleteLater();
        return;
    }
    
    // 记录连接时间用于心跳检测
    worker->setProperty("lastHeartbeat", QDateTime::currentDateTime());
    
    connect(worker,&ServerWorker::logMessage,this,&ChatServer::logMessage);
    connect(worker,&ServerWorker::jsonReceived,this,&ChatServer::jsonReceived);
    connect(worker,&ServerWorker::disconnectedFromClient,this,std::bind(&ChatServer::userDisconnected,this,worker));
    m_clients.append(worker);//成功了就添加进来
    emit logMessage("新的用户连接上了");
}

void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    for(ServerWorker *worker : m_clients){
        if(worker != exclude){
            worker->sendJson(message);
        }
    }
}

void ChatServer::sendPrivateMessage(const QJsonObject &message, ServerWorker *sender)//发送私聊信息
{
    QString receiver = message.value("receiver").toString();
    QString senderName = message.value("sender").toString();
    // 查找接收者
    for(ServerWorker *worker : m_clients){
        if(worker->userName() == receiver){
            // 找到接收者，发送消息
            worker->sendJson(message);
            // 记录日志
            emit logMessage(QString("私聊: %1 -> %2").arg(senderName).arg(receiver));
            return;
        }
    }
    // 如果没有找到接收者，给发送者发送错误消息
    QJsonObject errorMessage;
    errorMessage["type"] = "private_error";
    errorMessage["text"] = QString("用户 %1 不在线").arg(receiver);
    errorMessage["receiver"] = receiver;
    sender->sendJson(errorMessage);
    emit logMessage(QString("私聊失败: 用户 %1 不存在或离线").arg(receiver));
}

void ChatServer::stopServer()
{
    close();
}

void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &docObj)//处理接收到的json信息
{
    const QJsonValue typeVal= docObj.value("type");
    if(typeVal.isNull()||!typeVal.isString()) return ;
    
    QString messageType = typeVal.toString();
    
    // 处理心跳消息
    if(messageType.compare("heartbeat", Qt::CaseInsensitive) == 0){
        // 更新客户端最后心跳时间
        sender->setProperty("lastHeartbeat", QDateTime::currentDateTime());
        
        // 发送心跳响应
        QJsonObject heartbeatResponse;
        heartbeatResponse["type"] = "heartbeat";
        heartbeatResponse["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
        sender->sendJson(heartbeatResponse);
        return;
    }
    
    if(messageType.compare("login",Qt::CaseInsensitive)==0){
        const QJsonValue userNameVal =docObj.value("text");
        if(userNameVal.isNull()||!userNameVal.isString()) return ;
        // 检查用户名是否已存在
        QString userName = userNameVal.toString().trimmed();
        if(userName.isEmpty()) return;
        bool isUserNameTaken = false;
        for(ServerWorker *worker : m_clients){
            if(worker->userName() == userName){
                isUserNameTaken = true;
                break;
            }
        }
        if(isUserNameTaken){
            // 发送登录失败消息
            QJsonObject loginFailedMessage;
            loginFailedMessage["type"] = "loginfailed";
            loginFailedMessage["reason"] = "用户名已存在";
            sender->sendJson(loginFailedMessage);
            return;
        }
        //登录没有问题
        sender->setUserName(userNameVal.toString());//把登录的用户名传过来设置好，后面发消息才能获取到用户名
        // 发送登录成功的消息，包含用户名
        QJsonObject loginSuccessMessage;
        loginSuccessMessage["type"] = "login_success";
        loginSuccessMessage["username"] = userName;
        sender->sendJson(loginSuccessMessage);

        QJsonObject connectedMessage;
        connectedMessage["type"] = "newuser";
        connectedMessage["username"] = userNameVal.toString();
        broadcast(connectedMessage,sender);

        //还得把用户列表告诉新登进来的用户
        QJsonObject userListMessage;
        userListMessage["type"] = "userlist";
        QJsonArray userlist;
        for(ServerWorker *worker : m_clients){
            if(worker == sender) userlist.append(worker->userName()+ "*");
            else userlist.append(worker->userName());
        }
        userListMessage["userlist"] = userlist;
        sender->sendJson(userListMessage);
        
        emit logMessage(QString("用户 %1 登录成功").arg(userName));
    }
    else if(messageType.compare("message",Qt::CaseInsensitive)==0){ //发信息的往后稍稍
        const QJsonValue textVal =docObj.value("text");
        if(textVal.isNull()||!textVal.isString()) return ;
        const QString text= textVal.toString().trimmed();
        if(text.isEmpty()) return ;
        QJsonObject message;
        message["type"] = "message";
        message["text"] = text;
        message["sender"] = sender->userName();
        broadcast(message,sender);
        
        emit logMessage(QString("群聊消息: %1 - %2").arg(sender->userName()).arg(text));
    }
    else if(messageType.compare("private", Qt::CaseInsensitive) == 0){
        // 处理私聊消息
        const QJsonValue textVal = docObj.value("text");
        const QJsonValue receiverVal = docObj.value("receiver");
        const QJsonValue senderVal = docObj.value("sender");
        if(textVal.isNull() || !textVal.isString()) return;
        if(receiverVal.isNull() || !receiverVal.isString()) return;
        QString text = textVal.toString().trimmed();
        QString receiver = receiverVal.toString().trimmed();
        if(text.isEmpty()) return;
        // 构建私聊消息
        QJsonObject privateMessage;
        privateMessage["type"] = "private";
        privateMessage["text"] = text;
        privateMessage["sender"] = sender->userName();
        privateMessage["receiver"] = receiver;
        privateMessage["timestamp"] = QDateTime::currentDateTime().toString("hh:mm:ss");

        // 发送私聊消息
        sendPrivateMessage(privateMessage, sender);
        
        emit logMessage(QString("私聊消息: %1 -> %2 - %3").arg(sender->userName()).arg(receiver).arg(text));
    }
    else if(messageType.compare("logout", Qt::CaseInsensitive) == 0){
        // 处理登出消息
        const QJsonValue userNameVal = docObj.value("username");
        if(!userNameVal.isNull() && userNameVal.isString()){
            QString userName = userNameVal.toString();
            emit logMessage(QString("用户 %1 主动登出").arg(userName));
            
            // 发送用户下线消息
            QJsonObject disconnectedMessage;
            disconnectedMessage["type"] = "userdisconnected";
            disconnectedMessage["username"] = userName;
            broadcast(disconnectedMessage, sender);
        }
        
        // 断开客户端连接
        sender->disconnectFromHost();
    }
    else if(messageType.compare("add_contact_request", Qt::CaseInsensitive) == 0){
        // 处理添加联系人请求
        const QJsonValue senderVal = docObj.value("sender");
        const QJsonValue receiverVal = docObj.value("receiver");
        const QJsonValue messageVal = docObj.value("message");
        
        if(senderVal.isNull() || !senderVal.isString()) return;
        if(receiverVal.isNull() || !receiverVal.isString()) return;
        if(messageVal.isNull() || !messageVal.isString()) return;
        
        QString senderName = senderVal.toString();
        QString receiverName = receiverVal.toString();
        QString message = messageVal.toString();
        
        // 查找接收者
        ServerWorker *receiverWorker = nullptr;
        for(ServerWorker *worker : m_clients){
            if(worker->userName() == receiverName && worker != sender){
                receiverWorker = worker;
                break;
            }
        }
        
        if(receiverWorker){
            // 转发添加联系人请求给接收者
            QJsonObject forwardMessage;
            forwardMessage["type"] = "add_contact_request";
            forwardMessage["sender"] = senderName;
            forwardMessage["message"] = message;
            receiverWorker->sendJson(forwardMessage);
            emit logMessage(QString("转发添加联系人请求: %1 -> %2").arg(senderName).arg(receiverName));
        } else {
            // 接收者不在线，发送错误回复
            QJsonObject errorResponse;
            errorResponse["type"] = "add_contact_response";
            errorResponse["sender"] = receiverName;
            errorResponse["receiver"] = senderName;
            errorResponse["status"] = "error";
            errorResponse["message"] = QString("用户 %1 不在线").arg(receiverName);
            sender->sendJson(errorResponse);
            emit logMessage(QString("添加联系人请求失败: 用户 %1 不在线").arg(receiverName));
        }
    }
    else if(messageType.compare("add_contact_response", Qt::CaseInsensitive) == 0){
        // 处理添加联系人响应
        const QJsonValue senderVal = docObj.value("sender");
        const QJsonValue receiverVal = docObj.value("receiver");
        const QJsonValue statusVal = docObj.value("status");
        const QJsonValue messageVal = docObj.value("message");
        
        if(senderVal.isNull() || !senderVal.isString()) return;
        if(receiverVal.isNull() || !receiverVal.isString()) return;
        if(statusVal.isNull() || !statusVal.isString()) return;
        if(messageVal.isNull() || !messageVal.isString()) return;
        
        QString senderName = senderVal.toString();
        QString receiverName = receiverVal.toString();
        QString status = statusVal.toString();
        QString message = messageVal.toString();
        
        // 查找原始请求发送者（现在是响应的接收者）
        ServerWorker *originalSender = nullptr;
        for(ServerWorker *worker : m_clients){
            if(worker->userName() == receiverName){
                originalSender = worker;
                break;
            }
        }
        
        if(originalSender){
            // 转发响应给原始发送者
            QJsonObject forwardResponse;
            forwardResponse["type"] = "add_contact_response";
            forwardResponse["sender"] = senderName;
            forwardResponse["status"] = status;
            forwardResponse["message"] = message;
            originalSender->sendJson(forwardResponse);
            emit logMessage(QString("转发添加联系人响应: %1 -> %2 (状态: %3)").arg(senderName).arg(receiverName).arg(status));
        } else {
            emit logMessage(QString("添加联系人响应失败: 原始发送者 %1 不在线").arg(receiverName));
        }
    }
}

void ChatServer::userDisconnected(ServerWorker *sender)
{
    m_clients.removeAll(sender);//移除数组中的这个客户端
    const QString userName = sender->userName();
    if(!userName.isEmpty()){
        QJsonObject disconnectedMessage;
        disconnectedMessage["type"]= "userdisconnected";
        disconnectedMessage["username"]= userName;
        broadcast(disconnectedMessage,nullptr);
        emit logMessage(QString("用户 %1 断开连接").arg(userName));
    }
    sender->deleteLater();//真正删除掉
}

void ChatServer::checkHeartbeat()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QList<ServerWorker*> disconnectedClients;
    
    for(ServerWorker *worker : m_clients){
        QDateTime lastHeartbeat = worker->property("lastHeartbeat").toDateTime();
        if(lastHeartbeat.isValid() && lastHeartbeat.secsTo(currentTime) > 120){ // 超过2分钟没有心跳
            emit logMessage(QString("用户 %1 心跳超时，强制断开").arg(worker->userName()));
            disconnectedClients.append(worker);
        }
    }
    
    // 断开超时的客户端
    for(ServerWorker *worker : disconnectedClients){
        worker->disconnectFromHost();
    }
}

void ChatServer::handleAddContactRequest(const QJsonObject &docObj, ServerWorker *sender)
{
    // 验证必需字段
    QString senderName, receiverName, message;
    if (!extractContactRequestFields(docObj, senderName, receiverName, message)) {
        return;
    }
    
    // 查找接收者
    ServerWorker *receiverWorker = findWorkerByUserName(receiverName);
    if (!receiverWorker || receiverWorker == sender) {
        sendContactErrorResponse(senderName, receiverName, "用户不在线或不存在", sender);
        return;
    }
    
    // 转发请求给接收者
    QJsonObject forwardMessage = createContactRequestMessage(senderName, message);
    receiverWorker->sendJson(forwardMessage);
    emit logMessage(QString("转发添加联系人请求: %1 -> %2").arg(senderName).arg(receiverName));
}

void ChatServer::handleAddContactResponse(const QJsonObject &docObj, ServerWorker *sender)
{
    // 验证必需字段
    QString senderName, receiverName, status, message;
    if (!extractContactResponseFields(docObj, senderName, receiverName, status, message)) {
        return;
    }
    
    // 查找原始请求发送者（现在是响应接收者）
    ServerWorker *originalSender = findWorkerByUserName(receiverName);
    if (!originalSender) {
        emit logMessage(QString("添加联系人响应失败: 原始发送者 %1 不在线").arg(receiverName));
        return;
    }
    
    // 转发响应给原始发送者
    QJsonObject forwardResponse = createContactResponseMessage(senderName, status, message);
    originalSender->sendJson(forwardResponse);
    emit logMessage(QString("转发添加联系人响应: %1 -> %2 (状态: %3)").arg(senderName).arg(receiverName).arg(status));
}

bool ChatServer::extractContactRequestFields(const QJsonObject &docObj, QString &senderName, QString &receiverName, QString &message)
{
    const QJsonValue senderVal = docObj.value("sender");
    const QJsonValue receiverVal = docObj.value("receiver");
    const QJsonValue messageVal = docObj.value("message");
    
    if(senderVal.isNull() || !senderVal.isString()) return false;
    if(receiverVal.isNull() || !receiverVal.isString()) return false;
    if(messageVal.isNull() || !messageVal.isString()) return false;
    
    senderName = senderVal.toString();
    receiverName = receiverVal.toString();
    message = messageVal.toString();
    return true;
}

bool ChatServer::extractContactResponseFields(const QJsonObject &docObj, QString &senderName, QString &receiverName, QString &status, QString &message)
{
    const QJsonValue senderVal = docObj.value("sender");
    const QJsonValue receiverVal = docObj.value("receiver");
    const QJsonValue statusVal = docObj.value("status");
    const QJsonValue messageVal = docObj.value("message");
    
    if(senderVal.isNull() || !senderVal.isString()) return false;
    if(receiverVal.isNull() || !receiverVal.isString()) return false;
    if(statusVal.isNull() || !statusVal.isString()) return false;
    if(messageVal.isNull() || !messageVal.isString()) return false;
    
    senderName = senderVal.toString();
    receiverName = receiverVal.toString();
    status = statusVal.toString();
    message = messageVal.toString();
    return true;
}

QJsonObject ChatServer::createContactRequestMessage(const QString &senderName, const QString &message)
{
    QJsonObject forwardMessage;
    forwardMessage["type"] = "add_contact_request";
    forwardMessage["sender"] = senderName;
    forwardMessage["message"] = message;
    return forwardMessage;
}

QJsonObject ChatServer::createContactResponseMessage(const QString &senderName, const QString &status, const QString &message)
{
    QJsonObject forwardResponse;
    forwardResponse["type"] = "add_contact_response";
    forwardResponse["sender"] = senderName;
    forwardResponse["status"] = status;
    forwardResponse["message"] = message;
    return forwardResponse;
}

ServerWorker* ChatServer::findWorkerByUserName(const QString &userName)
{
    for(ServerWorker *worker : m_clients){
        if(worker->userName() == userName){
            return worker;
        }
    }
    return nullptr;
}

void ChatServer::sendContactErrorResponse(const QString &senderName, const QString &receiverName, const QString &errorMessage, ServerWorker *sender)
{
    QJsonObject errorResponse;
    errorResponse["type"] = "add_contact_response";
    errorResponse["sender"] = receiverName;
    errorResponse["receiver"] = senderName;
    errorResponse["status"] = "error";
    errorResponse["message"] = errorMessage;
    sender->sendJson(errorResponse);
    emit logMessage(QString("添加联系人请求失败: %1").arg(errorMessage));
}
