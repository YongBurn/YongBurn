#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_chatClient(nullptr)
    , m_database(new DataBase(this))
    , m_contactModel(new ContactModel(this))
    , m_networkThread(new NetworkThread(this))
    , m_statusUpdateTimer(new QTimer(this))
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    
    // 初始化组件
    setupConnections();
    setupModels();
    
    // 启动网络工作线程
    // 注意：NetworkThread现在是一个QObject，不是QThread
    
    // 启动状态更新定时器
    connect(m_statusUpdateTimer, &QTimer::timeout, this, &MainWindow::updateConnectionStatus);
    m_statusUpdateTimer->start(1000); // 每秒更新一次状态
    
    // 设置默认服务器地址
    ui->ServerEdit->setText("127.0.0.1");
    ui->ServerEdit_2->setText("127.0.0.1");
}

MainWindow::~MainWindow()
{
    if (m_networkThread) {
        m_networkThread->disconnectFromServer();
    }
    delete ui;
}

void MainWindow::setupConnections()
{
    // 登录注册按钮
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &MainWindow::on_registerButton_clicked);
    connect(ui->returnButton, &QPushButton::clicked, this, &MainWindow::on_returnButton_clicked);
    connect(ui->Register, &QPushButton::clicked, this, &MainWindow::on_Register_clicked);
    connect(ui->logoutBtn, &QPushButton::clicked, this, &MainWindow::on_logoutBtn_clicked);
    
    // 聊天功能按钮
    connect(ui->sayBtn, &QPushButton::clicked, this, &MainWindow::on_sayBtn_clicked);
    connect(ui->SendprivateChat, &QPushButton::clicked, this, &MainWindow::on_SendprivateChat_clicked);
    connect(ui->PrivateChatreturn, &QPushButton::clicked, this, &MainWindow::on_PrivateChatreturn_clicked);
    
    // 联系人管理按钮
    connect(ui->contacts, &QPushButton::clicked, this, &MainWindow::on_contacts_clicked);
    connect(ui->AddGroup, &QPushButton::clicked, this, &MainWindow::on_AddGroup_clicked);
    connect(ui->Addcontact, &QPushButton::clicked, this, &MainWindow::on_Addcontact_clicked);
    connect(ui->Return, &QPushButton::clicked, this, &MainWindow::on_Return_clicked);
    
    // 用户列表双击事件
    connect(ui->userListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::on_userListWidget_itemDoubleClicked);
    connect(ui->userListWidget_2, &QListWidget::itemDoubleClicked, this, &MainWindow::on_userListWidget_2_itemDoubleClicked);
    connect(ui->userListWidget_4, &QListWidget::itemDoubleClicked, this, &MainWindow::on_userListWidget_4_itemDoubleClicked);
    connect(ui->Grouping, &QListWidget::itemClicked, this, &MainWindow::on_Grouping_itemClicked);
    
    // 网络线程信号
    connect(m_networkThread, &NetworkThread::connected, this, &MainWindow::onNetworkConnected);
    connect(m_networkThread, &NetworkThread::disconnected, this, &MainWindow::onNetworkDisconnected);
    connect(m_networkThread, &NetworkThread::connectionError, this, &MainWindow::onNetworkError);
    connect(m_networkThread, &NetworkThread::messageReceived, this, &MainWindow::onNetworkMessageReceived);
    connect(m_networkThread, &NetworkThread::reconnectionAttempt, this, &MainWindow::onReconnectionAttempt);
}

void MainWindow::setupModels()
{
    // 设置联系人模型
    // 这里可以添加QML视图或者自定义的列表视图
}

bool MainWindow::validateLoginInput()
{
    if (ui->UserNameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入用户名");
        return false;
    }
    if (ui->UserPasswordEdit->text().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入密码");
        return false;
    }
    return true;
}

