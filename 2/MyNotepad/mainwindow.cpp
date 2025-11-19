#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include "search.h"
#include"replace.h"
#include<QFileDialog>
#include<QMessageBox>
#include<QTextStream>
#include<QColorDialog>
#include<QFontDialog>
#include"codeeditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TextChanged=false;
    on_actionNew_triggered();

    statuslabel.setMaximumWidth(180);
    statuslabel.setText("length:"+QString::number(0)+" lines: "+QString::number(1));
    ui->statusbar->addPermanentWidget(&statuslabel);

    statusCursorLabel.setMaximumWidth(180);
    statusCursorLabel.setText("ln:"+QString::number(0)+" col: "+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author=new QLabel(ui->statusbar);
    author->setText(tr("刘东波"));
    ui->statusbar->addPermanentWidget(author);

    ui->actionCopy->setEnabled(false);
     ui->actionRecovery->setEnabled(false);
     ui->actionUndo->setEnabled(false);
      ui->actionCut->setEnabled(false);
      ui->actionPaste->setEnabled(false);

      QPlainTextEdit::LineWrapMode mode=ui->TextEdit->lineWrapMode();

      if(mode==QTextEdit::NoWrap){
          ui->TextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
          ui->actionSelfWrap->setChecked(false);
      }else{
          ui->TextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
          ui->actionSelfWrap->setChecked(true);
      }

      ui->actionStatusbar->setChecked(true);
      ui->actionToolbar->setChecked(true);
      ui->actionRehearsal->setChecked(false);
      on_actionRehearsal_triggered(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    About dlg;
    dlg.exec();
}


void MainWindow::on_actionFind_triggered()
{
    search dlg(this,ui->TextEdit);
    dlg.exec();
}


void MainWindow::on_actionReplace_triggered()
{
    Replace dlg(this,ui->TextEdit);
    dlg.exec();
}


void MainWindow::on_actionNew_triggered()
{    if(!userEditConfirmed())
        return;
    filePath="";
    ui->TextEdit->clear();
    this->setWindowTitle(tr("新建文本文件 —— 编辑器"));
    TextChanged=false;
}


void MainWindow::on_actionOpen_triggered()
{
    if(!userEditConfirmed())
        return;
    QString filename=QFileDialog::getOpenFileName(this,"打开文件",".",tr("Text files(*.txt);;ALL(*.*)"));
    QFile file(filename);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"..","打开文件失败");
        return;
    }

    filePath=filename;
    QTextStream in(&file);
    QString text=in.readAll();
    ui->TextEdit->insertPlainText(text);
    file.close();

    this->setWindowTitle(QFileInfo(filename).absoluteFilePath());
    TextChanged=false;
}


void MainWindow::on_actionSave_triggered()
{

    if(filePath==""){
        QString filename=QFileDialog::getSaveFileName(this,"保存文件",".",tr("Text files(*.text)"));
        QFile file(filename);
        if(!file.open(QFile::WriteOnly|QFile::Text)){
            QMessageBox::warning(this,"..","保存文件失败");
            return;
        }
        file.close();
        filePath=filename;
    }

    QFile file(filePath);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"..","保存文件失败");
        return;
    }
    QTextStream out(&file);
    QString text=ui->TextEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());

    TextChanged=false;
}


void MainWindow::on_actionSaveAs_triggered()
{        QString filename=QFileDialog::getSaveFileName(this,"保存文件",".",tr("Text files(*.text)"));
    QFile file(filename);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"..","保存文件失败");
        return;
    }
 filePath=filename;
    QTextStream out(&file);
    QString text=ui->TextEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());
}


void MainWindow::on_TextEdit_textChanged()
{
    if(!TextChanged){
        this->setWindowTitle("*"+this->windowTitle());
        TextChanged=true;
    }
    statuslabel.setText("length:"+QString::number(ui->TextEdit->toPlainText().length())+" lines:"+QString::number(ui->TextEdit->document()->lineCount()));
}

