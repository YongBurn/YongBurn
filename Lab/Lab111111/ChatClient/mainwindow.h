#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();       // 登录（切换到连接页）
    void on_connectButton_clicked();     // 连接服务器
    void on_sendButton_clicked();        // 发送消息

    void onSocketReadyRead();            // 读取服务器数据
    void onSocketConnected();            // 连接成功
    void onSocketDisconnected();         // 断开连接
    void onSocketError(QAbstractSocket::SocketError error); // 连接错误

private:
    Ui::MainWindow *ui;
    QTcpSocket *m_socket;                // TCP套接字
    QString m_username;                  // 用户名
    void appendMessage(const QString &msg); // 追加聊天消息
};

#endif // MAINWINDOW_H
