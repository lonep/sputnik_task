#include "dbmanager.h"

#include <QSqlQuery>
#include <QCoreApplication>

DBmanager::DBmanager(const QString &dbName, const QString &hostName, const QString &userName, const QString &dbPassword)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(hostName);
    db.setDatabaseName(QString(QCoreApplication::applicationDirPath() + "/" + dbName));
    db.setUserName(userName);
    db.setPassword(dbPassword);

    db.open();
}

void DBmanager::isertInTestTable(int hash, int data)
{
    sqlRequest(QString("INSERT INTO TEST VALUES (%1, %2)").arg(hash).arg(data));
}

QSqlQuery DBmanager::sqlRequest(const QString &request)
{
    QSqlQuery query(request);
    return query;
}





