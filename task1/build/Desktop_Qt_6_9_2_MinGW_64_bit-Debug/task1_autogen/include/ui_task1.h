/********************************************************************************
** Form generated from reading UI file 'task1.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK1_H
#define UI_TASK1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_task1
{
public:
    QLabel *label;

    void setupUi(QWidget *task1)
    {
        if (task1->objectName().isEmpty())
            task1->setObjectName("task1");
        task1->resize(800, 600);
        label = new QLabel(task1);
        label->setObjectName("label");
        label->setGeometry(QRect(200, 30, 221, 131));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        label->setFont(font);

        retranslateUi(task1);

        QMetaObject::connectSlotsByName(task1);
    } // setupUi

    void retranslateUi(QWidget *task1)
    {
        task1->setWindowTitle(QCoreApplication::translate("task1", "task1", nullptr));
        label->setText(QCoreApplication::translate("task1", "Hello World", nullptr));
    } // retranslateUi

};

namespace Ui {
    class task1: public Ui_task1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK1_H
