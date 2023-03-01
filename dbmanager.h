#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>

class DBmanager //Using for only SqLite
{
public:
    DBmanager(const QString &dbName, const QString &hostName = "", const QString &userName = "", const QString &dbPassword = "");

    void isertInTestTable(int hash, int data);
    QSqlQuery sqlRequest(const QString &request);
private:
    QSqlDatabase db;

};

#endif // DBMANAGER_H
