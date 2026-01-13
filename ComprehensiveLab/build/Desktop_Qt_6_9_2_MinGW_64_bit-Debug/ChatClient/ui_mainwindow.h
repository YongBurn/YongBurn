/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QLabel *title;
    QStackedWidget *stackedWidget;
    QWidget *chatPage;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout;
    QTextEdit *roomTextEdit;
    QListWidget *userListWidget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *sayLineEdit;
    QPushButton *sayBtn;
    QPushButton *logoutBtn;
    QPushButton *contacts;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QHBoxLayout *horizontalLayout_4;
    QTextEdit *privateTextEdit;
    QListWidget *userListWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *PrivateChatSayLineEdit;
    QPushButton *SendprivateChat;
    QPushButton *PrivateChatreturn;
    QWidget *page_3;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_11;
    QListWidget *Grouping;
    QPushButton *AddGroup;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_12;
    QListWidget *userListWidget_4;
    QPushButton *Addcontact;
    QLabel *label_16;
    QVBoxLayout *verticalLayout_10;
    QSpacerItem *verticalSpacer;
    QPushButton *Return;
    QWidget *loginPage;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *ServerEdit;
    QLineEdit *UserNameEdit;
    QLineEdit *UserPasswordEdit;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QWidget *page;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_5;
    QVBoxLayout *verticalLayout;
    QLineEdit *ServerEdit_2;
    QLineEdit *RegisterUserNameEdit;
    QLineEdit *RegisterUserPasswordEdit;
    QLineEdit *AddressNameEdit;
    QLineEdit *TelephonenumberEdit;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *Register;
    QPushButton *returnButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(895, 546);
        MainWindow->setStyleSheet(QString::fromUtf8("#title {\n"
"    color: white;\n"
"    font-size: 24px;\n"
"    text-align: center;\n"
"    padding: 5px;\n"
"    background: white;\n"
"    border: none;\n"
"	border-bottom: 1px solid black;\n"
"	background-color: #2a5caa;\n"
"}\n"
"\n"
"#nickname {\n"
"    color: white;\n"
"    font-size: 24px;\n"
"    text-align: center;\n"
"    padding: 5px;\n"
"    background: white;\n"
"    border: none;\n"
"	border-bottom: 1px solid black;\n"
"	background-color: #2a5caa;\n"
"}\n"
"\n"
"#loginFrame {\n"
"    background-color: #e6f7ff;\n"
"    border-radius: 20px;\n"
"    padding: 10px;\n"
"    border: 1px solid gray;\n"
"}\n"
"\n"
"#loginButton {\n"
"    background-color: #2a5caa;\n"
"    color: white; /* \347\231\275\350\211\262\346\226\207\345\255\227 */\n"
"    border: 2px solid #000000; /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 6px;\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        title = new QLabel(centralwidget);
        title->setObjectName("title");
        QFont font;
        title->setFont(font);
        title->setStyleSheet(QString::fromUtf8(""));
        title->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(title, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        chatPage = new QWidget();
        chatPage->setObjectName("chatPage");
        verticalLayout_2 = new QVBoxLayout(chatPage);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_10 = new QLabel(chatPage);
        label_10->setObjectName("label_10");

        verticalLayout_2->addWidget(label_10);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        roomTextEdit = new QTextEdit(chatPage);
        roomTextEdit->setObjectName("roomTextEdit");

        horizontalLayout->addWidget(roomTextEdit);

        userListWidget = new QListWidget(chatPage);
        userListWidget->setObjectName("userListWidget");
        userListWidget->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(userListWidget);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        sayLineEdit = new QLineEdit(chatPage);
        sayLineEdit->setObjectName("sayLineEdit");

        horizontalLayout_2->addWidget(sayLineEdit);

        sayBtn = new QPushButton(chatPage);
        sayBtn->setObjectName("sayBtn");

        horizontalLayout_2->addWidget(sayBtn);

        logoutBtn = new QPushButton(chatPage);
        logoutBtn->setObjectName("logoutBtn");

        horizontalLayout_2->addWidget(logoutBtn);

        contacts = new QPushButton(chatPage);
        contacts->setObjectName("contacts");

        horizontalLayout_2->addWidget(contacts);


        verticalLayout_2->addLayout(horizontalLayout_2);

        stackedWidget->addWidget(chatPage);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(page_2);
        label->setObjectName("label");

        verticalLayout_3->addWidget(label);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        privateTextEdit = new QTextEdit(page_2);
        privateTextEdit->setObjectName("privateTextEdit");

        horizontalLayout_4->addWidget(privateTextEdit);

        userListWidget_2 = new QListWidget(page_2);
        userListWidget_2->setObjectName("userListWidget_2");
        userListWidget_2->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_4->addWidget(userListWidget_2);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        PrivateChatSayLineEdit = new QLineEdit(page_2);
        PrivateChatSayLineEdit->setObjectName("PrivateChatSayLineEdit");

        horizontalLayout_3->addWidget(PrivateChatSayLineEdit);

        SendprivateChat = new QPushButton(page_2);
        SendprivateChat->setObjectName("SendprivateChat");

        horizontalLayout_3->addWidget(SendprivateChat);

        PrivateChatreturn = new QPushButton(page_2);
        PrivateChatreturn->setObjectName("PrivateChatreturn");

        horizontalLayout_3->addWidget(PrivateChatreturn);


        verticalLayout_3->addLayout(horizontalLayout_3);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        horizontalLayout_10 = new QHBoxLayout(page_3);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        label_11 = new QLabel(page_3);
        label_11->setObjectName("label_11");

        verticalLayout_8->addWidget(label_11);

        Grouping = new QListWidget(page_3);
        Grouping->setObjectName("Grouping");
        Grouping->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_8->addWidget(Grouping);

        AddGroup = new QPushButton(page_3);
        AddGroup->setObjectName("AddGroup");

        verticalLayout_8->addWidget(AddGroup);


        horizontalLayout_10->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        label_12 = new QLabel(page_3);
        label_12->setObjectName("label_12");

        verticalLayout_9->addWidget(label_12);

        userListWidget_4 = new QListWidget(page_3);
        userListWidget_4->setObjectName("userListWidget_4");
        userListWidget_4->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_9->addWidget(userListWidget_4);

        Addcontact = new QPushButton(page_3);
        Addcontact->setObjectName("Addcontact");

        verticalLayout_9->addWidget(Addcontact);


        horizontalLayout_10->addLayout(verticalLayout_9);

        label_16 = new QLabel(page_3);
        label_16->setObjectName("label_16");

        horizontalLayout_10->addWidget(label_16);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_10->addItem(verticalSpacer);

        Return = new QPushButton(page_3);
        Return->setObjectName("Return");

        verticalLayout_10->addWidget(Return);


        horizontalLayout_10->addLayout(verticalLayout_10);

        stackedWidget->addWidget(page_3);
        loginPage = new QWidget();
        loginPage->setObjectName("loginPage");
        gridLayout = new QGridLayout(loginPage);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_2 = new QLabel(loginPage);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setPointSize(11);
        label_2->setFont(font1);

        verticalLayout_7->addWidget(label_2);

        label_3 = new QLabel(loginPage);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);

        verticalLayout_7->addWidget(label_3);

        label_4 = new QLabel(loginPage);
        label_4->setObjectName("label_4");
        label_4->setFont(font1);

        verticalLayout_7->addWidget(label_4);


        horizontalLayout_7->addLayout(verticalLayout_7);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        ServerEdit = new QLineEdit(loginPage);
        ServerEdit->setObjectName("ServerEdit");

        verticalLayout_6->addWidget(ServerEdit);

        UserNameEdit = new QLineEdit(loginPage);
        UserNameEdit->setObjectName("UserNameEdit");

        verticalLayout_6->addWidget(UserNameEdit);

        UserPasswordEdit = new QLineEdit(loginPage);
        UserPasswordEdit->setObjectName("UserPasswordEdit");

        verticalLayout_6->addWidget(UserPasswordEdit);


        horizontalLayout_7->addLayout(verticalLayout_6);


        gridLayout->addLayout(horizontalLayout_7, 0, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        loginButton = new QPushButton(loginPage);
        loginButton->setObjectName("loginButton");
        loginButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;       /* \346\240\270\345\277\203\357\274\232\346\214\211\351\222\256\350\203\214\346\231\257\350\256\276\344\270\272\347\231\275\350\211\262 */\n"
"    color: #333333;                /* \346\226\207\345\255\227\350\256\276\344\270\272\346\267\261\347\201\260\350\211\262\357\274\214\351\201\277\345\205\215\347\231\275\350\211\262\350\203\214\346\231\257\344\270\213\347\234\213\344\270\215\350\247\201\346\226\207\345\255\227 */\n"
"    border: 1px solid #E5E5E5;     /* \345\212\240\346\265\205\347\201\260\350\211\262\350\276\271\346\241\206\357\274\214\350\256\251\346\214\211\351\222\256\350\275\256\345\273\223\346\233\264\346\270\205\346\231\260 */\n"
"    border-radius: 4px;            /* \345\234\206\350\247\222\346\225\210\346\236\234\357\274\214\344\277\235\346\214\201\347\276\216\350\247\202\357\274\210\344\270\216\344\271\213\345\211\215\346\240\267\345\274\217\344\270\200\350\207\264\357\274\211 */\n"
"    padding: 6px 12px;             /* \345\206\205\350\276"
                        "\271\350\267\235\357\274\214\346\216\247\345\210\266\346\214\211\351\222\256\345\244\247\345\260\217\347\273\237\344\270\200 */\n"
"    font-size: 14px;               /* \345\255\227\344\275\223\345\244\247\345\260\217\347\273\237\344\270\200 */\n"
"    font-weight: 500;              /* \345\255\227\344\275\223\345\212\240\347\262\227\357\274\214\346\217\220\345\215\207\345\217\257\350\257\273\346\200\247 */\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #F8F8F8;     /* hover\346\227\266\350\256\276\344\270\272\346\265\205\347\201\260\350\211\262\357\274\214\345\242\236\345\274\272\344\272\244\344\272\222\345\217\215\351\246\210 */\n"
"    border-color: #165DFF;         /* hover\346\227\266\350\276\271\346\241\206\345\217\230\350\223\235\350\211\262\357\274\214\346\217\220\345\215\207\350\247\206\350\247\211\346\225\210\346\236\234 */\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #F5F5F5;     /* \347\246\201\347\224\250\346\227\266\346\265\205\347\201\260\350\211\262\350\203\214\346\231\257"
                        " */\n"
"    color: #999999;                /* \347\246\201\347\224\250\346\227\266\346\226\207\345\255\227\347\201\260\350\211\262 */\n"
"    border-color: #E5E5E5;\n"
"}"));

        horizontalLayout_8->addWidget(loginButton);

        registerButton = new QPushButton(loginPage);
        registerButton->setObjectName("registerButton");
        registerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;       /* \346\240\270\345\277\203\357\274\232\346\214\211\351\222\256\350\203\214\346\231\257\350\256\276\344\270\272\347\231\275\350\211\262 */\n"
"    color: #333333;                /* \346\226\207\345\255\227\350\256\276\344\270\272\346\267\261\347\201\260\350\211\262\357\274\214\351\201\277\345\205\215\347\231\275\350\211\262\350\203\214\346\231\257\344\270\213\347\234\213\344\270\215\350\247\201\346\226\207\345\255\227 */\n"
"    border: 1px solid #E5E5E5;     /* \345\212\240\346\265\205\347\201\260\350\211\262\350\276\271\346\241\206\357\274\214\350\256\251\346\214\211\351\222\256\350\275\256\345\273\223\346\233\264\346\270\205\346\231\260 */\n"
"    border-radius: 4px;            /* \345\234\206\350\247\222\346\225\210\346\236\234\357\274\214\344\277\235\346\214\201\347\276\216\350\247\202\357\274\210\344\270\216\344\271\213\345\211\215\346\240\267\345\274\217\344\270\200\350\207\264\357\274\211 */\n"
"    padding: 6px 12px;             /* \345\206\205\350\276"
                        "\271\350\267\235\357\274\214\346\216\247\345\210\266\346\214\211\351\222\256\345\244\247\345\260\217\347\273\237\344\270\200 */\n"
"    font-size: 14px;               /* \345\255\227\344\275\223\345\244\247\345\260\217\347\273\237\344\270\200 */\n"
"    font-weight: 500;              /* \345\255\227\344\275\223\345\212\240\347\262\227\357\274\214\346\217\220\345\215\207\345\217\257\350\257\273\346\200\247 */\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #F8F8F8;     /* hover\346\227\266\350\256\276\344\270\272\346\265\205\347\201\260\350\211\262\357\274\214\345\242\236\345\274\272\344\272\244\344\272\222\345\217\215\351\246\210 */\n"
"    border-color: #165DFF;         /* hover\346\227\266\350\276\271\346\241\206\345\217\230\350\223\235\350\211\262\357\274\214\346\217\220\345\215\207\350\247\206\350\247\211\346\225\210\346\236\234 */\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #F5F5F5;     /* \347\246\201\347\224\250\346\227\266\346\265\205\347\201\260\350\211\262\350\203\214\346\231\257"
                        " */\n"
"    color: #999999;                /* \347\246\201\347\224\250\346\227\266\346\226\207\345\255\227\347\201\260\350\211\262 */\n"
"    border-color: #E5E5E5;\n"
"}"));

        horizontalLayout_8->addWidget(registerButton);


        gridLayout->addLayout(horizontalLayout_8, 1, 0, 1, 1);

        stackedWidget->addWidget(loginPage);
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_5 = new QVBoxLayout(page);
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_7 = new QLabel(page);
        label_7->setObjectName("label_7");
        label_7->setFont(font);
        label_7->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black; /* \346\267\261\347\201\260\350\211\262\346\226\207\345\255\227\357\274\214\345\234\250\346\267\241\350\223\235\351\235\242\346\235\277\344\270\212\346\270\205\346\231\260\345\217\257\350\247\201\357\274\210\345\222\214\346\210\252\345\233\276\344\270\200\350\207\264\357\274\211 */\n"
