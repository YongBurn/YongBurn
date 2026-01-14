#include "ChatClient/database.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    // 创建数据库实例
    DataBase db;
    
    // 测试数据库初始化
    qDebug() << "数据库路径:" << QDir::homePath() + "/.chatapp/chatapp.db";
    
    // 测试用户存在性
    QString testUser = "testuser";
    QString testPassword = "testpass123";
    
    qDebug() << "检查用户是否存在:" << testUser << "-" << db.userExists(testUser);
    
    // 如果用户不存在，尝试添加
    if (!db.userExists(testUser)) {
        bool addResult = db.addUser(testUser, testPassword, "测试用户", "123456789");
        qDebug() << "添加用户结果:" << addResult;
    }
    
    // 测试用户验证
    bool validateResult = db.validateUser(testUser, testPassword);
    qDebug() << "用户验证结果:" << validateResult;
    
    // 测试错误密码
    bool wrongPassResult = db.validateUser(testUser, "wrongpassword");
    qDebug() << "错误密码验证结果:" << wrongPassResult;
    
    // 检查数据库中的用户
    qDebug() << "测试完成";
    
    return 0;
}