bool MainWindow::validateRegisterInput()
{
    if (ui->RegisterUserNameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入用户名");
        return false;
    }
    if (ui->RegisterUserPasswordEdit->text().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入密码");
        return false;
    }
    if (ui->AddressNameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入姓名");
        return false;
    }
    return true;
}

void MainWindow::on_loginButton_clicked()
{
    if (!validateLoginInput()) return;
    
    QString username = ui->UserNameEdit->text().trimmed();
    QString password = ui->UserPasswordEdit->text();
    
    qDebug() << "尝试登录 - 用户名:" << username << "密码长度:" << password.length();
    
    // 首先验证本地数据库
    bool isValid = m_database->validateUser(username, password);
    qDebug() << "数据库验证结果:" << isValid;
    
    if (isValid) {
        m_currentUser = username;
        qDebug() << "用户验证成功，开始连接服务器";
        
        // 连接到服务器
        QString serverAddress = ui->ServerEdit->text();
        qDebug() << "服务器地址:" << serverAddress;
        m_networkThread->connectToServer(serverAddress, 1967);
        
        // 注意：不要在连接时发送登录消息，等待连接成功后再发送
        // 登录消息将在 onNetworkConnected 中发送
        
    } else {
        qDebug() << "用户验证失败 - 显示错误消息";
        QMessageBox::warning(this, "登录失败", "用户名或密码错误");
    }
}

void MainWindow::on_registerButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void MainWindow::on_returnButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void MainWindow::on_Register_clicked()
{
    if (!validateRegisterInput()) return;
    
    QString username = ui->RegisterUserNameEdit->text().trimmed();
    QString password = ui->RegisterUserPasswordEdit->text();
    QString nickname = ui->AddressNameEdit->text().trimmed();
    QString phone = ui->TelephonenumberEdit->text().trimmed();
    
    // 检查用户是否已存在
    if (m_database->userExists(username)) {
        QMessageBox::warning(this, "注册失败", "用户名已存在");
        return;
    }
    
    // 添加到本地数据库
    if (m_database->addUser(username, password, nickname, phone)) {
        QMessageBox::information(this, "注册成功", "用户注册成功，请登录");
        ui->stackedWidget->setCurrentWidget(ui->loginPage);
        
        // 清空注册表单
        ui->RegisterUserNameEdit->clear();
        ui->RegisterUserPasswordEdit->clear();
        ui->AddressNameEdit->clear();
        ui->TelephonenumberEdit->clear();
    } else {
        QMessageBox::warning(this, "注册失败", "用户注册失败，请重试");
    }
}

void MainWindow::on_sayBtn_clicked()
{
    QString text = ui->sayLineEdit->text().trimmed();
    if (text.isEmpty()) return;
    
    // 检查是否是私聊消息（格式: @用户名 消息内容）
    if (text.startsWith("@")) {
        int spaceIndex = text.indexOf(" ");
        if (spaceIndex > 1) {
            QString receiver = text.mid(1, spaceIndex - 1).trimmed();
            QString message = text.mid(spaceIndex + 1).trimmed();
            if (!receiver.isEmpty() && !message.isEmpty()) {
                // 发送私聊消息
                QJsonObject privateMessage;
                privateMessage["type"] = "private";
                privateMessage["receiver"] = receiver;
                privateMessage["text"] = message;
                privateMessage["sender"] = m_currentUser;
                m_networkThread->sendMessage(privateMessage);
                
                // 本地显示
                displayPrivateMessage(receiver, message, "", true);
                ui->sayLineEdit->clear();
                
                // 保存到本地数据库
                saveMessageToLocal(m_currentUser, receiver, message, "private");
                return;
            }
        }
    }
    
    // 普通群聊消息
    QJsonObject groupMessage;
    groupMessage["type"] = "message";
    groupMessage["text"] = text;
    groupMessage["sender"] = m_currentUser;
    m_networkThread->sendMessage(groupMessage);
    
    // 立即在本地显示自己发送的群聊消息
    messageReceived(m_currentUser, text);
    
    ui->sayLineEdit->clear();
    
    // 保存到本地数据库
    saveMessageToLocal(m_currentUser, "group", text, "group");
}