"    font-size: 14px;\n"
"}"));

        verticalLayout_4->addWidget(label_7);

        label_6 = new QLabel(page);
        label_6->setObjectName("label_6");
        label_6->setFont(font1);

        verticalLayout_4->addWidget(label_6);

        label_9 = new QLabel(page);
        label_9->setObjectName("label_9");
        label_9->setFont(font1);

        verticalLayout_4->addWidget(label_9);

        label_8 = new QLabel(page);
        label_8->setObjectName("label_8");
        label_8->setFont(font1);

        verticalLayout_4->addWidget(label_8);

        label_5 = new QLabel(page);
        label_5->setObjectName("label_5");
        label_5->setFont(font1);

        verticalLayout_4->addWidget(label_5);


        horizontalLayout_6->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        ServerEdit_2 = new QLineEdit(page);
        ServerEdit_2->setObjectName("ServerEdit_2");
        ServerEdit_2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;       /* \350\276\223\345\205\245\346\241\206\350\203\214\346\231\257\344\270\272\347\231\275\350\211\262\357\274\214\345\222\214\346\267\241\350\223\235\351\235\242\346\235\277\345\214\272\345\210\206 */\n"
"    border: 1px solid #E0E0E0;     /* \347\273\206\346\265\205\347\201\260\350\276\271\346\241\206\357\274\210\345\222\214\346\210\252\345\233\276\344\270\255\350\276\223\345\205\245\346\241\206\347\232\204\347\273\206\350\276\271\346\241\206\344\270\200\350\207\264\357\274\211 */\n"
"    border-radius: 4px;            /* \350\276\223\345\205\245\346\241\206\345\260\217\345\234\206\350\247\222\357\274\214\351\243\216\346\240\274\347\273\237\344\270\200 */\n"
"    padding: 4px 6px;              /* \350\276\223\345\205\245\346\241\206\345\206\205\350\276\271\350\267\235\357\274\214\346\226\207\345\255\227\344\270\215\350\264\264\350\276\271 */\n"
"    font-size: 14px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #C0C0C0;         /* \350\201\232\347\204\246\346"
                        "\227\266\350\276\271\346\241\206\347\250\215\346\267\261\357\274\214\346\217\220\345\215\207\344\272\244\344\272\222\346\204\237\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"}"));

        verticalLayout->addWidget(ServerEdit_2);

        RegisterUserNameEdit = new QLineEdit(page);
        RegisterUserNameEdit->setObjectName("RegisterUserNameEdit");
        RegisterUserNameEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;       /* \350\276\223\345\205\245\346\241\206\350\203\214\346\231\257\344\270\272\347\231\275\350\211\262\357\274\214\345\222\214\346\267\241\350\223\235\351\235\242\346\235\277\345\214\272\345\210\206 */\n"
