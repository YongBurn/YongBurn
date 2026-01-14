#include <QCoreApplication>
#include <QDebug>
#include <QTest>
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonArray>

#include "database.h"
#include "contactmodel.h"
#include "networkthread.h"

class TestModules : public QObject
{
    Q_OBJECT

private slots:
    void testDatabase();
    void testContactModel();
    void testNetworkThread();
    void testIntegration();

private:
    DataBase *m_database;
    ContactModel *m_contactModel;
    NetworkThread *m_networkThread;
};

void TestModules::testDatabase()
{
    qDebug() << "=== 测试数据库模块 ===";
    
    m_database = new DataBase(this);
    QVERIFY(m_database->isDatabaseReady());
    
    // 测试用户管理
    QString testUser = "test_user";
    QString testPassword = "test_password";
    QString testNickname = "测试用户";
    QString testPhone = "13800138000";
    
    // 清理测试用户
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE username = ?");
    query.addBindValue(testUser);
    query.exec();
    
    // 添加用户
    QVERIFY(m_database->addUser(testUser, testPassword, testNickname, testPhone));
    
    // 验证用户
    QVERIFY(m_database->validateUser(testUser, testPassword));
    QVERIFY(m_database->userExists(testUser));
    QCOMPARE(m_database->getUserNickname(testUser), testNickname);
    
    // 测试联系人管理
    QString contact1 = "contact1";
    QString contact2 = "contact2";
    
    QVERIFY(m_database->addContact(testUser, contact1, "好友"));
    QVERIFY(m_database->addContact(testUser, contact2, "同事"));
    
    QStringList contacts = m_database->getContacts(testUser);
    QCOMPARE(contacts.size(), 2);
    QVERIFY(contacts.contains(contact1));
    QVERIFY(contacts.contains(contact2));
    
    // 测试分组管理
    QVERIFY(m_database->addGroup(testUser, "测试分组"));
    QStringList groups = m_database->getGroups(testUser);
    QVERIFY(groups.contains("测试分组"));
    
    // 测试消息记录
    QVERIFY(m_database->saveMessage(testUser, contact1, "测试消息1", "text"));
    QVERIFY(m_database->saveMessage(contact1, testUser, "测试消息2", "text"));
    
    QJsonArray history = m_database->getChatHistory(testUser, contact1, 10);
    QCOMPARE(history.size(), 2);
    
    qDebug() << "数据库模块测试通过";
}

void TestModules::testContactModel()
{
    qDebug() << "=== 测试联系人模型 ===";
    
    m_contactModel = new ContactModel(this);
    
    // 添加联系人
    Contact contact1;
    contact1.name = "user1";
    contact1.nickname = "用户1";
    contact1.group = "好友";
    contact1.isOnline = true;
    contact1.unreadCount = 0;
    
    Contact contact2;
    contact2.name = "user2";
    contact2.nickname = "用户2";
    contact2.group = "同事";
    contact2.isOnline = false;
    contact2.unreadCount = 3;
    
    m_contactModel->addContact(contact1);
    m_contactModel->addContact(contact2);
    
    QCOMPARE(m_contactModel->rowCount(), 2);
    
    // 测试数据获取
    QModelIndex index1 = m_contactModel->index(0);
    QCOMPARE(m_contactModel->data(index1, ContactModel::NameRole).toString(), QString("user1"));
    QCOMPARE(m_contactModel->data(index1, ContactModel::NicknameRole).toString(), QString("用户1"));
    QCOMPARE(m_contactModel->data(index1, ContactModel::GroupRole).toString(), QString("好友"));
    QCOMPARE(m_contactModel->data(index1, ContactModel::IsOnlineRole).toBool(), true);
    QCOMPARE(m_contactModel->data(index1, ContactModel::UnreadCountRole).toInt(), 0);
    
    // 测试分组筛选
    m_contactModel->filterByGroup("好友");
    QCOMPARE(m_contactModel->rowCount(), 1);
    
    m_contactModel->showAllContacts();
    QCOMPARE(m_contactModel->rowCount(), 2);
    
    // 测试更新
    m_contactModel->setContactOnline("user1", false);
    QModelIndex updatedIndex = m_contactModel->index(0);
    QCOMPARE(m_contactModel->data(updatedIndex, ContactModel::IsOnlineRole).toBool(), false);
    
    m_contactModel->updateUnreadCount("user1", 5);
    QCOMPARE(m_contactModel->data(updatedIndex, ContactModel::UnreadCountRole).toInt(), 5);
    
    qDebug() << "联系人模型测试通过";
}

void TestModules::testNetworkThread()
{
    qDebug() << "=== 测试网络线程 ===";
    
    m_networkThread = new NetworkThread(this);
    
    // 测试连接状态
    QCOMPARE(m_networkThread->isConnected(), false);
    QCOMPARE(m_networkThread->connectionState(), QString("未连接"));
    
    // 测试消息发送（未连接状态）
    QJsonObject testMessage;
    testMessage["type"] = "test";
    testMessage["content"] = "测试消息";
    
    // 这应该不会导致崩溃
    m_networkThread->sendMessage(testMessage);
    
    // 测试心跳发送
    m_networkThread->sendHeartbeat();
    
    qDebug() << "网络线程基础测试通过";
}

void TestModules::testIntegration()
{
    qDebug() << "=== 测试模块集成 ===";
    
    // 测试数据库和联系人模型的集成
    QString testUser = "integration_user";
    QString testContact = "integration_contact";
    
    // 清理测试数据
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE username = ?");
    query.addBindValue(testUser);
    query.exec();
    query.prepare("DELETE FROM users WHERE username = ?");
    query.addBindValue(testContact);
    query.exec();
    
    // 添加测试用户
    QVERIFY(m_database->addUser(testUser, "password", "集成测试用户", ""));
    QVERIFY(m_database->addUser(testContact, "password", "集成测试联系人", ""));
    
    // 添加联系人关系
    QVERIFY(m_database->addContact(testUser, testContact, "测试分组"));
    
    // 保存消息
    QVERIFY(m_database->saveMessage(testUser, testContact, "集成测试消息", "text"));
    
    // 从数据库加载到联系人模型
    QStringList contacts = m_database->getContacts(testUser);
    QCOMPARE(contacts.size(), 1);
    QCOMPARE(contacts.first(), testContact);
    
    // 验证聊天记录
    QJsonArray history = m_database->getChatHistory(testUser, testContact, 10);
    QCOMPARE(history.size(), 1);
    
    QJsonObject message = history.first().toObject();
    QCOMPARE(message["sender"].toString(), testUser);
    QCOMPARE(message["receiver"].toString(), testContact);
    QCOMPARE(message["content"].toString(), QString("集成测试消息"));
    
    qDebug() << "模块集成测试通过";
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    qDebug() << "开始测试Qt聊天应用模块...";
    qDebug() << "测试时间:" << QDateTime::currentDateTime().toString();
    qDebug() << "";
    
    TestModules test;
    
    // 运行所有测试
    test.testDatabase();
    qDebug() << "";
    
    test.testContactModel();
    qDebug() << "";
    
    test.testNetworkThread();
    qDebug() << "";
    
    test.testIntegration();
    qDebug() << "";
    
    qDebug() << "所有模块测试完成！";
    qDebug() << "测试时间:" << QDateTime::currentDateTime().toString();
    
    return 0;
}

#include "test_modules.moc"