void MainWindow::on_SendprivateChat_clicked()
{
    QString text = ui->PrivateChatSayLineEdit->text().trimmed();
    if (text.isEmpty() || m_currentContact.isEmpty()) return;
    
    // 发送私聊消息
    QJsonObject privateMessage;
    privateMessage["type"] = "private";
    privateMessage["receiver"] = m_currentContact;
    privateMessage["text"] = text;
    privateMessage["sender"] = m_currentUser;
    m_networkThread->sendMessage(privateMessage);
    
    // 本地显示
    displayPrivateMessage(m_currentContact, text, "", true);
    ui->PrivateChatSayLineEdit->clear();
    
    // 保存到本地数据库
    saveMessageToLocal(m_currentUser, m_currentContact, text, "private");
}

void MainWindow::on_PrivateChatreturn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);
}

void MainWindow::on_logoutBtn_clicked()
{
    // 发送登出消息
    QJsonObject logoutMessage;
    logoutMessage["type"] = "logout";
    logoutMessage["username"] = m_currentUser;
    m_networkThread->sendMessage(logoutMessage);
    
    // 断开连接
    m_networkThread->disconnectFromServer();
    
    // 切换到登录页面
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    
    // 清空用户列表
    ui->userListWidget->clear();
    m_currentUser.clear();
    m_currentContact.clear();
}

void MainWindow::on_contacts_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
    loadContactsFromDatabase();
    loadGroupsFromDatabase();
}

void MainWindow::on_AddGroup_clicked()
{
    bool ok;
    QString groupName = QInputDialog::getText(this, "添加分组", "请输入分组名称:", QLineEdit::Normal, "", &ok);
    if (ok && !groupName.trimmed().isEmpty()) {
        if (m_database->addGroup(m_currentUser, groupName.trimmed())) {
            loadGroupsFromDatabase();
            QMessageBox::information(this, "成功", "分组添加成功");
        } else {
            QMessageBox::warning(this, "失败", "分组添加失败");
        }
    }
}

void MainWindow::on_Addcontact_clicked()
{
    bool ok;
    QString contactName = QInputDialog::getText(this, "添加联系人", "请输入联系人用户名:", QLineEdit::Normal, "", &ok);
    if (ok && !contactName.trimmed().isEmpty()) {
        QString groupName = "默认分组";
        if (ui->Grouping->currentItem()) {
            groupName = ui->Grouping->currentItem()->text();
        }
        
        QString targetUser = contactName.trimmed();
        
        // 1. 验证用户是否存在（检查在线用户列表）
        bool userExists = false;
        for (int i = 0; i < ui->userListWidget->count(); ++i) {
            QString onlineUser = ui->userListWidget->item(i)->text();
            // 移除"*"标记进行比较
            if (onlineUser.endsWith("*")) {
                onlineUser = onlineUser.left(onlineUser.length() - 1);
            }
            if (onlineUser == targetUser) {
                userExists = true;
                break;
            }
        }
        
        if (!userExists) {
            QMessageBox::warning(this, "用户不存在", "该用户当前不在线或不存在于系统中");
            return;
        }
        
        // 2. 检查是否已经添加过
        if (m_database->contactExists(m_currentUser, targetUser)) {
            QMessageBox::information(this, "重复添加", "该联系人已经存在于您的联系人列表中");
            return;
        }
        
        // 3. 向目标用户发送添加请求
        QJsonObject addRequest;
        addRequest["type"] = "add_contact_request";
        addRequest["sender"] = m_currentUser;
        addRequest["receiver"] = targetUser;
        addRequest["message"] = QString("%1 想要添加您为联系人").arg(m_currentUser);
        m_networkThread->sendMessage(addRequest);
        
        // 4. 显示等待确认提示
        QMessageBox msgBox;
        msgBox.setWindowTitle("添加联系人");
        msgBox.setText("添加请求已发送");
        msgBox.setInformativeText(QString("已向用户 %1 发送添加联系人请求\n\n对方需要在弹窗中确认后，您们才会成为联系人").arg(targetUser));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

void MainWindow::on_Return_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);
}