"    border: 1px solid #E0E0E0;     /* \347\273\206\346\265\205\347\201\260\350\276\271\346\241\206\357\274\210\345\222\214\346\210\252\345\233\276\344\270\255\350\276\223\345\205\245\346\241\206\347\232\204\347\273\206\350\276\271\346\241\206\344\270\200\350\207\264\357\274\211 */\n"
"    border-radius: 4px;            /* \350\276\223\345\205\245\346\241\206\345\260\217\345\234\206\350\247\222\357\274\214\351\243\216\346\240\274\347\273\237\344\270\200 */\n"
"    padding: 4px 6px;              /* \350\276\223\345\205\245\346\241\206\345\206\205\350\276\271\350\267\235\357\274\214\346\226\207\345\255\227\344\270\215\350\264\264\350\276\271 */\n"
"    font-size: 14px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #C0C0C0;         /* \350\201\232\347\204\246\346"
                        "\227\266\350\276\271\346\241\206\347\250\215\346\267\261\357\274\214\346\217\220\345\215\207\344\272\244\344\272\222\346\204\237\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"}"));

        verticalLayout->addWidget(RegisterUserNameEdit);

        RegisterUserPasswordEdit = new QLineEdit(page);
        RegisterUserPasswordEdit->setObjectName("RegisterUserPasswordEdit");
        RegisterUserPasswordEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;       /* \350\276\223\345\205\245\346\241\206\350\203\214\346\231\257\344\270\272\347\231\275\350\211\262\357\274\214\345\222\214\346\267\241\350\223\235\351\235\242\346\235\277\345\214\272\345\210\206 */\n"
