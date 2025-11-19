#include "replace.h"
#include "ui_replace.h"
#include<QMessageBox>

Replace::Replace(QWidget *parent,QPlainTextEdit*textEdit)
    : QDialog(parent)
    , ui(new Ui::Replace)
{
    ui->setupUi(this);
    pTextEdit=textEdit;

    ui->rbDown->setChecked(true);
}

Replace::~Replace()
{
    delete ui;
}

void Replace::on_btFindnext_clicked()
{
    QString target = ui->searchText->text();
    if (target.isEmpty() || pTextEdit == nullptr)
        return;

    QString text = pTextEdit->toPlainText();
    QTextCursor c = pTextEdit->textCursor();
    int index = -1;


    if (ui->rbUp->isChecked()) {
        index = text.lastIndexOf(target, c.position() - 1,
                                 ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0) {
            c.setPosition(index + target.length());
            c.setPosition(index, QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);
        }
    }

    else if (ui->rbDown->isChecked()) {
        index = text.indexOf(target, c.position(),
                             ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0) {
            c.setPosition(index);
            c.setPosition(index + target.length(), QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);
        }
    }


    if (index < 0) {
        QMessageBox::information(this, "记事本", QString("找不到 '%1'").arg(target));
    }
}



void Replace::on_btCancel_clicked()
{
    accept();
}





void Replace::on_btReplace_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->targetText->text();
    if ((pTextEdit != nullptr )&&( target!="") &&(to!="")){

        QString selText =pTextEdit->textCursor().selectedText();
        if (selText==target)
        {
            pTextEdit->insertPlainText(to);
        }

        on_btFindnext_clicked();
    }
}


void Replace::on_btReplaceAll_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->targetText->text();
    if (pTextEdit == nullptr || target.isEmpty() || to.isEmpty())
        return;

    QString Text = pTextEdit->toPlainText();

    Text.replace(target, to,
                 ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

    pTextEdit->clear();
    pTextEdit->insertPlainText(Text);
}

