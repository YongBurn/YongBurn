#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_socket(new QTcpSocket(this))
{
    ui->setupUi(this);
    setWindowTitle("聊天客户端");

    // 修正1：QT6中使用errorOccurred信号（替代旧的error信号），解决QOverload匹配失败
    connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::onSocketReadyRead);
    connect(m_socket, &QTcpSocket::connected, this, &MainWindow::onSocketConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &MainWindow::onSocketDisconnected);
    // 两种写法均可：1. 直接绑定errorOccurred  2. QOverload（兼容写法）
    connect(m_socket, &QTcpSocket::errorOccurred, this, &MainWindow::onSocketError);
    // 若坚持用QOverload，写法如下（二选一即可）：
    // connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
    //         this, &MainWindow::onSocketError);

    // 修正2：UI控件名称适配（替换为你UI文件中实际存在的控件名）
    // 原chatTextEdit → 改为textEdit
    ui->textEdit->setReadOnly(true);
    // 原messageLineEdit → 改为lineEdit（若有多个lineEdit，可根据UI调整为lineEdit_2等）
    ui->loginUserLineEdit->setEnabled(false);
    // 原sendButton → 改为pushButton（若有多个pushButton，可调整为pushButton_3等）
    ui->pushButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    // 修正2：原userLineEdit → 改为lineEdit（UI实际控件名）
    m_username = ui->loginUserLineEdit->text().trimmed();
    if (m_username.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入用户名！");
        return;
    }
    // 若UI中有stackedWidget则保留，无则注释（根据你的UI调整）
    if (ui->stackedWidget) {
        ui->stackedWidget->setCurrentIndex(1); // 切换到连接页
    }
}

void MainWindow::on_connectButton_clicked()
{
    m_socket->connectToHost("127.0.0.1", 6666);
    appendMessage("正在连接服务器...");
}

void MainWindow::on_sendButton_clicked()
{
    // 修正2：原messageLineEdit → 改为lineEdit
    QString text = ui->loginUserLineEdit->text().trimmed();
    if (text.isEmpty()) return;

    // 构造JSON消息
    QJsonObject msg;
    msg["type"] = "message";
    msg["content"] = text;
    QByteArray data = QJsonDocument(msg).toJson(QJsonDocument::Compact) + '\n';
    m_socket->write(data);

    // 显示自己发送的消息
    QString localMsg = "[我] " + text;
    appendMessage(localMsg);

    ui->loginUserLineEdit->clear();
}

void MainWindow::onSocketReadyRead()
{
    while (m_socket->canReadLine()) {
        QByteArray line = m_socket->readLine().trimmed();
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(line, &error);
        if (error.error != QJsonParseError::NoError || !doc.isObject()) continue;

        QJsonObject obj = doc.object();
        QString type = obj["type"].toString();

        if (type == "notification") {
            appendMessage("📢 " + obj["message"].toString());
        } else if (type == "message") {
            QString from = obj["from"].toString();
            QString content = obj["content"].toString();
            if (from != m_username) {
                appendMessage("[" + from + "] " + content);
            }
        }
    }
}

void MainWindow::onSocketConnected()
{
    appendMessage("✅ 已连接到服务器");

    // 发送登录请求
    QJsonObject login;
    login["type"] = "login";
    login["username"] = m_username;
    m_socket->write(QJsonDocument(login).toJson(QJsonDocument::Compact) + '\n');

    // 修正2：UI控件名称适配
    ui->loginUserLineEdit->setEnabled(true);
    ui->pushButton->setEnabled(true);
    // 若UI中有stackedWidget则保留，无则注释
    if (ui->stackedWidget) {
        ui->stackedWidget->setCurrentIndex(2); // 切换到聊天界面
    }
}

void MainWindow::onSocketDisconnected()
{
    appendMessage("❌ 与服务器断开连接");
    // 修正2：UI控件名称适配
    ui->loginUserLineEdit->setEnabled(false);
    ui->pushButton->setEnabled(false);
}

void MainWindow::onSocketError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);
    appendMessage("⚠️ 连接错误: " + m_socket->errorString());
}

void MainWindow::appendMessage(const QString &msg)
{
    // 修正2：原chatTextEdit → 改为textEdit
    ui->textEdit->append(QDateTime::currentDateTime().toString("hh:mm:ss") + " " + msg);
}
