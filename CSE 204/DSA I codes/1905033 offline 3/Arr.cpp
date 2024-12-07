#include <iostream>
#include <assert.h>
#include "Queue.h"
#define DEFAULT_SIZE 16
using namespace std;
template <typename E>
class AQueue: public Queue<E>
{
    int maxSize,constSize;
    int front;
    int rear;
    E *listArray;
public:
    AQueue(int size =DEFAULT_SIZE)
    {
        maxSize =constSize= size+1;
        rear = 0;
        front = 1;
        listArray = new E[maxSize];
    }
    AQueue(E* arr,int size)
    {
        maxSize =constSize= size+1;
        rear = 0;
        front = 1;
        listArray = arr;
    }
    ~AQueue()
    {
        delete[] listArray;
    }
    void clear()
    {
        rear = 0;
        front = 1;
        delete[] listArray;
        listArray=new E[maxSize];
    }
    void enqueue(const E it)
    {

        if(((rear+2) % maxSize) == front)
        {
            E* temp=new E[maxSize+constSize];
            for(int i=front;i!=rear;(i++)%maxSize)
            {
                temp[i]=listArray[i];
            }
            temp[rear]=listArray[rear];
            delete[] listArray;
            listArray=temp;
            maxSize=maxSize+constSize;
        }
        rear = (rear+1) % maxSize;
        listArray[rear] = it;
    }
    E dequeue()
    {
        assert(length() != 0);
        E it = listArray[front];
        front = (front+1) % maxSize;
        return it;
    }
    int length()
    {
        return ((rear+maxSize) - front + 1) % maxSize;
    }
    const E frontValue()
    {
        assert(length() != 0);
        return listArray[front];
    }
    const E rearValue()
    {
        assert(length() != 0);
        return listArray[rear];
    }
    const E leaveQueue()
    {
        assert(length() != 0);
        E it = listArray[rear];
        rear = (rear-1) % maxSize;
        return it;
    }
};
