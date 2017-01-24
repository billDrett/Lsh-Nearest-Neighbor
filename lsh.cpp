#include <math.h>
#include <limits>
#include "lsh.h"
#include <ctime>

using namespace std;

//prototypo gia ton constructor ths LSH, ton eidikeuoume gia kathe periptwsh
template <class T>
LSH<T>::LSH(List<T>* Input,  int L1, int K1):L(L1), K(K1)
{

}


template <>
LSH<Hamming*>::LSH(List<Hamming*>* Input, int L1, int K1): L(L1), K(K1)
{
    const int noBuckets = pow(2, K);
    const int noBits = Input->get_begin()->get_data()->get_noBits();
    HashFunction<Hamming*>* hashFunct;

    input = Input;

    hashtables = new HashTable<Hamming*>*[L]; //kataskeuazoume ena pinaka apo listes
    for(int i = 0; i < L; i++) //kataskeuazoume L hashtable
    {
        hashFunct = new HashFunction<Hamming*>(K, noBits); //thn hamming hash function
        hashtables[i] = new HashTable<Hamming*>(noBuckets, hashFunct);
    }
}

template <>
LSH<Vector*>::LSH(List<Vector*>* Input, int L1, int K1):L(L1), K(K1)
{
    const int noBuckets = pow(2, K);
    const int dimensions = Input->get_begin()->get_data()->get_dimensions();
    HashFunction<Vector*>* hashFunct;

    input = Input;

    hashtables = new HashTable<Vector*>*[L]; //kataskeuazoume ena pinaka apo listes
    for(int i = 0; i < L; i++) //kataskeuazoume L hashtable
    {
        hashFunct = new HashFunction<Vector*>(K, dimensions); //thn cosine hash function
        hashtables[i] = new HashTable<Vector*>(noBuckets, hashFunct);
    }

}


template <>
LSH<EuclideanNode*>::LSH(List<EuclideanNode*>* Input, int L1, int K1):L(L1), K(K1)
{
    const int noBuckets = Input->getSize()/8; // n/8, opou n to synolo twn stoixeiwn
    const int dimensions = Input->get_begin()->get_data()->get_vector()->get_dimensions();
    HashFunction<EuclideanNode*>* hashFunct;

    input = Input;

    hashtables = new HashTable<EuclideanNode*>*[L]; //kataskeuazoume ena pinaka apo listes
    for(int i = 0; i < L; i++) //kataskeuazoume L hashtable
    {
        hashFunct = new HashFunction<EuclideanNode*>(K, dimensions, 4, noBuckets); //thn eukleidia hash function
        hashtables[i] = new HashTable<EuclideanNode*>(noBuckets, hashFunct);
    }

    Node<EuclideanNode*>* node = input->get_begin();
    EuclideanNode* tmpNode;
    int sizeList = input->getSize();
    for(int i =0; i <sizeList; i++) //vazoyme kathe stoixeio se ola ta hashtable pou ftiaksame
    {
        for(int j = 0; j < L; j++)
        {
            tmpNode = new EuclideanNode(node->get_data()->get_vector()); //ftiaxnw neo stoixeio giati se kathe table tha exoun diaforetiko ID
            input->insertEnd(tmpNode); //to vazw se lista gia diagrafh argotera

            hashtables[j]->insertNode(tmpNode);
        }
        node=node->get_next();
    }
}

template <>
LSH<MatrixPoint*>::LSH(List<MatrixPoint*>* Input, int L1, int K1):L(L1), K(K1)
{
    const int noBuckets = pow(2, K);
    HashFunction<MatrixPoint*>* hashFunct;

    input = Input;

    hashtables = new HashTable<MatrixPoint*>*[L]; //kataskeuazoume ena pinaka apo listes
    for(int i = 0; i < L; i++) //kataskeuazoume L hashtable
    {
        hashFunct = new HashFunction<MatrixPoint*>(K, input); //thn matrix hash function
        hashtables[i] = new HashTable<MatrixPoint*>(noBuckets, hashFunct);
    }
}

template <class T>
LSH<T>::~LSH()
{
    for(int i =0; i < L; i++)
    {
        delete hashtables[i]->getHashFunction();
        delete hashtables[i];
    }
    delete []hashtables;
}