bool MainWindow::userEditConfirmed()
{
    if(TextChanged){
        QString path=(filePath!="")?filePath:"无标题.txt";
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("...");
            msg.setWindowFlag(Qt::Drawer);
        msg.setText(QString("是否将更改保存到\n")+"\""+path+"\"?");
            msg.setStandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        int r=msg.exec();
            switch(r){
        case QMessageBox::Yes:
                on_actionSave_triggered();
            break;
        case QMessageBox::No:
            TextChanged=false;
            break;
        case QMessageBox::Cancel:
            return false;
            }
    }
    return true;

}


void MainWindow::on_actionUndo_triggered()
{
    ui->TextEdit->undo();
}


void MainWindow::on_actionCut_triggered()
{
    ui->TextEdit->cut();
     ui->actionPaste->setEnabled(true);
}


void MainWindow::on_actionCopy_triggered()
{
    ui->TextEdit->copy();
    ui->actionPaste->setEnabled(true);
}


void MainWindow::on_actionPaste_triggered()
{
    ui->TextEdit->paste();
}


void MainWindow::on_actionRecovery_triggered()
{
    ui->TextEdit->redo();
}


void MainWindow::on_TextEdit_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);
}


void MainWindow::on_TextEdit_redoAvailable(bool b)
{
    ui->actionRecovery->setEnabled(b);
}


void MainWindow::on_TextEdit_undoAvailable(bool b)
{
    ui->actionUndo->setEnabled(b);
}


void MainWindow::on_actionFont_triggered()
{
    bool ok=false;
    QFont font=QFontDialog::getFont(&ok,this);
    if(ok)
        ui->TextEdit->setFont(font);
}


void MainWindow::on_actionColor_triggered()
{
    QColor color=QColorDialog::getColor(Qt::black,this,"选择颜色");
    if(color.isValid()){
        ui->TextEdit->setStyleSheet(QString("QPlainTextEdit{color:%1}").arg(color.name()));
    }
}


void MainWindow::on_actionBackgroundColor_triggered()
{
    QColor color=QColorDialog::getColor(Qt::black,this,"选择颜色");
    if(color.isValid()){
        ui->TextEdit->setStyleSheet(QString("QPlainTextEdit{background-color:%1}").arg(color.name()));
    }
}


void MainWindow::on_actionCompilerColor_triggered()
{

}


void MainWindow::on_actionSelfWrap_triggered()
{
    QPlainTextEdit::LineWrapMode mode=ui->TextEdit->lineWrapMode();
    if(mode==QTextEdit::NoWrap){
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actionSelfWrap->setChecked(true);
    }else{
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionSelfWrap->setChecked(false);
    }
}


void MainWindow::on_actionToolbar_triggered()
{
    bool visible=ui->toolBar->isVisible();
    ui->toolBar->setVisible(!visible);
    ui->actionToolbar->setChecked(!visible);
}


void MainWindow::on_actionStatusbar_triggered()
{
    bool visible=ui->statusbar->isVisible();
    ui->statusbar->setVisible(!visible);
    ui->actionStatusbar->setChecked(!visible);
}


void MainWindow::on_actionSelectAll_triggered()
{
    ui->TextEdit->selectAll();
}


void MainWindow::on_actionExit_triggered()
{
    if(userEditConfirmed())
        exit(0);
}


void MainWindow::on_TextEdit_cursorPositionChanged()
{
    int col=0;
    int In=0;
    int flg=-1;
    int pos=ui->TextEdit->textCursor().position();
    QString text=ui->TextEdit->toPlainText();
    for(int i=0;i<pos;i++){
        if(text[i]=='\n'){
            In++;
            flg=i;
        }
    }
    flg++;
    col=pos-flg;
    statuslabel.setText("length:"+QString::number(In+1)+" lines: "+QString::number(col+1));
}


void MainWindow::on_actionRehearsal_triggered(bool checked)
{
    ui->TextEdit->hideLineNumberArea(!checked);
}

