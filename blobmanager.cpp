#include "blobmanager.h"

#include <QtEndian>
#include <algorithm>
#include <QByteArray>

int BlobManager::getHash(int number)
{
 return ((number >> 24) & 0xFF) ^ ((number >> 16) & 0xFF) ^ ((number >> 8) & 0xFF) ^ (number & 0xFF);
}

QList<int> BlobManager::toIntList(QByteArray blobByteArray)
{
    QList <int> data_list;
    int dataSize = 4; //4bytes

    for (int i = 0; i < blobByteArray.size() / dataSize; ++i)
        data_list.push_back(qFromBigEndian<int>(blobByteArray.mid(i * dataSize, i * dataSize + dataSize)));

    return data_list;
}

QByteArray BlobManager::prepareForBlobInput(QList<int> blobNumbers, int input)
{
    auto it = std::upper_bound(blobNumbers.begin(), blobNumbers.end(), input);

    if (it == blobNumbers.end())
        blobNumbers.push_back(input);
    else
        blobNumbers.insert(it, input);

    QByteArray result;
    for (auto it : blobNumbers)
    {
        result.append(prepareForBlobInput(it));
    }

    return result;
}

QByteArray BlobManager::prepareForBlobInput(int input)
{
    QByteArray arr;
    arr.resize(4);

    arr[0] = (input >> 24) & 0xFF;
    arr[1] = (input >> 16) & 0xFF;
    arr[2] = (input >> 8) & 0xFF;
    arr[3] = (input & 0xFF);

    return arr;
}

bool BlobManager::checkNumInBlob(QList<int> blobNumbers, int num)
{
    return std::binary_search(blobNumbers.begin(), blobNumbers.end(), num);
}
