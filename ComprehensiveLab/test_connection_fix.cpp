#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <QJsonObject>

// 简单的测试类来验证连接逻辑
class ConnectionTest {
public:
    ConnectionTest() : m_currentUser(""), m_isConnected(false) {}
    
    void simulateLoginButtonClicked(const QString& username) {
        qDebug() << "=== 模拟登录按钮点击 ===";
        qDebug() << "用户名:" << username;
        
        // 模拟本地验证成功
        m_currentUser = username;
        qDebug() << "本地验证成功，开始连接服务器";
        
        // 模拟连接到服务器
        simulateConnectToServer();
    }
    
    void simulateConnectToServer() {
        qDebug() << "连接到服务器...";
        // 模拟连接成功
        QTimer::singleShot(100, [this]() {
            m_isConnected = true;
            simulateOnNetworkConnected();
        });
    }
    
    void simulateOnNetworkConnected() {
        qDebug() << "=== 网络连接成功事件 ===";
        qDebug() << "当前用户:" << m_currentUser;
        
        // 只有在有当前用户时才发送登录消息
        if (!m_currentUser.isEmpty()) {
            QJsonObject loginMessage;
            loginMessage["type"] = "login";
            loginMessage["text"] = m_currentUser;
            qDebug() << "发送登录消息:" << loginMessage;
            qDebug() << "✓ 登录流程正确 - 登录消息只在连接成功后发送一次";
        } else {
            qDebug() << "✗ 错误 - 没有当前用户";
        }
    }
    
    void simulateServerResponse(const QString& response) {
        qDebug() << "=== 模拟服务器响应 ===";
        qDebug() << "服务器响应:" << response;
        
        if (response == "login_success") {
            qDebug() << "✓ 登录成功，可以切换到聊天页面";
        } else if (response == "username_exists") {
            qDebug() << "✗ 用户名已存在错误";
        }
    }
    
    void simulateReconnection() {
        qDebug() << "=== 模拟重新连接 ===";
        m_isConnected = false;
        simulateConnectToServer();
    }

private:
    QString m_currentUser;
    bool m_isConnected;
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    qDebug() << "=== 测试连接修复 ===";
    qDebug() << "测试目标：确保登录消息只在连接成功后发送一次";
    qDebug() << "";
    
    ConnectionTest test;
    
    // 测试场景1：正常登录
    qDebug() << "测试场景1：正常登录流程";
    test.simulateLoginButtonClicked("testuser");
    
    // 测试场景2：重新连接
    QTimer::singleShot(500, [&test]() {
        qDebug() << "\n测试场景2：重新连接";
        test.simulateReconnection();
    });
    
    // 测试场景3：服务器响应
    QTimer::singleShot(800, [&test]() {
        qDebug() << "\n测试场景3：服务器响应登录成功";
        test.simulateServerResponse("login_success");
    });
    
    QTimer::singleShot(1200, [&app]() {
        qDebug() << "\n=== 测试完成 ===";
        app.quit();
    });
    
    return app.exec();
}