// 该函数已在前面定义，这里不需要重复实现

void MainWindow::on_userListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if (!item) return;
    
    QString userName = item->text();
    if (userName.endsWith("*")) {
        // 是自己，显示友好提示
        QMessageBox::information(this, "提示", "不能和自己聊天哦！");
        return;
    }
    
    // 在主聊天界面，双击用户时直接进入私聊界面
    switchToPrivateChat(userName);
}

void MainWindow::on_Grouping_itemClicked(QListWidgetItem *item)
{
    if (!item) return;
    
    QString groupName = item->text();
    if (groupName == "全部联系人") {
        m_contactModel->showAllContacts();
    } else {
        m_contactModel->filterByGroup(groupName);
    }
    
    // 刷新联系人列表显示
    updateContactList();
}

void MainWindow::on_userListWidget_4_itemDoubleClicked(QListWidgetItem *item)
{
    if (!item) return;
    
    QString userName = item->text();
    // 移除可能的在线状态标记
    if (userName.contains(" (在线)")) {
        userName = userName.left(userName.indexOf(" (在线)"));
    }
    
    if (userName == m_currentUser) {
        // 是自己，显示友好提示
        QMessageBox::information(this, "提示", "不能和自己聊天哦！");
        return;
    }
    
    // 进入私聊界面
    switchToPrivateChat(userName);
}

void MainWindow::onNetworkConnected()
{
    qDebug() << "网络连接成功 - 当前用户:" << m_currentUser;
    
    // 只有在有当前用户时才发送登录消息
    if (!m_currentUser.isEmpty()) {
        QJsonObject loginMessage;
        loginMessage["type"] = "login";
        loginMessage["text"] = m_currentUser;
        qDebug() << "连接成功，发送登录消息:" << loginMessage;
        m_networkThread->sendMessage(loginMessage);
    }
}

void MainWindow::onNetworkDisconnected()
{
    qDebug() << "Network disconnected";
    updateConnectionStatus();
}

void MainWindow::onNetworkError(const QString &error)
{
    QMessageBox::warning(this, "网络错误", error);
    updateConnectionStatus();
}

void MainWindow::onNetworkMessageReceived(const QJsonObject &message)
{
    jsonReceived(message);
}

void MainWindow::onReconnectionAttempt(int attempt)
{
    qDebug() << "Reconnection attempt:" << attempt;
    updateConnectionStatus();
}

void MainWindow::connectedToServer()
{
    qDebug() << "Connected to server";
    // 不要在这里切换页面，等待登录验证结果
    // switchToChatPage();
}

void MainWindow::disconnectedFromServer()
{
    qDebug() << "Disconnected from server";
}

void MainWindow::messageReceived(const QString &sender, const QString &text)
{
    ui->roomTextEdit->append(QString("%1 : %2").arg(sender).arg(text));
}

