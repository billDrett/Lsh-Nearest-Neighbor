#include <iostream>
#include <cstdlib>
#include "List.h"
#include "Node.h"
#include "dataTypes.h"
#include "euclideanNode.h"
using namespace std;

template <class T>
List<T>::List()
{
    listSize = 0;
    start = NULL;
    last = NULL;
}

template <class T>
List<T>::~List()
{
    Node<T>* tmp = start;
    Node<T>* del;

    while(tmp != NULL)//diagrafoume enan enan tous komvous
    {
        del = tmp;
        tmp = tmp->get_next();
        listSize--;
        delete del;
    }
}

template <class T>
bool List<T>::checkEmpty()
{
	return(listSize == 0);
}

template <class T>
int List<T>::getSize()
{
    return listSize;
}

template <class T>
Node<T>* List<T>::get_begin()
{
    return start;
}

template <class T>
Node<T>* List<T>::get_last()
{
    return last;
}

template <class T>
void List<T>::insertBeginning(T item)
{
	Node<T>* node = new Node<T>(item);

	if(checkEmpty()) //an einai to monadiko stoixeio prepei na allaksw ton deikti start kai last
	{
	    start = node;
	    last = node;
	    listSize++;
		return;
	}
	//alliws eisodos stin arxi
    node->set_next(start);
    start = node;
    listSize++;
}

template <class T>
void List<T>::insertEnd(T item)
{
	Node<T>* node = new Node<T>(item);

	if(checkEmpty()) //an einai to monadiko stoixeio prepei na allaksw ton deikti start kai last
	{
	    start = node;
	    last = node;
	    listSize++;
		return;
	}
	//alliws eisodos sto telos ths listas
    last->set_next(node);
    node->set_next(NULL);
    last = node;
    listSize++;
}

template <class T>
T List<T>::deleteFirstNode()
{
    Node<T>* tmp;
    T tmpAccount;
    if(checkEmpty())
    {
        return 0;
    }

    tmp = start;
    start = start->get_next();
    if(listSize == 1) last = NULL; //arxi kai telos deixnoun sto idio, epomenos i lista exei mono ena stoixeio

    tmpAccount = tmp->get_data();
    delete tmp;
    listSize--;
    return tmpAccount;
}

template <class T>
T List<T>::deleteLastNode()
{
    Node<T>* tmp = start;
    T tmpAccount;
    if(checkEmpty())
    {
        return 0;
    }

    if(listSize == 1) //an exei mono ena stoixeio tote prepei na allaksei kai o deiktis start
    {
        tmpAccount = start->get_data();
        delete start;
        start = NULL;
        last = NULL;
        listSize--;
        return tmpAccount;
    }

    while(tmp->get_next() != last) //pairnw to proteleutaio stoixeio
    {
        tmp = tmp->get_next();
    }
    tmpAccount = last->get_data();
    delete last;
    last = tmp;
    tmp->set_next(NULL);
    listSize--;
    return tmpAccount;
}

template <class T>
T List<T>::deleteNode(Node<T>* node) //diagrafei tou sigekrimenou node
{
    Node<T>* tmp = start;
    Node<T>* del = NULL;
    T data;

    if(checkEmpty() == true)
    {
        return 0;
    }

    if(start == node) // an einai o prwtos 'h o monadikos komvos
    {
        return this->deleteFirstNode();
    }

    if(last == node) //an o teleutaios
    {
        return this->deleteLastNode();
    }

    while(tmp->get_next() != node)
    {
        if(tmp->get_next() == NULL)
        {
            return 0;
        }
        tmp = tmp->get_next();
    }
    del = tmp->get_next();
    tmp->set_next(del->get_next());

    data = del->get_data();
    listSize--;
    delete del;
    return data;
}


template class List<int>;
template class List<double>;
template class List<string>;
template class List<Vector* >;
template class List<Hamming* >;
template class List<EuclideanNode* >;
template class List<MatrixPoint* >;