"    border: 1px solid #E0E0E0;     /* \347\273\206\346\265\205\347\201\260\350\276\271\346\241\206\357\274\210\345\222\214\346\210\252\345\233\276\344\270\255\350\276\223\345\205\245\346\241\206\347\232\204\347\273\206\350\276\271\346\241\206\344\270\200\350\207\264\357\274\211 */\n"
"    border-radius: 4px;            /* \350\276\223\345\205\245\346\241\206\345\260\217\345\234\206\350\247\222\357\274\214\351\243\216\346\240\274\347\273\237\344\270\200 */\n"
"    padding: 4px 6px;              /* \350\276\223\345\205\245\346\241\206\345\206\205\350\276\271\350\267\235\357\274\214\346\226\207\345\255\227\344\270\215\350\264\264\350\276\271 */\n"
"    font-size: 14px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #C0C0C0;         /* \350\201\232\347\204\246\346"
                        "\227\266\350\276\271\346\241\206\347\250\215\346\267\261\357\274\214\346\217\220\345\215\207\344\272\244\344\272\222\346\204\237\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"}"));

        verticalLayout->addWidget(RegisterUserPasswordEdit);

        AddressNameEdit = new QLineEdit(page);
        AddressNameEdit->setObjectName("AddressNameEdit");
        AddressNameEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;       /* \350\276\223\345\205\245\346\241\206\350\203\214\346\231\257\344\270\272\347\231\275\350\211\262\357\274\214\345\222\214\346\267\241\350\223\235\351\235\242\346\235\277\345\214\272\345\210\206 */\n"