void MainWindow::jsonReceived(const QJsonObject &docObj)
{
    const QJsonValue typeVal = docObj.value("type");
    if (typeVal.isNull() || !typeVal.isString()) return;
    
    QString type = typeVal.toString();
    
    if (type.compare("login_success", Qt::CaseInsensitive) == 0) {
        const QJsonValue userNameVal = docObj.value("username");
        if (!userNameVal.isNull() && userNameVal.isString()) {
            m_currentUser = userNameVal.toString();
            qDebug() << "登录成功，切换到聊天页面";
            // 只有在登录成功后才切换到聊天页面
            ui->stackedWidget->setCurrentWidget(ui->chatPage);
        }
    }
    else if (type.compare("message", Qt::CaseInsensitive) == 0) {
        const QJsonValue textVal = docObj.value("text");
        const QJsonValue senderVal = docObj.value("sender");
        if (textVal.isNull() || !textVal.isString()) return;
        if (senderVal.isNull() || !senderVal.isString()) return;
        
        QString sender = senderVal.toString();
        QString text = textVal.toString();
        
        // 如果是自己发送的消息，不再重复显示（因为已经在发送时本地显示了）
        if (sender != m_currentUser) {
            messageReceived(sender, text);
        }
        saveMessageToLocal(sender, "group", text, "group");
    }
    else if (type.compare("newuser", Qt::CaseInsensitive) == 0) {
        const QJsonValue userNameVal = docObj.value("username");
        if (userNameVal.isNull() || !userNameVal.isString()) return;
        userJoined(userNameVal.toString());
    }
    else if (type.compare("add_contact_request", Qt::CaseInsensitive) == 0) {
        const QJsonValue senderVal = docObj.value("sender");
        const QJsonValue messageVal = docObj.value("message");
        
        if (senderVal.isNull() || !senderVal.isString()) return;
        if (messageVal.isNull() || !messageVal.isString()) return;
        
        QString sender = senderVal.toString();
        QString message = messageVal.toString();
        
        // 显示添加联系人请求确认对话框
        QMessageBox msgBox;
        msgBox.setWindowTitle("新的联系人请求");
        msgBox.setText(QString("用户 %1 想要添加您为联系人").arg(sender));
        msgBox.setInformativeText("是否接受请求并添加对方为您的联系人？");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        msgBox.setIcon(QMessageBox::Question);
        
        // 设置按钮文本
        msgBox.button(QMessageBox::Yes)->setText("接受并添加");
        msgBox.button(QMessageBox::No)->setText("拒绝");
        
        // 显示弹窗并等待用户响应
        QMessageBox::StandardButton reply = (QMessageBox::StandardButton)msgBox.exec();
        
        if (reply == QMessageBox::Yes) {
            // 接受请求，添加对方为联系人
            QString groupName = "默认分组";
            if (m_database->addContact(m_currentUser, sender, groupName)) {
                // 发送确认回复
                QJsonObject response;
                response["type"] = "add_contact_response";
                response["sender"] = m_currentUser;
                response["receiver"] = sender;
                response["status"] = "accepted";
                response["message"] = QString("%1 已接受您的添加请求").arg(m_currentUser);
                m_networkThread->sendMessage(response);
                
                QMessageBox::information(this, "成功", QString("已添加 %1 为联系人").arg(sender));
                updateContactList();
            } else {
                QMessageBox::warning(this, "失败", "添加联系人失败");
            }
        } else {
            // 拒绝请求，发送拒绝回复
            QJsonObject response;
            response["type"] = "add_contact_response";
            response["sender"] = m_currentUser;
            response["receiver"] = sender;
            response["status"] = "rejected";
            response["message"] = QString("%1 拒绝了您的添加请求").arg(m_currentUser);
            m_networkThread->sendMessage(response);
            
            QMessageBox::information(this, "已拒绝", QString("已拒绝 %1 的添加请求").arg(sender));
        }
    }
    else if (type.compare("add_contact_response", Qt::CaseInsensitive) == 0) {
        const QJsonValue senderVal = docObj.value("sender");
        const QJsonValue statusVal = docObj.value("status");
        const QJsonValue messageVal = docObj.value("message");
        
        if (senderVal.isNull() || !senderVal.isString()) return;
        if (statusVal.isNull() || !statusVal.isString()) return;
        if (messageVal.isNull() || !messageVal.isString()) return;
        
        QString sender = senderVal.toString();
        QString status = statusVal.toString();
        QString message = messageVal.toString();
        
        if (status == "accepted") {
            // 对方接受了添加请求
            QString groupName = "默认分组";
            if (m_database->addContact(m_currentUser, sender, groupName)) {
                updateContactList();
                QMessageBox::information(this, "添加成功", QString("%1 已接受您的添加请求，已自动添加为联系人").arg(sender));
            } else {
                QMessageBox::warning(this, "添加失败", "自动添加联系人失败，请手动添加");
            }
        } else {
            // 对方拒绝了添加请求
            QMessageBox::information(this, "添加被拒绝", message);
        }
    }
    else if (type.compare("userdisconnected", Qt::CaseInsensitive) == 0) {
        const QJsonValue userNameVal = docObj.value("username");
        if (userNameVal.isNull() || !userNameVal.isString()) return;
        userLeft(userNameVal.toString());
    }
    else if (type.compare("userlist", Qt::CaseInsensitive) == 0) {
        const QJsonValue userlistVal = docObj.value("userlist");
        if (userlistVal.isNull() || !userlistVal.isArray()) return;
        userListReceived(userlistVal.toVariant().toStringList());
    }
    else if (type.compare("loginfailed", Qt::CaseInsensitive) == 0) {
        const QJsonValue reasonVal = docObj.value("reason");
        QString reason = "登录失败";
        if (!reasonVal.isNull() && reasonVal.isString()) {
            reason = reasonVal.toString();
        }
        QMessageBox::warning(this, "登录失败", reason);
        m_networkThread->disconnectFromServer();
        switchToLoginPage();
    }
    else if (type.compare("private", Qt::CaseInsensitive) == 0) {
        const QJsonValue textVal = docObj.value("text");
        const QJsonValue senderVal = docObj.value("sender");
        const QJsonValue receiverVal = docObj.value("receiver");
        const QJsonValue timestampVal = docObj.value("timestamp");
        
        if (textVal.isNull() || !textVal.isString()) return;
        if (senderVal.isNull() || !senderVal.isString()) return;
        if (receiverVal.isNull() || !receiverVal.isString()) return;
        
        QString text = textVal.toString();
        QString sender = senderVal.toString();
        QString receiver = receiverVal.toString();
        QString timestamp = timestampVal.isString() ? timestampVal.toString() : "";
        
        bool isSentByMe = (sender == m_currentUser);
        
        if (isSentByMe) {
            displayPrivateMessage(receiver, text, timestamp, true);
        } else {
            displayPrivateMessage(sender, text, timestamp, false);
        }
        
        // 保存到本地数据库
        QString contact = isSentByMe ? receiver : sender;
        saveMessageToLocal(sender, receiver, text, "private");
    }
    else if (type.compare("private_error", Qt::CaseInsensitive) == 0) {
        const QJsonValue textVal = docObj.value("text");
        const QJsonValue receiverVal = docObj.value("receiver");
        
        if (!textVal.isNull() && textVal.isString()) {
            QString errorMsg = textVal.toString();
            QString receiver = receiverVal.isString() ? receiverVal.toString() : "";
            QMessageBox::warning(this, "私聊发送失败", QString("给 %1 的消息发送失败: %2").arg(receiver).arg(errorMsg));
        }
    }
}

