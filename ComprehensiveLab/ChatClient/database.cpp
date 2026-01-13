#include "database.h"
#include <QDebug>
#include <QDir>
#include <QCryptographicHash>

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    initDatabase();
}

DataBase::~DataBase()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DataBase::initDatabase()
{
    qDebug() << "DataBase::initDatabase - 开始初始化数据库";
    
    // 创建数据库目录
    QDir dbDir(QDir::homePath() + "/.chatapp");
    if (!dbDir.exists()) {
        bool dirCreated = dbDir.mkpath(".");
        qDebug() << "数据库目录创建结果:" << dirCreated;
    }

    // 设置数据库连接
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = dbDir.absoluteFilePath("chatapp.db");
    m_db.setDatabaseName(dbPath);
    qDebug() << "数据库路径:" << dbPath;

    if (!m_db.open()) {
        QString errorMsg = "无法打开数据库: " + m_db.lastError().text();
        qDebug() << "数据库打开失败:" << errorMsg;
        emit databaseError(errorMsg);
        return false;
    }

    qDebug() << "数据库打开成功";
    
    // 创建表结构
    bool result = createTables();
    qDebug() << "创建表结构结果:" << result;
    return result;
}

bool DataBase::createTables()
{
    qDebug() << "DataBase::createTables - 开始创建表结构";
    
    // 用户表
    QString createUsersTable = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            nickname TEXT NOT NULL,
            phone TEXT,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    )";

    // 分组表
    QString createGroupsTable = R"(
        CREATE TABLE IF NOT EXISTS groups (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL,
            group_name TEXT NOT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            UNIQUE(username, group_name)
        )
    )";

    // 联系人表
    QString createContactsTable = R"(
        CREATE TABLE IF NOT EXISTS contacts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL,
            contact_name TEXT NOT NULL,
            group_name TEXT DEFAULT '默认分组',
            added_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            UNIQUE(username, contact_name)
        )
    )";

    // 消息记录表
    QString createMessagesTable = R"(
        CREATE TABLE IF NOT EXISTS messages (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            sender TEXT NOT NULL,
            receiver TEXT NOT NULL,
            content TEXT NOT NULL,
            message_type TEXT DEFAULT 'text',
            timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            is_read INTEGER DEFAULT 0
        )
    )";

    qDebug() << "创建用户表...";
    bool success = executeQuery(createUsersTable);
    qDebug() << "用户表创建结果:" << success;
    
    qDebug() << "创建分组表...";
    success &= executeQuery(createGroupsTable);
    qDebug() << "分组表创建结果:" << success;
    
    qDebug() << "创建联系人表...";
    success &= executeQuery(createContactsTable);
    qDebug() << "联系人表创建结果:" << success;
    
    qDebug() << "创建消息表...";
    success &= executeQuery(createMessagesTable);
    qDebug() << "消息表创建结果:" << success;

    // 插入默认分组
    if (success) {
        qDebug() << "插入默认分组...";
        QString insertDefaultGroup = "INSERT OR IGNORE INTO groups (username, group_name) VALUES ('system', '默认分组')";
        executeQuery(insertDefaultGroup);
        
        // 添加默认测试用户
        QString defaultUsername = "test";
        QString defaultPassword = "123456";
        QString defaultNickname = "测试用户";
        QString defaultPhone = "***********";
        
        // 检查测试用户是否已存在
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT id FROM users WHERE username = ?");
        checkQuery.addBindValue(defaultUsername);
        
        if (checkQuery.exec() && !checkQuery.next()) {
            // 测试用户不存在，创建它
            qDebug() << "创建默认测试用户:" << defaultUsername;
            QString hashedPassword = QCryptographicHash::hash(defaultPassword.toUtf8(), QCryptographicHash::Md5).toHex();
            
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO users (username, password, nickname, phone) VALUES (?, ?, ?, ?)");
            insertQuery.addBindValue(defaultUsername);
            insertQuery.addBindValue(hashedPassword);
            insertQuery.addBindValue(defaultNickname);
            insertQuery.addBindValue(defaultPhone);
            
            if (insertQuery.exec()) {
                qDebug() << "默认测试用户创建成功 - 用户名:" << defaultUsername << "密码:" << defaultPassword;
                
                // 为测试用户创建默认分组
                addGroup(defaultUsername, "默认分组");
                addGroup(defaultUsername, "好友");
                addGroup(defaultUsername, "同事");
            } else {
                qDebug() << "默认测试用户创建失败:" << insertQuery.lastError().text();
            }
        } else {
            qDebug() << "默认测试用户已存在，跳过创建";
        }
    }

    return success;
}

bool DataBase::executeQuery(const QString &queryStr)
{
    QSqlQuery query;
    if (!query.exec(queryStr)) {
        emit databaseError("SQL执行错误: " + query.lastError().text());
        qDebug() << "SQL Error:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::addUser(const QString &username, const QString &password, const QString &nickname, const QString &phone)
{
    if (userExists(username)) {
        return false;
    }

    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, nickname, phone) VALUES (?, ?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(hashedPassword);
    query.addBindValue(nickname);
    query.addBindValue(phone);

    if (!query.exec()) {
        emit databaseError("添加用户失败: " + query.lastError().text());
        return false;
    }

    // 为新用户创建默认分组
    addGroup(username, "默认分组");
    addGroup(username, "好友");
    addGroup(username, "同事");

    return true;
}

bool DataBase::validateUser(const QString &username, const QString &password)
{
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());

    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(hashedPassword);

    if (query.exec() && query.next()) {
        return true;
    }

    return false;
}

bool DataBase::userExists(const QString &username)
{
    qDebug() << "DataBase::userExists - 检查用户名:" << username;
    
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE username = ?");
    query.addBindValue(username);

    if (query.exec() && query.next()) {
        qDebug() << "用户存在";
        return true;
    } else {
        qDebug() << "用户不存在";
        return false;
    }
}

QString DataBase::getUserNickname(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT nickname FROM users WHERE username = ?");
    query.addBindValue(username);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }

    return username; // 如果找不到，返回用户名
}

