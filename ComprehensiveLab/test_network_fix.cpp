// 简单的语法测试文件，验证NetworkThread修复后的语法正确性
#include "ChatClient/networkthread.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    // 测试NetworkThread的创建和使用
    NetworkThread networkThread;
    
    // 测试连接方法（不实际连接，只验证语法）
    QObject::connect(&networkThread, &NetworkThread::connected, []() {
        qDebug() << "Connected signal received";
    });
    
    QObject::connect(&networkThread, &NetworkThread::disconnected, []() {
        qDebug() << "Disconnected signal received";
    });
    
    QObject::connect(&networkThread, &NetworkThread::connectionError, [](const QString& error) {
        qDebug() << "Connection error:" << error;
    });
    
    // 验证方法调用语法
    networkThread.isConnected();
    networkThread.connectionState();
    
    qDebug() << "NetworkThread语法测试通过";
    return 0;
}