void MainWindow::userJoined(const QString &user)
{
    ui->userListWidget->addItem(user);
}

void MainWindow::userLeft(const QString &user)
{
    for (auto aItem : ui->userListWidget->findItems(user, Qt::MatchExactly)) {
        ui->userListWidget->removeItemWidget(aItem);
        delete aItem;
    }
}

void MainWindow::userListReceived(const QStringList &list)
{
    ui->userListWidget->clear();
    ui->userListWidget->addItems(list);
    
    // 为群聊界面的用户列表设置提示信息
    for (int i = 0; i < ui->userListWidget->count(); ++i) {
        QListWidgetItem *item = ui->userListWidget->item(i);
        QString userName = item->text();
        
        if (userName.endsWith("*")) {
            userName = userName.left(userName.length() - 1);
            if (userName == m_currentUser) {
                item->setToolTip("这是你自己");
            } else {
                item->setToolTip("双击开始私聊");
            }
        } else {
            item->setToolTip("双击开始私聊");
        }
    }
    
    // 同步更新私聊界面的用户列表
    syncPrivateChatUserList();
}

void MainWindow::displayPrivateMessage(const QString &sender, const QString &text, const QString &timestamp, bool isSentByMe)
{
    QString timeStr = timestamp.isEmpty() ? QDateTime::currentDateTime().toString("hh:mm:ss") : timestamp;
    QString formattedMsg;
    
    if (isSentByMe) {
        formattedMsg = QString("[%1] 你对 %2 说(私聊): %3").arg(timeStr).arg(sender).arg(text);
    } else {
        formattedMsg = QString("[%1] %2 对你说(私聊): %3").arg(timeStr).arg(sender).arg(text);
    }
    
    // 私聊消息只显示在私聊界面，不显示在群聊界面
    ui->privateTextEdit->append(formattedMsg);
}

