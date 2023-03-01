#include <QCoreApplication>
#include <random>

#include "dbmanager.h"
#include "qsqlquery.h"

int getTestHash(int number)
{
    return ((number >> 24) & 0xFF) ^ ((number >> 16) & 0xFF) ^ ((number >> 8) & 0xFF) ^ (number & 0xFF);
}

void fillTestTable(DBmanager &db)
{
    std::random_device os_seed;
    const int seed = os_seed();

    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> randomObject(0, INT_MAX);

    int randNumber = 0;

    for (int i = 0; i < 256; ++i)
    {
        randNumber = randomObject(generator);
        db.isertInTestTable(getTestHash(randNumber), randNumber);
    }
}

bool checkNumInTestTable(int number, DBmanager &db)
{
    return db.sqlRequest(QString("SELECT blob_data FROM (SELECT * FROM test WHERE hash = %1) WHERE blob_data = %2").arg(getTestHash(number)).arg(number)).next();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DBmanager db("testDB.db");
//    fillTestTable(db);

    qDebug() << "Is the number 2082706808 in the table?" << checkNumInTestTable(2082706808, db);
    qDebug() << "Is the number 2082706810 in the table?" << checkNumInTestTable(2082706810, db);

    return a.exec();
}
