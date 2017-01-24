#include "hashFunctionMatrix.h"
#include "psedoRandomNumbers.h"
#include <cmath>

HashFunctionMatrix::HashFunctionMatrix(int X1, int X2, double DistX1X2):x1(X1), x2(X2), distX1X2(DistX1X2)
{
}

HashFunctionMatrix::~HashFunctionMatrix()
{
}

bool HashFunctionMatrix::value(MatrixPoint* key)
{
    return (dCalculation(key) >= median);
}

double HashFunctionMatrix::dCalculation(MatrixPoint* key)
{
    return (pow(key->get_distance(x1), 2)+pow(key->get_distance(x2), 2) - pow(distX1X2, 2))/(2*distX1X2); //ypologizei thn timh ths h
}

void HashFunctionMatrix::setMedian(double t1)
{
    median = t1;
}

double median(double* t, int no)
{
    double temp;
    for(int i=0;i<no;i++) //taksinomoume ton pinaka
    {
        for(int j=0;j<no-i;j++)
        {
            if(j!=(no-1)&&t[j]>t[j+1])
            {
                temp=t[j];
                t[j]=t[j+1];
                t[j+1]=temp;
            }
        }
    }

    if(no%2==0) //artios
    {
        return (t[no/2]+t[no/2-1])/2; //pairnoume ta dyo mesaia kai vriskoume mesw oro
    }
    else //perittos
    {
        return t[(no/2)]; //pairnoume to mesaio
    }

}