void MainWindow::switchToChatPage()
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);
    loadLocalData();
}

void MainWindow::switchToLoginPage()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}


void MainWindow::switchToPrivateChat(const QString &contact)
{
    m_currentContact = contact;
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    ui->privateTextEdit->clear();
    
    // 同步私聊界面的用户列表
    syncPrivateChatUserList();
    
    // 加载聊天历史
    loadChatHistory(contact);
    
    // 更新联系人未读消息数
    m_contactModel->updateUnreadCount(contact, 0);
}

void MainWindow::switchToContactsPage()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
    loadContactsFromDatabase();
    loadGroupsFromDatabase();
}

// switchToLoginPage函数已在前面定义

void MainWindow::loadContactsFromDatabase()
{
    if (!m_database || !m_database->isDatabaseReady() || m_currentUser.isEmpty()) return;
    
    QStringList contacts = m_database->getContacts(m_currentUser);
    m_contactModel->clearContacts();
    
    for (const QString &contact : contacts) {
        Contact c;
        c.name = contact;
        c.nickname = m_database->getUserNickname(contact);
        c.group = "默认分组"; // 可以从数据库获取实际分组
        c.isOnline = false; // 可以从服务器获取在线状态
        c.unreadCount = 0; // 可以计算未读消息数
        m_contactModel->addContact(c);
    }
    
    updateContactList();
}

void MainWindow::loadGroupsFromDatabase()
{
    if (!m_database || !m_database->isDatabaseReady() || m_currentUser.isEmpty()) return;
    
    ui->Grouping->clear();
    ui->Grouping->addItem("全部联系人");
    
    QStringList groups = m_database->getGroups(m_currentUser);
    for (const QString &group : groups) {
        ui->Grouping->addItem(group);
    }
}

void MainWindow::addContactToList(const QString &contact, const QString &group)
{
    if (!m_database || !m_database->isDatabaseReady() || m_currentUser.isEmpty()) return;
    
    Contact c;
    c.name = contact;
    c.nickname = m_database->getUserNickname(contact);
    c.group = group;
    c.isOnline = false;
    c.unreadCount = 0;
    
    m_contactModel->addContact(c);
    updateContactList();
}

