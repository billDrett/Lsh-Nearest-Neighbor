#ifndef Included_HashFunction_H
#define Included_HashFunction_H

#include "dataTypes.h"
#include "euclideanNode.h"
#include <bitset>
#include "List.h"

#include "hashFunctionCosine.h"
#include "psedoRandomNumbers.h"
#include "hashFunctionEuclidean.h"
#include "hashFunctionMatrix.h"

#define M 4294967291 //2^32-5

template<class T> //prototype gia thn hashFunction
class HashFunction
{
    private:

    public:
        HashFunction();
        unsigned int HashFunctionHash(T key); //prepei na pairnei to key kai na epistrefei to bucket

};

template<>
class HashFunction<Vector*>
{
    private:
        const int dimensions;
        const int kHashFunctions;
        HashFunctionCosine** gFunction;


    public:
        HashFunction(int K, int Dimensions);
        ~HashFunction();

        unsigned int HashFunctionHash(Vector* key);
};

template<>
class HashFunction<Hamming*>
{
    private:
        const int kHashFunctions;
        const int noBits;
        int* gFunction;


    public:
        HashFunction(int K, int noBts);
        ~HashFunction();

        unsigned int HashFunctionHash(Hamming* key);
};

template<>
class HashFunction<EuclideanNode*>
{
    private:
        const int dimensions;
        const int kHashFunctions;
        const int nBuckets;
        HashFunctionEuclidean** gFunction;
        int* rVariables;


    public:
        HashFunction(int K, int Dimensions, int W, int noBuckets);
        ~HashFunction();

        unsigned int HashFunctionHash(EuclideanNode* key);

        int hashFunctionID(EuclideanNode* key);
};

template<>
class HashFunction<MatrixPoint*>
{
    private:
        const int kHashFunctions;
        HashFunctionMatrix** gFunction;

        MatrixPoint* getPoint(List<MatrixPoint*>* myList, int pos);

    public:
        HashFunction(int K, List<MatrixPoint*>* myInput);
        ~HashFunction();

        unsigned int HashFunctionHash(MatrixPoint* key);

};

unsigned int modulo(int x1, int x2);
#endif

