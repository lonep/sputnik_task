#ifndef BLOBMANAGER_H
#define BLOBMANAGER_H

#include <QList>

class BlobManager
{
public:

    static int getHash(int number);
    static std::unique_ptr<QList<int>> toIntList(std::unique_ptr<QByteArray> blobByteArray);

    static std::unique_ptr<QByteArray> prepareForBlobInput(std::unique_ptr<QList<int>> blobNumbers, int input);
    static QByteArray prepareForBlobInput(int input);

    static bool checkNumInBlob(std::unique_ptr<QList<int>> blobNumbers, int num);

};

#endif // BLOBMANAGER_H