void MainWindow::updateContactList()
{
    // userListWidget_4 用于显示联系人（在联系人界面）
    ui->userListWidget_4->clear();
    
    // 获取当前选中的分组
    QListWidgetItem *currentItem = ui->Grouping->currentItem();
    QString currentGroup = currentItem ? currentItem->text() : "全部联系人";
    
    // 根据当前分组获取联系人
    QStringList contacts;
    if (currentGroup == "全部联系人") {
        contacts = m_database->getContacts(m_currentUser);
    } else {
        contacts = m_database->getContactsByGroup(m_currentUser, currentGroup);
    }
    
    // 添加联系人到列表，并设置在线状态
    for (const QString &contactName : contacts) {
        QListWidgetItem *item = new QListWidgetItem(contactName);
        ui->userListWidget_4->addItem(item);
        
        // 检查联系人是否在线（根据在线用户列表）
        bool isOnline = false;
        for (int i = 0; i < ui->userListWidget->count(); ++i) {
            QString onlineUser = ui->userListWidget->item(i)->text();
            // 移除"*"标记进行比较
            if (onlineUser.endsWith("*")) {
                onlineUser = onlineUser.left(onlineUser.length() - 1);
            }
            if (onlineUser == contactName) {
                isOnline = true;
                break;
            }
        }
        
        // 设置显示文本和提示
        if (isOnline) {
            item->setText(contactName + " (在线)");
            item->setToolTip(contactName + " - 在线，双击开始私聊");
        } else {
            item->setToolTip(contactName + " - 离线，双击发送消息");
        }
        
        // 设置双击事件处理
        item->setFlags(item->flags() | Qt::ItemIsEnabled);
    }
    
    // userListWidget_2 用于显示在线用户（在私聊界面），由 syncPrivateChatUserList 函数维护
    // 不需要在这里更新，它会在用户列表变化时自动同步
}

void MainWindow::syncPrivateChatUserList()
{
    // 同步私聊界面的用户列表与群聊界面的在线用户列表
    ui->userListWidget_2->clear();
    
    for (int i = 0; i < ui->userListWidget->count(); ++i) {
        QListWidgetItem *sourceItem = ui->userListWidget->item(i);
        if (!sourceItem) continue;
        
        QString userName = sourceItem->text();
        
        // 复制用户到私聊界面的用户列表
        QListWidgetItem *newItem = new QListWidgetItem(userName);
        ui->userListWidget_2->addItem(newItem);
        
        // 复制提示信息
        newItem->setToolTip(sourceItem->toolTip());
        
        // 设置相同的双击行为
        newItem->setFlags(newItem->flags() | Qt::ItemIsEnabled);
    }
}

void MainWindow::updateConnectionStatus()
{
    if (m_networkThread) {
        QString state = m_networkThread->connectionState();
        // 可以在状态栏显示连接状态
        qDebug() << "Connection state:" << state;
    }
}

void MainWindow::loadLocalData()
{
    if (m_currentUser.isEmpty()) return;
    
    // 加载联系人
    loadContactsFromDatabase();
    
    // 加载分组
    loadGroupsFromDatabase();
    
    // 加载最近的聊天记录
    // 这里可以实现加载最近聊天记录的功能
}

void MainWindow::saveMessageToLocal(const QString &sender, const QString &receiver, const QString &content, const QString &type)
{
    if (m_database && m_database->isDatabaseReady()) {
        m_database->saveMessage(sender, receiver, content, type);
    }
}

void MainWindow::loadChatHistory(const QString &contact)
{
    if (!m_database || !m_database->isDatabaseReady()) return;
    
    QJsonArray history = m_database->getChatHistory(m_currentUser, contact, 50);
    
    for (const QJsonValue &value : history) {
        QJsonObject message = value.toObject();
        QString sender = message["sender"].toString();
        QString content = message["content"].toString();
        QString timestamp = message["timestamp"].toString();
        bool isSentByMe = (sender == m_currentUser);
        
        displayPrivateMessage(contact, content, timestamp, isSentByMe);
    }
}

void MainWindow::updateGroupList()
{
    // 更新分组列表显示
    loadGroupsFromDatabase();
}

void MainWindow::on_userListWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    if (!item) return;
    
    QString userName = item->text();
    if (userName == m_currentUser) {
        // 是自己，显示友好提示
        QMessageBox::information(this, "提示", "不能和自己聊天哦！");
        return;
    }
    
    // 在联系人界面，双击用户时跳转到私聊界面
    switchToPrivateChat(userName);
}

// 这些函数已在前面定义，这里不需要重复实现