"    border: 1px solid #E0E0E0;     /* \347\273\206\346\265\205\347\201\260\350\276\271\346\241\206\357\274\210\345\222\214\346\210\252\345\233\276\344\270\255\350\276\223\345\205\245\346\241\206\347\232\204\347\273\206\350\276\271\346\241\206\344\270\200\350\207\264\357\274\211 */\n"
"    border-radius: 4px;            /* \350\276\223\345\205\245\346\241\206\345\260\217\345\234\206\350\247\222\357\274\214\351\243\216\346\240\274\347\273\237\344\270\200 */\n"
"    padding: 4px 6px;              /* \350\276\223\345\205\245\346\241\206\345\206\205\350\276\271\350\267\235\357\274\214\346\226\207\345\255\227\344\270\215\350\264\264\350\276\271 */\n"
"    font-size: 14px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #C0C0C0;         /* \350\201\232\347\204\246\346"
                        "\227\266\350\276\271\346\241\206\347\250\215\346\267\261\357\274\214\346\217\220\345\215\207\344\272\244\344\272\222\346\204\237\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"}"));

        verticalLayout->addWidget(AddressNameEdit);

        TelephonenumberEdit = new QLineEdit(page);
        TelephonenumberEdit->setObjectName("TelephonenumberEdit");
        TelephonenumberEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;       /* \350\276\223\345\205\245\346\241\206\350\203\214\346\231\257\344\270\272\347\231\275\350\211\262\357\274\214\345\222\214\346\267\241\350\223\235\351\235\242\346\235\277\345\214\272\345\210\206 */\n"
