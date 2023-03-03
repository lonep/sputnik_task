
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