template<class T>
void LSH<T>::runLSH(std::ofstream& outFile, List<T>* Search, double radius)
{
    double aproxDistance, trueDistance;
    T aproxNear;
    T trueNear;
    List<T>* result= new List<T>();
    clock_t begin, end;
    double LSHTime, BruteTime;

    if(hashtables[0]->checkEmpty()) //an dn exoume eisagei ta dedomena eisodou na ta eisagoume
    {
        for(Node<T>* i = input->get_begin(); i != NULL; i = i->get_next()) //vazoyme kathe stoixeio se ola ta hashtable pou ftiaksame
        {
            for(int j = 0; j < L; j++)
            {
                hashtables[j]->insertNode(i->get_data());
            }
        }
    }

    for(Node<T>* i = Search->get_begin(); i != NULL; i = i->get_next()) //gia kathe simeio sto query list
    {
        rangeSearch(i->get_data(), result, radius); //anazhthsh R geitonwn
        begin = clock();
        aproxDistance = AproxNN(i->get_data(), aproxNear);  //aproximate nearest neighbor
        end = clock();
        LSHTime = (double)(end-begin)/CLOCKS_PER_SEC; //ypologizw ton xrono
        begin = clock();
        trueDistance = TrueNN(i->get_data(), trueNear); //pragmatika kontinoteros
        end = clock();
        BruteTime = (double)(end-begin)/CLOCKS_PER_SEC;

        //grafoume ta apotelesmata sto arxeio
        writeFile(outFile, i->get_data(), result, aproxNear, aproxDistance, trueDistance, LSHTime, BruteTime);

        while(result->deleteFirstNode() != NULL) //adeiazw thn lista gia to epomeno query point
        {
        }
    }

    delete result;
}


template<class T>
double LSH<T>::EuclideanNNTrick(T key, T& aproxNear) //mono prototypo gia thn eukleidia
{
    return-1;
}

template<>
double LSH<EuclideanNode*>::EuclideanNNTrick(EuclideanNode* key, EuclideanNode*& aproxNear)
{
    EuclideanNode* minElement = NULL;
    double minDistance = std::numeric_limits<double>::max();
    double tmpDistance;

    for(int i = 0; i < L; i++)
    {
        for(Node<EuclideanNode*>* j = hashtables[i]->get_bucket(key); j != NULL; j =j->get_next())
        {
            if(j->get_data()->get_ID() != key->get_ID()) continue;

            tmpDistance = distance(j->get_data(), key);
            if(tmpDistance < minDistance)
            {
                minElement = j->get_data();
                minDistance = tmpDistance;
            }
        }
    }

    aproxNear= minElement;
    return minDistance;
}

//allages gia thn periptwsh ths eukleidias
template<>
void LSH<EuclideanNode*>::runLSH(std::ofstream& outFile, List<EuclideanNode*>* Search, double radius)
{
    double aproxDistance, trueDistance;
    EuclideanNode* aproxNear = NULL;
    EuclideanNode* trueNear = NULL;
    List<EuclideanNode*>* result= new List<EuclideanNode*>();
    clock_t begin, end;
    double LSHTime, BruteTime;


    for(Node<EuclideanNode*>* i = Search->get_begin(); i != NULL; i = i->get_next())
    {
        rangeSearch(i->get_data(), result, radius); //anazhthsh R geitonwn

        begin = clock();
        //exw ylopoihsei to trick alla merikes fores dn vriskei ta kalytera apotelesmata opote to vazw san sxolio

        /*aproxDistance = EuclideanNNTrick(i->get_data(), aproxNear);
        if(aproxNear == NULL) //dn vrikame kati me to trick
        {
            aproxDistance = AproxNN(i->get_data(), aproxNear);
        }*/
        aproxDistance = AproxNN(i->get_data(), aproxNear); //ypologizw ton aproximate NN
        end = clock();

        LSHTime = (double)(end-begin)/CLOCKS_PER_SEC;
        begin = clock();
        trueDistance = TrueNN(i->get_data(), trueNear); // ypologizw ton pragrmatika kontinotero
        end = clock();
        BruteTime = (double)(end-begin)/CLOCKS_PER_SEC;

        //grapsimo se arxeio
        writeFile(outFile, i->get_data(), result, aproxNear, aproxDistance, trueDistance, LSHTime, BruteTime);


        while(result->deleteFirstNode() != NULL) //adeiazw thn lista gia to epomeno query point
        {
        }

    }

    delete result;
}

template<class T>
void LSH<T>::writeFile(std::ofstream& outFile, T queryPoint, List<T>* rangeNeigtbours, T aproxVector, double aproxDistance,  double trueDistance, double LSHTime, double bruteTime)
{//grafei sto arxeio thn eksodo tou query point
    outFile << "Query: " << queryPoint->get_string()<<endl;
    outFile << "R-near neighbors:"<<endl;
    for(Node<T>* i = rangeNeigtbours->get_begin(); i != NULL; i = i->get_next())
    {
        outFile<<i->get_data()->get_string()<<endl;
    }

    if(aproxDistance == std::numeric_limits<double>::max()) //dn vrethike
    {
        outFile << "Nearest neighbor: not found"<<endl;
        outFile << "DistanceLSH: not found"<<endl;
    }
    else
    {
        outFile << "Nearest neighbor: "<<aproxVector->get_string()<<endl;
        outFile << "DistanceLSH: "<<aproxDistance<<endl;
    }

    outFile << "DistanceTrue: "<<trueDistance<<endl;
    outFile << "tLSH: "<< LSHTime<<endl;
    outFile << "tTrue: " << bruteTime<<endl;
    outFile<<endl;
}

