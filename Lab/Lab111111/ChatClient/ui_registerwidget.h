/********************************************************************************
** Form generated from reading UI file 'registerwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWIDGET_H
#define UI_REGISTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *AccountEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *NameEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *PasswordEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLineEdit *NumberEdit;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *Return;
    QPushButton *Confirm;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(400, 300);
        verticalLayout_3 = new QVBoxLayout(Form);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(Form);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_3 = new QLabel(Form);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        AccountEdit = new QLineEdit(Form);
        AccountEdit->setObjectName("AccountEdit");

        horizontalLayout->addWidget(AccountEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_4 = new QLabel(Form);
        label_4->setObjectName("label_4");

        horizontalLayout_2->addWidget(label_4);

        NameEdit = new QLineEdit(Form);
        NameEdit->setObjectName("NameEdit");

        horizontalLayout_2->addWidget(NameEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_5 = new QLabel(Form);
        label_5->setObjectName("label_5");

        horizontalLayout_3->addWidget(label_5);

        PasswordEdit = new QLineEdit(Form);
        PasswordEdit->setObjectName("PasswordEdit");

        horizontalLayout_3->addWidget(PasswordEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_6 = new QLabel(Form);
        label_6->setObjectName("label_6");

        horizontalLayout_4->addWidget(label_6);

        NumberEdit = new QLineEdit(Form);
        NumberEdit->setObjectName("NumberEdit");

        horizontalLayout_4->addWidget(NumberEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        Return = new QPushButton(Form);
        Return->setObjectName("Return");

        horizontalLayout_5->addWidget(Return);

        Confirm = new QPushButton(Form);
        Confirm->setObjectName("Confirm");

        horizontalLayout_5->addWidget(Confirm);


        verticalLayout->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label->setText(QCoreApplication::translate("Form", "QQ\345\244\232\344\272\272\345\215\263\346\227\266\351\200\232\344\277\241\347\263\273\347\273\237", nullptr));
        label_3->setText(QCoreApplication::translate("Form", "\350\264\246\345\217\267\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("Form", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("Form", "\345\257\206\347\240\201\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("Form", "\345\217\267\347\240\201\357\274\232", nullptr));
        Return->setText(QCoreApplication::translate("Form", "\350\277\224\345\233\236", nullptr));
        Confirm->setText(QCoreApplication::translate("Form", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWIDGET_H
