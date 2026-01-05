#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QJsonObject>

// 网络管理器基类，简化版本
class NetworkManager : public QObject
{
    Q_OBJECT
public:
    static NetworkManager* instance();

    // 登录注册
    void login(const QString &account, const QString &password);
    void registerUser(const QString &account, const QString &name,
                      const QString &password, const QString &number);
    void logout();

    // 消息发送
    void sendGroupMessage(const QString &message);
    void sendPrivateMessage(const QString &receiver, const QString &message);

    // 连接管理
    void connectToServer();
    void disconnectFromServer();

signals:
    // 登录注册信号
    void loginSuccess(const QJsonObject &userInfo);
    void loginFailed(const QString &reason);
    void registerSuccess();
    void registerFailed(const QString &reason);

    // 消息信号
    void newGroupMessage(const QString &fromUser, const QString &message, const QString &time);
    void newPrivateMessage(const QString &fromUser, const QString &message, const QString &time);

private:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager() = default;

    static NetworkManager* m_instance;
};

#endif // NETWORKMANAGER_H
