
#include <QSqlQuery>
#include <QCoreApplication>
#include <QList>
#include <QtEndian>
#include <iterator>
#include <memory>

#include "dbmanager.h"
#include "blobmanager.h"

DBmanager::DBmanager(const QString &dbName, const QString &hostName, const QString &userName, const QString &dbPassword)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(hostName);
    db.setDatabaseName(QString(QCoreApplication::applicationDirPath() + "/" + dbName));
    db.setUserName(userName);
    db.setPassword(dbPassword);

    db.open();
}

DBmanager::~DBmanager()
{
    db.close();
}

void DBmanager::insertBlob(int input)
{
    int hash = BlobManager::getHash(input);

    QSqlQuery req;
    if (!findHash(hash))
    {
        req.prepare(QString("INSERT INTO TEST VALUES (%1, :data)").arg(hash));
        req.bindValue(":data", BlobManager::prepareForBlobInput(input));
        req.exec();
    }
    else
    {
        req.prepare(QString("UPDATE test SET blob_data = :data WHERE hash=%1").arg(hash));
        req.bindValue(":data", *BlobManager::prepareForBlobInput(getListFromBlob(hash), input));
        req.exec();
    }
}

void DBmanager::insertBlob(QList<int> &input)
{
    QSqlQuery insertReq;
    QSqlQuery updateReq;

    insertReq.prepare("INSERT INTO TEST VALUES (:hash, :data)");
    updateReq.prepare("UPDATE test SET blob_data = :data WHERE hash=:hash");

    std::function<void(int, QByteArray, QSqlQuery&)> bindAndExec = [](int hash, QByteArray blob, QSqlQuery &req)
    {
        req.bindValue(":hash", hash);
        req.bindValue(":data", blob);
        req.exec();
    };

    int hash = 0;

    sqlRequest("BEGIN TRANSACTION");
    for (auto it: input)
    {
        hash = BlobManager::getHash(it);

        if (!findHash(hash))
            bindAndExec(hash, BlobManager::prepareForBlobInput(it), insertReq);
        else
            bindAndExec(hash, BlobManager::prepareForBlobInput(it), updateReq);
    }
    sqlRequest("COMMIT");
}



bool DBmanager::isTableContains(int number)
{
   int hash = BlobManager::getHash(number);

   return findHash(hash) ? BlobManager::checkNumInBlob(getListFromBlob(hash), number) : false;
}


QSqlQuery DBmanager::sqlRequest(const QString &request)
{
    return QSqlQuery(request);
}

bool DBmanager::findHash(int hash)
{
    return sqlRequest(QString("SELECT * FROM test WHERE hash = %1").arg(hash)).next();
}

 std::unique_ptr<QByteArray> DBmanager::getByteArrayFromBlob(int hash)
{
    QSqlQuery req = sqlRequest(QString("SELECT blob_data FROM test WHERE hash = %1").arg(hash));

    std::unique_ptr<QByteArray> blob_data (new QByteArray);
    while (req.next())
        *blob_data = req.value(0).toByteArray();

    return blob_data;
}

std::unique_ptr<QList<int>> DBmanager::getListFromBlob(int hash)
{
    return BlobManager::toIntList(getByteArrayFromBlob(hash));
}





