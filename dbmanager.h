#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>

class DBmanager //Using for only SqLite
{
public:
    DBmanager(const QString &dbName, const QString &hostName = "", const QString &userName = "", const QString &dbPassword = "");

    std::unique_ptr<QByteArray> getByteArrayFromBlob(int hash);
    std::unique_ptr<QList<int>> getListFromBlob(int hash);

    void insertBlob(int input);
    bool isTableContains(int number);

private:
    QSqlQuery sqlRequest(const QString &request);
    bool findHash(int hash);

    QSqlDatabase db;

};

#endif // DBMANAGER_H
