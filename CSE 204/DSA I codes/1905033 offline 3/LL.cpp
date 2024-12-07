#include <iostream>
#include <assert.h>
#include "Queue.h"
using namespace std;
template <typename E>
class Node
{
public:
    E element;
    Node* next;
    Node(const E item, Node* next=NULL)
    {
        element=item;
        this->next=next;
    }
    Node(Node* next=NULL)
    {
        this->next=next;
    }
};
template <typename E>
class LQueue: public Queue<E>
{
    Node<E>* front;
    Node<E>* rear;
    int size;
public:
    LQueue(int sz =0)
    {
        front = rear = new Node<E>();
        size = 0;
    }
    ~LQueue()
    {
        clear();
    }
    void clear()
    {
        while(front!=NULL)
        {
            rear=front;
            front=front->next;
            delete rear;
        }
        size=0;
        rear=front;//=new Node<E>();
    }
    void enqueue(const E it)
    {
        rear->next = new Node<E>(it, NULL);
        rear = rear->next;
        size++;
    }
    E dequeue()
    {
        assert(size != 0);
        E it = front->next->element;
        Node<E>* ltemp = front->next;

        delete front;
//        if (rear == ltemp)
//            rear = front;
        front=ltemp;
        size --;
        return it;
    }
    int length()
    {
        return size;
    }
    const E frontValue()
    {
        assert(size != 0);
        return front->next->element;
    }
    const E rearValue()
    {
        assert(size != 0);
        return rear->element;
    }
    const E leaveQueue()
    {
        assert(size != 0);
        E it = rear->element;
        Node<E>* ltemp = front;
        while(ltemp->next->next)
        {
            ltemp=ltemp->next;
        }
        ltemp->next=NULL;
        delete rear;
        rear=ltemp;
        size --;
        return it;
    }
};

