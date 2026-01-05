#include "networkmanager.h"
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <QJsonDocument>

NetworkManager* NetworkManager::m_instance = nullptr;

NetworkManager* NetworkManager::instance()
{
    if (!m_instance) {
        m_instance = new NetworkManager();
    }
    return m_instance;
}

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
{
    // 构造函数
}

void NetworkManager::login(const QString &account, const QString &password)
{
    qDebug() << "尝试登录：" << account;

    // 模拟网络延迟
    QTimer::singleShot(1000, this, [=]() {
        // 模拟登录成功
        if (account == "test" && password == "123456") {
            QJsonObject userInfo;
            userInfo["account"] = account;
            userInfo["name"] = "测试用户";
            userInfo["status"] = "online";
            emit loginSuccess(userInfo);
        } else if (account.isEmpty() || password.isEmpty()) {
            emit loginFailed("账号或密码不能为空");
        } else {
            emit loginFailed("账号或密码错误");
        }
    });
}

void NetworkManager::registerUser(const QString &account, const QString &name,
                                  const QString &password, const QString &number)
{
    qDebug() << "尝试注册：" << account << name;

    // 模拟网络延迟
    QTimer::singleShot(1000, this, [=]() {
        if (account.length() >= 6 && password.length() >= 6 &&
            number.length() == 11 && !name.isEmpty()) {
            emit registerSuccess();
        } else {
            emit registerFailed("注册失败，请检查输入信息");
        }
    });
}

void NetworkManager::logout()
{
    qDebug() << "用户退出登录";
}

void NetworkManager::sendGroupMessage(const QString &message)
{
    qDebug() << "发送群消息：" << message;

    // 模拟消息发送
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    emit newGroupMessage("当前用户", message, time);
}

void NetworkManager::sendPrivateMessage(const QString &receiver, const QString &message)
{
    qDebug() << "发送私聊消息给" << receiver << "：" << message;

    // 模拟消息发送
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    emit newPrivateMessage("当前用户", message, time);
}

void NetworkManager::connectToServer()
{
    qDebug() << "连接到服务器";
}

void NetworkManager::disconnectFromServer()
{
    qDebug() << "断开服务器连接";
}
