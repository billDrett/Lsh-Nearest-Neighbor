#ifndef Included_Node_H
#define Included_Node_H

template <class T>
class Node
{
    private:
        Node* next;
        T data;
    public:
        Node(T Data);
        ~Node();

        Node* get_next();
        T get_data();

        void set_next(Node* next1);
        void set_data(T Data);
};
#endif
