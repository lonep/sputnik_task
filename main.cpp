#include <QCoreApplication>
#include <random>

#include "dbmanager.h"

void fillTestTable(DBmanager &db)
{
    std::random_device os_seed;
    const int seed = os_seed();

    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> randomObject(0, INT_MAX);

    for (int i = 0; i < 256; ++i)
        db.insertBlob(randomObject(generator));
    db.insertBlob(15);

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DBmanager db("testDB.db");
//    fillTestTable(db);

    qDebug() << db.isTableContains(15); //test: Number with unique hash, res:TRUE

    qDebug() << db.isTableContains(272371190); //test1: Number with not unique hash, res:TRUE
    qDebug() << db.isTableContains(671164630); //test2: Number with not unique hash, res:TRUE

    qDebug() << db.isTableContains(672985141); //test: Missing number, res:FALSE

    return a.exec();
}
