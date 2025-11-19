#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include<QPlainTextEdit>

namespace Ui {
class search;
}

class search : public QDialog
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = nullptr,QPlainTextEdit *textEdit=nullptr);
    ~search();

private slots:
    void on_btFindnext_clicked();

    void on_btCancel_clicked();

private:
    Ui::search *ui;
    QPlainTextEdit *pTextEdit;
};

#endif // SEARCH_H
