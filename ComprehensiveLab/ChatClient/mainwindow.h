#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "chatclient.h"
#include "database.h"
#include "contactmodel.h"
#include "networkthread.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 登录注册
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void on_returnButton_clicked();
    void on_Register_clicked();
    void on_logoutBtn_clicked();
    
    // 聊天功能
    void on_sayBtn_clicked();
    void on_SendprivateChat_clicked();
    void on_PrivateChatreturn_clicked();
    
    // 联系人管理
    void on_contacts_clicked();
    void on_AddGroup_clicked();
    void on_Addcontact_clicked();
    void on_Return_clicked();
    void on_userListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_userListWidget_2_itemDoubleClicked(QListWidgetItem *item);
    void on_userListWidget_4_itemDoubleClicked(QListWidgetItem *item);
    void on_Grouping_itemClicked(QListWidgetItem *item);

    // 网络通信
    void connectedToServer();
    void disconnectedFromServer();
    void messageReceived(const QString &sender,const QString &text);
    void jsonReceived(const QJsonObject &docObj);
    void userJoined(const QString &user);
    void userLeft(const QString &user);
    void userListReceived(const QStringList &list);
    void displayPrivateMessage(const QString &sender, const QString &text,const QString &timestamp, bool isSentByMe);
    
    // 网络线程信号
    void onNetworkConnected();
    void onNetworkDisconnected();
    void onNetworkError(const QString &error);
    void onNetworkMessageReceived(const QJsonObject &message);
    void onReconnectionAttempt(int attempt);

    // 数据库操作
    void loadLocalData();
    void saveMessageToLocal(const QString &sender, const QString &receiver, const QString &content, const QString &type);
    void loadChatHistory(const QString &contact);

    // UI更新
    void updateConnectionStatus();
    void updateContactList();
    void updateGroupList();
    void syncPrivateChatUserList();

private:
    Ui::MainWindow *ui;

    ChatClient *m_chatClient;
    DataBase *m_database;
    ContactModel *m_contactModel;
    NetworkThread *m_networkThread;
    
    QString m_currentUser;
    QString m_currentContact;
    QString m_currentGroup;
    
    QTimer *m_statusUpdateTimer;
    
    void setupConnections();
    void setupModels();
    void switchToChatPage();
    void switchToPrivateChat(const QString &contact);
    void switchToContactsPage();
    void switchToLoginPage();
    
    bool validateLoginInput();
    bool validateRegisterInput();
    
    void loadContactsFromDatabase();
    void loadGroupsFromDatabase();
    void addContactToList(const QString &contact, const QString &group = "默认分组");
    
    void updateUserListWidget();
    void updatePrivateChatWidget();
    
    QString getCurrentTimestamp() const;
};

#endif // MAINWINDOW_H