//vriskei ta simeia pou vriskontai se aktina r
template <class T>
void LSH<T>::rangeSearch(T key, List<T>* result, double radius)
{
    for(int i = 0; i < L; i++)
    {
        for(Node<T>* j = hashtables[i]->get_bucket(key); j != NULL; j =j->get_next())
        {
            if(distance(j->get_data(), key) < radius)
            {
                if(elementExists(result, j->get_data())) continue; //yparxei hdh ara dn to vazw sthn lista
                result->insertEnd(j->get_data());
            }
        }
    }
}


template <class T>
double LSH<T>::TrueNN(T key, T& aproxNear) //brute force gia pragmatika kontinotero
{
    double minDistance = std::numeric_limits<double>::max(); //dinoume thn megalyterh timh pou mporei na parei o double
    double tmpDistance;

    for(Node<T>*i = input->get_begin(); i != NULL; i = i->get_next())
    {
        tmpDistance = distance(i->get_data(), key);

        if(tmpDistance < minDistance)
        {
            minDistance = tmpDistance;
            aproxNear = i->get_data();
        }
    }

    return minDistance;
}

template <class T>
double LSH<T>::AproxNN(T key, T& aproxNear) //epistrefei ton kontinotero symfwna me to lsh
{
    T minElement = 0;
    double minDistance = std::numeric_limits<double>::max();
    double tmpDistance;
    int totalItems = 0;

    for(int i = 0; i < L; i++)
    {
        for(Node<T>* j = hashtables[i]->get_bucket(key); j != NULL; j =j->get_next())
        {

           /* if(totalItems > 3*L) //orio gia to plithos twn elenxwn
            {
                totalItems++;
                aproxNear = minElement;
                delete tmpList;
                return minDistance;
            }*/

            tmpDistance = distance(j->get_data(), key);
            if(tmpDistance < minDistance)
            {
                minElement = j->get_data();
                minDistance = tmpDistance;
            }
        }
    }

    aproxNear= minElement;
    return minDistance;
}


template <class T>
bool LSH<T>::elementExists(List<T>* tmpList, T key) //elenxei an yparxei hdh to stoixeio sthn lista
{
    for(Node<T>* i = tmpList->get_begin(); i!= NULL; i = i->get_next()) //pairnw ta stoixeia pou exoun elengthei
    {
        if(i->get_data()->get_string() == key->get_string())
        {
            return true;
        }
    }

    return false;
}

template<class T>
double LSH<T>::distance(Vector* point1, Vector* point2) //ypologismos apostashs cosine
{
    double innerProduct = 0, lengthPoint1 = 0, lenghtPoint2 =0;

    for(int i =0; i < point1->get_dimensions(); i++)
    {
        innerProduct += point1->get_coordinance(i)*point2->get_coordinance(i); //vriskw eswteriko ginomeno

        lengthPoint1 += pow(point1->get_coordinance(i), 2); //metro tou point1
        lenghtPoint2 += pow(point2->get_coordinance(i), 2); //metro tou point2
    }
   return 1- innerProduct/(sqrt(lengthPoint1) * sqrt(lenghtPoint2));
}

template<class T>
int LSH<T>::distance(Hamming* point1, Hamming* point2) //ypologismos apostashs hamming
{
   	int distance=0;
   	bitset<64> str1;
   	bitset<64> str2;

   	point1->get_bitString(str1);
   	point2->get_bitString(str2);

	for(int i=0;i<point1->get_noBits();i++) //veltiwsh mexri point1 nobits
	{
		if(str1[i]!=str2[i]) //an einai diaforetika +1
		{
			distance++;
		}
	}

	return distance;
}

template<class T>
double LSH<T>::distance(EuclideanNode* point1, EuclideanNode* point2) //ypologismos apostashs gia eukleidia
{
	double sum=0.0;

	for(int i=0;i<point1->get_vector()->get_dimensions();i++)
	{
		sum=sum + pow((point1->get_vector()->get_coordinance(i)-point2->get_vector()->get_coordinance(i)),2.0);
	}

	return sqrt(sum);
}

template<class T>
double LSH<T>::distance(MatrixPoint* point1, MatrixPoint* point2)
{//ypologizw thn apostash apo to querykey sto point1 kai oxi to anapodo giati to point1 dn exei dedomena gia to querykey
    if(point2->get_distance(point1->get_pos())  == 0) return std::numeric_limits<double>::max();

    return point2->get_distance(point1->get_pos());
}

template class LSH<Vector* >;
template class LSH<Hamming* >;
template class LSH<EuclideanNode* >;
template class LSH<MatrixPoint* >;
