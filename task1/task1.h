#ifndef TASK1_H
#define TASK1_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class task1;
}
QT_END_NAMESPACE

class task1 : public QWidget
{
    Q_OBJECT

public:
    task1(QWidget *parent = nullptr);
    ~task1();

private:
    Ui::task1 *ui;
};
#endif // TASK1_H
