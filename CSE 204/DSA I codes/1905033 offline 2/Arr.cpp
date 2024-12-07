#include<iostream>
#include<assert.h>
#include"Stack.h"
#define DEFAULT_SIZE 16
using namespace std;
template <typename E>
class AStack: public Stack<E>
{
    int top,maxsize,dir;
    E* stackArray;
public:
    AStack(E* arr)
    {
        top=-1;
        maxsize=DEFAULT_SIZE;
        stackArray=arr;
        dir=1;
    }
    AStack(E* arr,int dir)
    {
        stackArray=arr;
        maxsize=DEFAULT_SIZE;
        this->dir=dir;
        if(dir==-1)
        {
            top=maxsize;
        }
        else if(dir==1)
        {
            top=-1;
        }
    }
    ~AStack()
    {
//        delete[] stackArray;
    }
    void clear()
    {
        if(dir==1)
        {
            top=-1;
        }
        else if(dir==-1)
        {
            top=maxsize;
        }
    }
    void push(const E item)
    {
        if(dir==1)
        {
            if(top==maxsize-1)
            {
                E* temp=new E[maxsize+DEFAULT_SIZE];
                for(int i=0; i<maxsize; i++)
                    temp[i]=stackArray[i];
                delete[] stackArray;
                stackArray=temp;
                maxsize+=DEFAULT_SIZE;
            }
            stackArray[++top]=item;
        }
        else if(dir==-1)
        {
            if(top==0)
            {
                E* temp=new E[maxsize+DEFAULT_SIZE];
                for(int i=maxsize+DEFAULT_SIZE-1; i>=maxsize; i--)
                    temp[i]=stackArray[i-DEFAULT_SIZE];
                delete[] stackArray;
                stackArray=temp;
                top=maxsize;
                maxsize+=DEFAULT_SIZE;
            }
            stackArray[--top]=item;
        }
    }
    E pop()
    {
        if(dir==1)
        {
            assert(top>=0);
            return stackArray[top--];
        }
        else if(dir==-1)
        {
            assert(top<=maxsize-1);
            return stackArray[top++];
        }
    }
    int length()
    {
        if(dir==1)
            return top+1;
        else if(dir==-1)
            return maxsize-top;
    }
    E topValue()
    {
        if(dir==1)
        {
            assert(top>=0);
        }
        else if(dir==-1)
        {
            assert(top<=maxsize-1);
        }
        return stackArray[top];
    }
    void setDirection(int dir)
    {
        if(dir==1){
            this->dir=1;
        }
        else if(dir==-1){
            this->dir=-1;
        }
        this->clear();
    }

};
template <typename E>
void printList(AStack<E>& ob)
{
    int top=ob.length();
    int a[top];

    for(int i=0; i<top; i++)
    {
        a[i]=ob.pop();
    }
    cout<<"<";
    for(int i=top-1;i>=0;i--)
        cout<<a[i]<<" ";
    cout<<">"<<'\n';
    for(int i=top-1; i>=0; i--)
    {
        ob.push(a[i]);
    }
}

//int main()
//{
//    int size,command,param,intParam;
//    int elem;
//    cin>>size;
//    int* arr=new int[DEFAULT_SIZE];
//    AStack<int> ob(arr,-1);
//    for(int i=0; i<size; i++)
//    {
//        cin>>elem;
//        ob.push(elem);
//    }
//    while(true)
//    {
//        cin>>command;
//        if(!command)
//            break;
//        else if(command==1)
//        {
//            cin>>intParam;
//            ob.clear();
//            printList(ob);
//            cout<<-1<<'\n';
//        }
//        else if(command==2)
//        {
//            cin>>param;
//            ob.push(param);
//            printList(ob);
//            cout<<-1<<'\n';
//        }
//        else if(command==3)
//        {
//            cin>>intParam;
//            int t=ob.pop();
//            printList(ob);
//            cout<<t<<'\n';
//        }
//        else if(command==4)
//        {
//            cin>>intParam;
//            printList(ob);
//            cout<<ob.length()<<'\n';
//        }
//        else if(command==5)
//        {
//            cin>>intParam;
//            printList(ob);
//            cout<<ob.topValue()<<'\n';
//        }
//        else if(command==6)
//        {
//            cin>>intParam;
//            ob.setDirection(intParam);
//            printList(ob);
//            cout<<-1<<'\n';
//        }
//    }
//    delete[] arr;
//}
