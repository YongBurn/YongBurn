#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnNam0,SIGNAL(clicked()),this,SLOT(btnNamClicked()));
    connect(ui->btnNam1,SIGNAL(clicked()),this,SLOT(btnNamClicked()));
    connect(ui->btnNam2,SIGNAL(clicked()),this,SLOT(btnNamClicked()));
    connect(ui->btnNam3,SIGNAL(clicked()),this,SLOT(btnNamClicked()));
    connect(ui->btnNam4,SIGNAL(clicked()),this,SLOT(btnNamClicked()));
    connect(ui->btnNam5,SIGNAL(clicked()),this,SLOT(btnNamClicked()));
    connect(ui->btnNam6,SIGNAL(clicked()),this,SLOT(btnNamClicked()));
    connect(ui->btnNam7,SIGNAL(clicked()),this,SLOT(btnNamClicked()));
    connect(ui->btnNam8,SIGNAL(clicked()),this,SLOT(btnNamClicked()));
    connect(ui->btnNam9,SIGNAL(clicked()),this,SLOT(btnNamClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnNamClicked()
{
    QString str=ui->display->text();
    str+=qobject_cast<QPushButton *>(sender())->text();

    ui->display->setText(str);

}

void MainWindow::btnUnaryOperatorClicked()
{

}

void MainWindow::on_btnPoint_clicked()
{
QString str=ui->display->text();
    if(!str.contains("."))
    str+=qobject_cast<QPushButton *>(sender())->text();

     ui->display->setText(str);
}


void MainWindow::on_btnDelete_clicked()
{
     QString str=ui->display->text();
    str=str.left(str.length()-1);
      ui->display->setText(str);
}

