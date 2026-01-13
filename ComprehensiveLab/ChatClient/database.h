#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    // 用户管理
    bool addUser(const QString &username, const QString &password, const QString &nickname, const QString &phone);
    bool validateUser(const QString &username, const QString &password);
    bool userExists(const QString &username);
    QString getUserNickname(const QString &username);

    // 联系人管理
    bool addContact(const QString &username, const QString &contactName, const QString &groupName = "默认分组");
    bool removeContact(const QString &username, const QString &contactName);
    bool contactExists(const QString &username, const QString &contactName);
    QStringList getContacts(const QString &username);
    QStringList getContactsByGroup(const QString &username, const QString &groupName);

    // 分组管理
    bool addGroup(const QString &username, const QString &groupName);
    bool removeGroup(const QString &username, const QString &groupName);
    QStringList getGroups(const QString &username);

    // 消息记录
    bool saveMessage(const QString &sender, const QString &receiver, const QString &content, 
                     const QString &messageType = "text", const QString &timestamp = "");
    QJsonArray getChatHistory(const QString &user1, const QString &user2, int limit = 100);
    bool clearChatHistory(const QString &user1, const QString &user2);

    // 数据库初始化
    bool initDatabase();
    bool isDatabaseReady() const { return m_db.isOpen(); }

signals:
    void databaseError(const QString &error);

private:
    QSqlDatabase m_db;
    bool createTables();
    bool executeQuery(const QString &queryStr);
};

#endif // DATABASE_H