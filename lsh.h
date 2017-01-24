#ifndef Included_Lsh_H
#define Included_Lsh_H

#include <fstream>
#include "dataTypes.h"
#include "List.h"
#include "hashtable.h"

template<class T>
class LSH
{
    private:
        const int L;
        const int K;

        HashTable<T>** hashtables;
        List<T>* input;

        bool elementExists(List<T>* tmpList, T key);
        double EuclideanNNTrick(T key, T& aproxNear);

    public:
        LSH(List<T>* Input, int L1, int K1);
        ~LSH();

        void runLSH(std::ofstream& outFile, List<T>* Search, double radius);
        void writeFile(std::ofstream& outFile, T queryPoint, List<T>* rangeNeigtbours, T aproxVector, double aproxDistance,  double trueDistance, double LSHTime, double bruteTime);
        void rangeSearch(T key, List<T>* result, double radius);
        double AproxNN(T key, T& aproxNear);
        double TrueNN(T key, T& aproxNear);

        double distance(Vector* point1, Vector* point2);
        int distance(Hamming* point1, Hamming* point2);
        double distance(EuclideanNode* point1, EuclideanNode* point2);
        double distance(MatrixPoint* point1, MatrixPoint* point2);


};

#endif
