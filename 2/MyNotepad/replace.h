#ifndef REPLACE_H
#define REPLACE_H

#include <QDialog>
#include<QPlainTextEdit>

namespace Ui {
class Replace;
}

class Replace : public QDialog
{
    Q_OBJECT

public:
    explicit Replace(QWidget *parent = nullptr,QPlainTextEdit*textEdit=nullptr);
    ~Replace();

private slots:
    void on_btFindnext_clicked();

    void on_btCancel_clicked();

    void on_btReplace_clicked();

    void on_btReplaceAll_clicked();

private:
    Ui::Replace *ui;
    QPlainTextEdit *pTextEdit;
};

#endif // REPLACE_H