"    border: 1px solid #E0E0E0;     /* \347\273\206\346\265\205\347\201\260\350\276\271\346\241\206\357\274\210\345\222\214\346\210\252\345\233\276\344\270\255\350\276\223\345\205\245\346\241\206\347\232\204\347\273\206\350\276\271\346\241\206\344\270\200\350\207\264\357\274\211 */\n"
"    border-radius: 4px;            /* \350\276\223\345\205\245\346\241\206\345\260\217\345\234\206\350\247\222\357\274\214\351\243\216\346\240\274\347\273\237\344\270\200 */\n"
"    padding: 4px 6px;              /* \350\276\223\345\205\245\346\241\206\345\206\205\350\276\271\350\267\235\357\274\214\346\226\207\345\255\227\344\270\215\350\264\264\350\276\271 */\n"
"    font-size: 14px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #C0C0C0;         /* \350\201\232\347\204\246\346"
                        "\227\266\350\276\271\346\241\206\347\250\215\346\267\261\357\274\214\346\217\220\345\215\207\344\272\244\344\272\222\346\204\237\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"}"));

        verticalLayout->addWidget(TelephonenumberEdit);


        horizontalLayout_6->addLayout(verticalLayout);


        verticalLayout_5->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        Register = new QPushButton(page);
        Register->setObjectName("Register");
        Register->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;       /* \346\240\270\345\277\203\357\274\232\346\214\211\351\222\256\350\203\214\346\231\257\350\256\276\344\270\272\347\231\275\350\211\262 */\n"
"    color: #333333;                /* \346\226\207\345\255\227\350\256\276\344\270\272\346\267\261\347\201\260\350\211\262\357\274\214\351\201\277\345\205\215\347\231\275\350\211\262\350\203\214\346\231\257\344\270\213\347\234\213\344\270\215\350\247\201\346\226\207\345\255\227 */\n"
"    border: 1px solid #E5E5E5;     /* \345\212\240\346\265\205\347\201\260\350\211\262\350\276\271\346\241\206\357\274\214\350\256\251\346\214\211\351\222\256\350\275\256\345\273\223\346\233\264\346\270\205\346\231\260 */\n"
"    border-radius: 4px;            /* \345\234\206\350\247\222\346\225\210\346\236\234\357\274\214\344\277\235\346\214\201\347\276\216\350\247\202\357\274\210\344\270\216\344\271\213\345\211\215\346\240\267\345\274\217\344\270\200\350\207\264\357\274\211 */\n"
"    padding: 6px 12px;             /* \345\206\205\350\276"
                        "\271\350\267\235\357\274\214\346\216\247\345\210\266\346\214\211\351\222\256\345\244\247\345\260\217\347\273\237\344\270\200 */\n"
"    font-size: 14px;               /* \345\255\227\344\275\223\345\244\247\345\260\217\347\273\237\344\270\200 */\n"
"    font-weight: 500;              /* \345\255\227\344\275\223\345\212\240\347\262\227\357\274\214\346\217\220\345\215\207\345\217\257\350\257\273\346\200\247 */\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #F8F8F8;     /* hover\346\227\266\350\256\276\344\270\272\346\265\205\347\201\260\350\211\262\357\274\214\345\242\236\345\274\272\344\272\244\344\272\222\345\217\215\351\246\210 */\n"
"    border-color: #165DFF;         /* hover\346\227\266\350\276\271\346\241\206\345\217\230\350\223\235\350\211\262\357\274\214\346\217\220\345\215\207\350\247\206\350\247\211\346\225\210\346\236\234 */\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #F5F5F5;     /* \347\246\201\347\224\250\346\227\266\346\265\205\347\201\260\350\211\262\350\203\214\346\231\257"
                        " */\n"
"    color: #999999;                /* \347\246\201\347\224\250\346\227\266\346\226\207\345\255\227\347\201\260\350\211\262 */\n"
"    border-color: #E5E5E5;\n"
"}"));

        horizontalLayout_5->addWidget(Register);

        returnButton = new QPushButton(page);
        returnButton->setObjectName("returnButton");
        returnButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;       /* \346\240\270\345\277\203\357\274\232\346\214\211\351\222\256\350\203\214\346\231\257\350\256\276\344\270\272\347\231\275\350\211\262 */\n"
