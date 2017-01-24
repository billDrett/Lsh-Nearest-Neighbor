#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "lsh.h"
#include "readFile.h"
#include "List.h"
#include "dataTypes.h"
#include "euclideanNode.h"

using namespace std;


int main(int argc, char *argv[])
{
    ifstream inFile;
    ifstream queryFile;
    ofstream outFile;
    string inputFile="", searchFile="", outputFile = "";
    string type;
    double radius;
    int L = 5, K = 4;
    Hamming* tmpHamming;
    Vector* tmpVector;
    MatrixPoint* tmpMatrix;
    List<Vector*>* myList1;
    List<Hamming*>* myList2;
    List<MatrixPoint*>* myList3;

    initialize(); //arxikopoiei thn srand

    if (argc < 7 || argc > 11)
    {
        cout<<"Please give all attributes –d <input file> –q <query file> –k <int> -L <int> -ο <output file>"<<endl;
        exit(1);
    }

    for(int i=1; i < argc; i++)
    {
        if(i+1 != argc) // an dn einai to teleutaio
        {
            if(strcmp(argv[i], "-d") == 0)
            {
                inputFile = argv[i+1];
            }
            else if(strcmp(argv[i], "-q") == 0)
            {
                searchFile = argv[i+1];
            }
            else if(strcmp(argv[i], "-k") == 0)
            {
                K = atoi(argv[i+1]);
            }
            else if(strcmp(argv[i], "-L") == 0)
            {
                L = atoi(argv[i+1]);
            }
            else if(strcmp(argv[i], "-o") == 0)
            {
                outputFile = argv[i+1];
            }
        }
    }
    if(inputFile == ""|| searchFile==""||outFile=="")
    {
        perror("Arguments dont match");
        exit(2);
    }

    if(K>32)
    {
        perror("support up to 32 bits and 2^32 buckets");
        exit(2);
    }
    inFile.open(inputFile.c_str());
    queryFile.open(searchFile.c_str());
    outFile.open(outputFile.c_str());

    if(inFile.is_open() == false || queryFile.is_open() == false ||outFile.is_open()==false)
    {
        perror("Cant open files");
        exit(3);
    }

    myList1 = new List<Vector*>();
    myList2 = new List<Hamming*>();
    myList3 = new List<MatrixPoint*>();

    if(readFile(inFile, type, myList1, myList2, myList3)) //diavazoume to arxeio kai to vazoume sthn lista
    {
        perror("Error data of files");
        exit(4);
    }

    if(type =="hamming") //ta dedomena einai hamming
    {
        cout<<"hamming"<<endl;
        LSH<Hamming*>* lsh = new LSH<Hamming*>(myList2,  L, K);
        List<Hamming*>* queryList = new List<Hamming*>();
        Hamming* tmp;

        do
        {
            readRadius(queryFile, radius); //diavazoume aktina
            readHammingFile(queryFile, queryList); //kai queryFile

            lsh->runLSH(outFile, queryList, radius); //trexoume ton lsh

            while((tmp = queryList->deleteFirstNode()) != NULL) //svinoume ta query points gia na dextoume ta epomena
            {
                delete tmp;
            }

            cout<<"Input next query file or end to stop"<<endl;
            cin >> searchFile; //diavazw onoma arxeiou
            if(searchFile != "end")
            {
                queryFile.close();
                queryFile.open(searchFile.c_str());
                if(queryFile.is_open()==false) //an dn ypaxxei stamataw
                {
                    perror("Query file doesnt exists");
                    exit(3);
                }
            }

        }while(searchFile != "end"); //diavazoume neo query file


        while((tmpHamming = myList2->deleteFirstNode()) != NULL) //diagrafw thn lista eisodou
        {
            delete tmpHamming;
        }

        delete lsh;
        delete queryList;
    }
    else if(type == "cosine")
    {
        cout<<"cosine"<<endl;
        string line = "";
        LSH<Vector*>* lsh = new LSH<Vector*>(myList1,  L, K);
        List<Vector*>* queryList = new List<Vector*>();
        Vector* tmp;


        do
        {

            readRadius(queryFile, radius); //diavazoume aktina kai dedomena
            readVectorFile(queryFile, line, queryList);

            lsh->runLSH(outFile, queryList, radius); //trexoume thn lsh
            while((tmp = queryList->deleteFirstNode()) != NULL)
            {
                delete tmp;
            }

            cout<<"Input next query file or end to stop"<<endl;
            cin >> searchFile;
            if(searchFile != "end")
            {
                queryFile.close();
                queryFile.open(searchFile.c_str());
                if(queryFile.is_open()==false)
                {
                    perror("Query file doesnt exists");
                    exit(3);
                }
            }

        }while(searchFile != "end");



        while((tmpVector = myList1->deleteFirstNode()) != NULL) //diagrafw thn lista eisodou
        {
            delete tmpVector;
        }

        delete lsh;
        delete queryList;
    }
    else if(type == "euclidean")
    {
        cout<<"euclidean"<<endl;
        string line;
        Vector* tmp;
        EuclideanNode* tmpEuclid;
        List<EuclideanNode*>* euclideanList = new List<EuclideanNode*>();
        for(Node<Vector*>*i=myList1->get_begin(); i!=NULL; i =i->get_next()) //ftiaxnw eukleidio node gia na exw kai to ID pedio
        {
            euclideanList->insertEnd(new EuclideanNode(i->get_data()));
        }

        LSH<EuclideanNode*>* lsh = new LSH<EuclideanNode*>(euclideanList,  L, K); //epeidi ta dedomena einai vector prepei na ta valw se eukleidia pou tha apothikeuw kai to id
        List<Vector*>* queryList = new List<Vector*>();
        List<EuclideanNode*>* queryListEuclidean = new List<EuclideanNode*>();

        do
        {
            readRadius(queryFile, radius);
            readVectorFile(queryFile, line, queryList);
            for(Node<Vector*>*i=queryList->get_begin(); i!=NULL; i =i->get_next()) //gia kathe query point kanw to eucleidio node
            {
                queryListEuclidean->insertEnd(new EuclideanNode(i->get_data()));
            }

            lsh->runLSH(outFile, queryListEuclidean, radius);

            while((tmpEuclid = queryListEuclidean->deleteFirstNode()) != NULL) //adeiazw tis listes gia to epomeno query list
            {
                delete tmpEuclid;
            }

            while((tmp = queryList->deleteFirstNode()) != NULL)
            {
                delete tmp;
            }

            cout<<"Input next query file or end to stop"<<endl;
            cin >> searchFile;
            if(searchFile != "end")
            {
                queryFile.close();
                queryFile.open(searchFile.c_str());
                if(queryFile.is_open()==false)
                {
                    perror("Query file doesnt exists");
                    exit(3);
                }
            }

        }while(searchFile != "end");

        while((tmpEuclid = euclideanList->deleteFirstNode()) != NULL)
        {
            delete tmpEuclid;
        }

        while((tmpVector = myList1->deleteFirstNode()) != NULL) //diagrafw thn lista eisodou
        {
            delete tmpVector;
        }

        delete euclideanList;
        delete queryListEuclidean;
        delete lsh;
        delete queryList;
    }
    else if(type == "matrix")
    {
        cout<<"matrix"<<endl;
        MatrixPoint* tmp;
        LSH<MatrixPoint*>* lsh = new LSH<MatrixPoint*>(myList3,  L, K);
        List<MatrixPoint*>* queryList = new List<MatrixPoint*>();

        do
        {
            readRadius(queryFile, radius);
            readMatrixQuery(queryFile, queryList);

            lsh->runLSH(outFile, queryList, radius);
            while((tmp = queryList->deleteFirstNode()) != NULL)
            {
                delete tmp;
            }

            cout<<"Input next query file or end to stop"<<endl;
            cin >> searchFile;
            if(searchFile != "end")
            {
                queryFile.close();
                queryFile.open(searchFile.c_str());
                if(queryFile.is_open()==false)
                {
                    perror("Query file doesnt exists");
                    exit(3);
                }
            }

        }while(searchFile != "end");

        while((tmpMatrix = myList3->deleteFirstNode()) != NULL) //diagrafw thn lista eisodou
        {
            delete tmpMatrix;
        }

        delete lsh;
        delete queryList;

    }

    delete myList1;
    delete myList2;
    delete myList3;
    inFile.close();
    queryFile.close();
    outFile.close();
}