bool DataBase::addContact(const QString &username, const QString &contactName, const QString &groupName)
{
    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO contacts (username, contact_name, group_name) VALUES (?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(contactName);
    query.addBindValue(groupName);

    if (!query.exec()) {
        emit databaseError("添加联系人失败: " + query.lastError().text());
        return false;
    }

    return true;
}

bool DataBase::removeContact(const QString &username, const QString &contactName)
{
    QSqlQuery query;
    query.prepare("DELETE FROM contacts WHERE username = ? AND contact_name = ?");
    query.addBindValue(username);
    query.addBindValue(contactName);

    if (!query.exec()) {
        emit databaseError("删除联系人失败: " + query.lastError().text());
        return false;
    }

    return true;
}

bool DataBase::contactExists(const QString &username, const QString &contactName)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM contacts WHERE username = ? AND contact_name = ?");
    query.addBindValue(username);
    query.addBindValue(contactName);

    if (query.exec() && query.next()) {
        return true;
    }

    return false;
}

QStringList DataBase::getContacts(const QString &username)
{
    QStringList contacts;
    QSqlQuery query;
    query.prepare("SELECT contact_name FROM contacts WHERE username = ? ORDER BY contact_name");
    query.addBindValue(username);

    if (query.exec()) {
        while (query.next()) {
            contacts.append(query.value(0).toString());
        }
    }

    return contacts;
}

QStringList DataBase::getContactsByGroup(const QString &username, const QString &groupName)
{
    QStringList contacts;
    QSqlQuery query;
    query.prepare("SELECT contact_name FROM contacts WHERE username = ? AND group_name = ? ORDER BY contact_name");
    query.addBindValue(username);
    query.addBindValue(groupName);

    if (query.exec()) {
        while (query.next()) {
            contacts.append(query.value(0).toString());
        }
    }

    return contacts;
}

bool DataBase::addGroup(const QString &username, const QString &groupName)
{
    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO groups (username, group_name) VALUES (?, ?)");
    query.addBindValue(username);
    query.addBindValue(groupName);

    if (!query.exec()) {
        emit databaseError("添加分组失败: " + query.lastError().text());
        return false;
    }

    return true;
}

bool DataBase::removeGroup(const QString &username, const QString &groupName)
{
    if (groupName == "默认分组") {
        return false; // 默认分组不能删除
    }

    QSqlQuery query;
    query.prepare("DELETE FROM groups WHERE username = ? AND group_name = ?");
    query.addBindValue(username);
    query.addBindValue(groupName);

    if (!query.exec()) {
        emit databaseError("删除分组失败: " + query.lastError().text());
        return false;
    }

    // 将该分组下的联系人移动到默认分组
    query.prepare("UPDATE contacts SET group_name = '默认分组' WHERE username = ? AND group_name = ?");
    query.addBindValue(username);
    query.addBindValue(groupName);
    query.exec();

    return true;
}

QStringList DataBase::getGroups(const QString &username)
{
    QStringList groups;
    QSqlQuery query;
    query.prepare("SELECT group_name FROM groups WHERE username = ? OR username = 'system' ORDER BY group_name");
    query.addBindValue(username);

    if (query.exec()) {
        while (query.next()) {
            groups.append(query.value(0).toString());
        }
    }

    return groups;
}

bool DataBase::saveMessage(const QString &sender, const QString &receiver, const QString &content, 
                          const QString &messageType, const QString &timestamp)
{
    QString actualTimestamp = timestamp.isEmpty() ? QDateTime::currentDateTime().toString(Qt::ISODate) : timestamp;

    QSqlQuery query;
    query.prepare("INSERT INTO messages (sender, receiver, content, message_type, timestamp) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(sender);
    query.addBindValue(receiver);
    query.addBindValue(content);
    query.addBindValue(messageType);
    query.addBindValue(actualTimestamp);

    if (!query.exec()) {
        emit databaseError("保存消息失败: " + query.lastError().text());
        return false;
    }

    return true;
}

QJsonArray DataBase::getChatHistory(const QString &user1, const QString &user2, int limit)
{
    QJsonArray messages;
    QSqlQuery query;
    query.prepare("SELECT sender, receiver, content, message_type, timestamp FROM messages "
                  "WHERE (sender = ? AND receiver = ?) OR (sender = ? AND receiver = ?) "
                  "ORDER BY timestamp DESC LIMIT ?");
    query.addBindValue(user1);
    query.addBindValue(user2);
    query.addBindValue(user2);
    query.addBindValue(user1);
    query.addBindValue(limit);

    if (query.exec()) {
        while (query.next()) {
            QJsonObject message;
            message["sender"] = query.value(0).toString();
            message["receiver"] = query.value(1).toString();
            message["content"] = query.value(2).toString();
            message["type"] = query.value(3).toString();
            message["timestamp"] = query.value(4).toString();
            messages.prepend(message); // 按时间升序排列
        }
    }

    return messages;
}

bool DataBase::clearChatHistory(const QString &user1, const QString &user2)
{
    QSqlQuery query;
    query.prepare("DELETE FROM messages WHERE (sender = ? AND receiver = ?) OR (sender = ? AND receiver = ?)");
    query.addBindValue(user1);
    query.addBindValue(user2);
    query.addBindValue(user2);
    query.addBindValue(user1);

    if (!query.exec()) {
        emit databaseError("清空聊天记录失败: " + query.lastError().text());
        return false;
    }

    return true;
}