"    color: #333333;                /* \346\226\207\345\255\227\350\256\276\344\270\272\346\267\261\347\201\260\350\211\262\357\274\214\351\201\277\345\205\215\347\231\275\350\211\262\350\203\214\346\231\257\344\270\213\347\234\213\344\270\215\350\247\201\346\226\207\345\255\227 */\n"
"    border: 1px solid #E5E5E5;     /* \345\212\240\346\265\205\347\201\260\350\211\262\350\276\271\346\241\206\357\274\214\350\256\251\346\214\211\351\222\256\350\275\256\345\273\223\346\233\264\346\270\205\346\231\260 */\n"
"    border-radius: 4px;            /* \345\234\206\350\247\222\346\225\210\346\236\234\357\274\214\344\277\235\346\214\201\347\276\216\350\247\202\357\274\210\344\270\216\344\271\213\345\211\215\346\240\267\345\274\217\344\270\200\350\207\264\357\274\211 */\n"
"    padding: 6px 12px;             /* \345\206\205\350\276"
                        "\271\350\267\235\357\274\214\346\216\247\345\210\266\346\214\211\351\222\256\345\244\247\345\260\217\347\273\237\344\270\200 */\n"
"    font-size: 14px;               /* \345\255\227\344\275\223\345\244\247\345\260\217\347\273\237\344\270\200 */\n"
"    font-weight: 500;              /* \345\255\227\344\275\223\345\212\240\347\262\227\357\274\214\346\217\220\345\215\207\345\217\257\350\257\273\346\200\247 */\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #F8F8F8;     /* hover\346\227\266\350\256\276\344\270\272\346\265\205\347\201\260\350\211\262\357\274\214\345\242\236\345\274\272\344\272\244\344\272\222\345\217\215\351\246\210 */\n"
"    border-color: #165DFF;         /* hover\346\227\266\350\276\271\346\241\206\345\217\230\350\223\235\350\211\262\357\274\214\346\217\220\345\215\207\350\247\206\350\247\211\346\225\210\346\236\234 */\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #F5F5F5;     /* \347\246\201\347\224\250\346\227\266\346\265\205\347\201\260\350\211\262\350\203\214\346\231\257"
                        " */\n"
"    color: #999999;                /* \347\246\201\347\224\250\346\227\266\346\226\207\345\255\227\347\201\260\350\211\262 */\n"
"    border-color: #E5E5E5;\n"
"}"));

        horizontalLayout_5->addWidget(returnButton);


        verticalLayout_5->addLayout(horizontalLayout_5);

        stackedWidget->addWidget(page);

        gridLayout_2->addWidget(stackedWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\201\212\345\244\251\345\256\244\345\256\242\346\210\267\347\253\257", nullptr));
        title->setText(QCoreApplication::translate("MainWindow", "\345\244\232\344\272\272\345\215\263\346\227\266\351\200\232\350\256\257\347\263\273\347\273\237", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\347\276\244\350\201\212", nullptr));
        sayBtn->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        logoutBtn->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        contacts->setText(QCoreApplication::translate("MainWindow", "\350\201\224\347\263\273\344\272\272", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\247\201\350\201\212", nullptr));
        SendprivateChat->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        PrivateChatreturn->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\350\201\224\347\263\273\344\272\272\345\210\206\347\273\204", nullptr));
        AddGroup->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\210\206\347\273\204", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\346\211\200\345\234\250\347\273\204\347\232\204\350\201\224\347\263\273\344\272\272", nullptr));
        Addcontact->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\350\201\224\347\263\273\344\272\272", nullptr));
        label_16->setText(QString());
        Return->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        ServerEdit->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        UserNameEdit->setText(QString());
        UserPasswordEdit->setText(QString());
        loginButton->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        registerButton->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\347\224\265\350\257\235\345\217\267\347\240\201\357\274\232", nullptr));
        ServerEdit_2->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        RegisterUserNameEdit->setText(QString());
        RegisterUserPasswordEdit->setText(QString());
        AddressNameEdit->setText(QString());
        TelephonenumberEdit->setText(QString());
        Register->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        returnButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
