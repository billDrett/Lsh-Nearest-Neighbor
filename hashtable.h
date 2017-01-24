#ifndef Included_HashTable_H
#define Included_HashTable_H

#include "List.h"
#include "Node.h"
#include "hashFunction.h"

template <class T>
class HashTable
{
    private:
        int nBuckets;
        int totalSize;
        List<T>** buckets;
        HashFunction<T>* gFunction;

        unsigned int hashFunction(T key);

    public:
        HashTable(int NBuckets, HashFunction<T>* hashMethod);
        ~HashTable();

        int get_TotalSize();
        int get_nBuckets();
        HashFunction<T>* getHashFunction();

        Node<T>* get_bucket(T key);

        void insertNode(T data);

        bool checkEmpty();
        void printSizeOfBuckets();
};

#endif

