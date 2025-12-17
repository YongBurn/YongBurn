#include "idatabase.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QSqlQuery>
#include <QDebug>
#include <QModelIndex>
#include <QSqlRecord> // 确保包含该头文件
#include<QUuid>

void IDatabase::ininDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString aFile = "D:/qt/task/lab4/Lab4a/Lab4a.db";
    database.setDatabaseName(aFile);
    if (!database.open()) {
        qDebug() << "failed to open database";
    } else {
        qDebug() << "open database is ok";
    }
}

bool IDatabase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this, database);
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(
        QSqlTableModel::OnManualSubmit
        );
    patientTabModel->setSort(patientTabModel->fieldIndex("name"), Qt::AscendingOrder);
    if (!(patientTabModel->select()))
        return false;
    thePatientSelection = new QItemSelectionModel(patientTabModel);
    return true;
}

int IDatabase::addNewPatient()
{
    // 关键修改：将QModelIndex()替换为QSqlRecord()（空记录）
    patientTabModel->insertRecord(patientTabModel->rowCount(), QSqlRecord());
    QModelIndex curIndex = patientTabModel->index(patientTabModel->rowCount() - 1, 1);

    int curRecNo=curIndex.row();
    QSqlRecord curRec=patientTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));
    patientTabModel->setRecord(curRecNo,curRec);
    return curIndex.row();
}

bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();
    // 修复：接收removeRow的返回值，并最终返回操作结果
    bool isDeleted = patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();
    patientTabModel->select();
    return isDeleted; // 补充返回值
}

bool IDatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
    patientTabModel->revertAll();
}

QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query;
    query.prepare("select username,password from user where username=:USER");
    query.bindValue(":USER", userName);
    query.exec();
    if (query.first() && query.value("username").isValid()) {
        QString passwd = query.value("password").toString();
        if (passwd == password) {
            qDebug() << "login ok";
            return "logonOk";
        } else {
            return "wrongPassword";
        }
    } else {
        qDebug() << "no such user";
        return "loginFailed";
    }
}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    ininDatabase();
}
