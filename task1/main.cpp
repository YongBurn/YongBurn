#include "task1.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    task1 w;//定义一个窗口对象
    w.show();//让窗口显示出来
    return a.exec();//应用程序循环
}
