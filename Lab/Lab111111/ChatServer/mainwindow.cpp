#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_server(new ChatServer(this))
{
    ui->setupUi(this);
    setWindowTitle("聊天服务器");

    // 绑定日志信号，显示到界面
    connect(m_server, &ChatServer::logMessage, this, [=](const QString &msg){
        ui->logEditer->appendPlainText(QDateTime::currentDateTime().toString("hh:mm:ss") + " " + msg);
    });

    // 自动启动服务器，固定 IP 和端口
    if (!m_server->listen(QHostAddress("127.0.0.1"), 6666)) {
        QMessageBox::critical(this, "错误",
                              "无法启动服务器！\n" + m_server->errorString());
        ui->logEditer->appendPlainText("❌ 无法启动服务器：" + m_server->errorString());
    } else {
        ui->logEditer->appendPlainText("✅ 服务器已启动，监听地址：127.0.0.1:6666");
        qDebug() << "✅ 服务器已启动，监听地址：127.0.0.1:6666";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
