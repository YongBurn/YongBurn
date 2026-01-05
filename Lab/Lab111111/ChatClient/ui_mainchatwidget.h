/********************************************************************************
** Form generated from reading UI file 'mainchatwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINCHATWIDGET_H
#define UI_MAINCHATWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QPushButton *MessageList;
    QPushButton *ContactList;
    QSpacerItem *verticalSpacer;
    QListWidget *List;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QListView *ChatView_2;
    QHBoxLayout *horizontalLayout;
    QTextEdit *ChatInput_2;
    QPushButton *Send_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QListWidget *GroupAnnouncements;
    QLabel *label_3;
    QListWidget *GroupMembers;
    QWidget *page_4;
    QLabel *label_6;
    QWidget *page_5;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QListView *ChatView;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *ChatInput;
    QPushButton *Send;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(632, 420);
        horizontalLayout_5 = new QHBoxLayout(Form);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_4 = new QLabel(Form);
        label_4->setObjectName("label_4");

        verticalLayout_3->addWidget(label_4);

        MessageList = new QPushButton(Form);
        MessageList->setObjectName("MessageList");

        verticalLayout_3->addWidget(MessageList);

        ContactList = new QPushButton(Form);
        ContactList->setObjectName("ContactList");

        verticalLayout_3->addWidget(ContactList);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout_3);

        List = new QListWidget(Form);
        List->setObjectName("List");
        List->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(List);

        stackedWidget = new QStackedWidget(Form);
        stackedWidget->setObjectName("stackedWidget");
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        horizontalLayout_2 = new QHBoxLayout(page_3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(page_3);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        ChatView_2 = new QListView(page_3);
        ChatView_2->setObjectName("ChatView_2");

        verticalLayout_2->addWidget(ChatView_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        ChatInput_2 = new QTextEdit(page_3);
        ChatInput_2->setObjectName("ChatInput_2");
        ChatInput_2->setMaximumSize(QSize(16777215, 110));

        horizontalLayout->addWidget(ChatInput_2);

        Send_2 = new QPushButton(page_3);
        Send_2->setObjectName("Send_2");

        horizontalLayout->addWidget(Send_2);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(page_3);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        GroupAnnouncements = new QListWidget(page_3);
        GroupAnnouncements->setObjectName("GroupAnnouncements");
        GroupAnnouncements->setMaximumSize(QSize(80, 150));

        verticalLayout->addWidget(GroupAnnouncements);

        label_3 = new QLabel(page_3);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        GroupMembers = new QListWidget(page_3);
        GroupMembers->setObjectName("GroupMembers");
        GroupMembers->setMaximumSize(QSize(80, 150));

        verticalLayout->addWidget(GroupMembers);


        horizontalLayout_2->addLayout(verticalLayout);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        label_6 = new QLabel(page_4);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(170, 140, 131, 51));
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        verticalLayout_5 = new QVBoxLayout(page_5);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_5 = new QLabel(page_5);
        label_5->setObjectName("label_5");

        verticalLayout_4->addWidget(label_5);

        ChatView = new QListView(page_5);
        ChatView->setObjectName("ChatView");

        verticalLayout_4->addWidget(ChatView);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        ChatInput = new QTextEdit(page_5);
        ChatInput->setObjectName("ChatInput");
        ChatInput->setMaximumSize(QSize(16777215, 110));

        horizontalLayout_3->addWidget(ChatInput);

        Send = new QPushButton(page_5);
        Send->setObjectName("Send");

        horizontalLayout_3->addWidget(Send);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_5->addLayout(verticalLayout_4);

        stackedWidget->addWidget(page_5);

        horizontalLayout_4->addWidget(stackedWidget);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        retranslateUi(Form);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label_4->setText(QCoreApplication::translate("Form", "QQ\345\244\232\344\272\272\345\215\263\346\227\266\351\200\232\344\277\241\347\263\273\347\273\237", nullptr));
        MessageList->setText(QCoreApplication::translate("Form", "\346\266\210\346\201\257", nullptr));
        ContactList->setText(QCoreApplication::translate("Form", "\350\201\224\347\263\273\344\272\272", nullptr));
        label->setText(QCoreApplication::translate("Form", "\345\244\232\344\272\272\350\201\212\345\244\251\347\225\214\351\235\242", nullptr));
        Send_2->setText(QCoreApplication::translate("Form", "\345\217\221\351\200\201", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "\347\276\244\345\205\254\345\221\212", nullptr));
        label_3->setText(QCoreApplication::translate("Form", "\347\276\244\346\210\220\345\221\230", nullptr));
        label_6->setText(QCoreApplication::translate("Form", "\350\257\267\345\274\200\345\247\213\350\201\212\345\244\251", nullptr));
        label_5->setText(QCoreApplication::translate("Form", "\347\247\201\350\201\212\347\225\214\351\235\242", nullptr));
        Send->setText(QCoreApplication::translate("Form", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINCHATWIDGET_H
