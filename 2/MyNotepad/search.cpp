#include "search.h"
#include "ui_search.h"
#include<QMessageBox>
search::search(QWidget *parent,QPlainTextEdit *textEdit)
    : QDialog(parent)
    , ui(new Ui::search)
{
    ui->setupUi(this);


    pTextEdit=textEdit;
    ui->rbDown->setChecked(true);

}

search::~search()
{
    delete ui;
}

void search::on_btFindnext_clicked()
{
    QString target = ui->searchText->text();
    if (target.isEmpty() || pTextEdit == nullptr)
        return;

    QString text = pTextEdit->toPlainText();
    QTextCursor c = pTextEdit->textCursor();
    int index = -1;

    // 向上搜索（从当前位置向前找）
    if (ui->rbUp->isChecked()) {
        index = text.lastIndexOf(target, c.position() - 1,  // 起始位置：当前位置-1
                                 ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0) {
            c.setPosition(index + target.length());  // 先定位到结束位置
            c.setPosition(index, QTextCursor::KeepAnchor);  // 锚定到起始位置（反向选中）
            pTextEdit->setTextCursor(c);
        }
    }
    // 向下搜索（从当前位置向后找）
    else if (ui->rbDown->isChecked()) {
        index = text.indexOf(target, c.position(),  // 起始位置：当前位置
                             ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0) {
            c.setPosition(index);  // 先定位到起始位置
            c.setPosition(index + target.length(), QTextCursor::KeepAnchor);  // 锚定到结束位置（正向选中）
            pTextEdit->setTextCursor(c);
        }
    }

    // 未找到目标时提示
    if (index < 0) {
        QMessageBox::information(this, "记事本", QString("找不到 '%1'").arg(target));
    }
}


void search::on_btCancel_clicked()
{
    accept();
}

