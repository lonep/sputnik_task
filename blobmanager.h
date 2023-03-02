#ifndef BLOBMANAGER_H
#define BLOBMANAGER_H

#include <QList>

class BlobManager
{
public:

    static int getHash(int number);
    static QList<int> toIntList(QByteArray blobByteArray);

    static QByteArray prepareForBlobInput(QList<int> blobNumbers, int input);
    static QByteArray prepareForBlobInput(int input);

    static bool checkNumInBlob(QList<int> blobNumbers, int num);

};

#endif // BLOBMANAGER_H
