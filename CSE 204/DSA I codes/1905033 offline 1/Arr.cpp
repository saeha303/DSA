#include<iostream>
#include<assert.h>
#include "List.h"
using namespace std;
#define DEFAULT 10
template <typename T>
class AList:public List<T>
{
    int maxsize,listsize,curr,constSize;
    T* listArray;
public:
    AList()
    {
        listsize=0;
        curr=0;
        maxsize=constSize=DEFAULT;
        listArray=new T[maxsize];
    }
    AList(int initSize,int size, T a[])
    {
        maxsize=constSize=size;
        listsize=initSize;
        curr=0;
        listArray=new T[maxsize];
        for(int i=0; i<listsize; i++)
            listArray[i]=a[i];
    }
    ~AList()
    {
        delete[] listArray;
    }
    void clear()//1
    {
        delete[] listArray;
        listsize=curr=0;
        listArray=new T[maxsize];
    }
    void insert(const T item)//2
    {
        T* temp;
        if(listsize==maxsize)
        {
            temp=new T[listsize+constSize];
            for(int i=0; i<listsize; i++)
            {
                temp[i]=listArray[i];
            }
            delete[] listArray;
            listArray=temp;
            maxsize=listsize+constSize;
        }
        for(int i=listsize-1; i>=curr; i--)
        {
            listArray[i+1]=listArray[i];
        }
        listArray[curr]=item;
        listsize++;
    }
    void append(const T item)//3
    {
        T* temp;
        if(listsize==maxsize)
        {
            temp=new T[2*listsize];
            for(int i=0; i<listsize; i++)
            {
                temp[i]=listArray[i];
            }
            delete[] listArray;
            listArray=temp;
            maxsize=2*listsize;
        }
        listArray[listsize++]=item;
    }
    T remove()//4
    {
        assert(curr>=0&&curr<listsize);
        T t=listArray[curr];
        for(int i=curr; i<listsize-1; i++)
            listArray[i]=listArray[i+1];
        listsize--;
        return t;
    }
    void moveToStart()//5
    {
        curr=0;
    }
    void moveToEnd()//6
    {
        curr=listsize-1;
    }
    void prev()//7
    {
        if(curr>0)
            curr--;
    }
    void next()//8
    {
        if(curr<listsize-1&&listsize==maxsize)
            curr++;
        else if(curr<listsize)
            curr++;
    }
    int length()//9
    {
        return listsize;
    }
    int currPos()//10
    {
        return curr;
    }
    void moveToPos(int pos)//11
    {
        if(listsize==maxsize&&pos>=0&&pos<listsize)
            curr=pos;
        else if(listsize<maxsize&&pos>=0&&pos<=listsize)
            curr=pos;
    }
    const T& getValue()//12
    {
        assert(curr>=0&&curr<listsize);
        return listArray[curr];
    }
    const int Search(const T item)//13
    {
        for(int i=0; i<listsize; i++)
        {
            if(listArray[i]==item)
            {
                return 1;
            }
        }
        return -1;
    }
};
template <typename T>
void printList(AList<T>& ob)
{
    int curr=ob.currPos(),len=ob.length();
    ob.moveToStart();
    cout<<"<";
    for(int i=0; i<len; i++)
    {
        if(i==curr)
            cout<<"| ";
        cout<<ob.getValue()<<" ";
        ob.next();
    }
    cout<<">"<<'\n';
    ob.moveToPos(curr);
}
template <typename T>
void swap(AList<T>& l)
{
    T t1=l.getValue();
    l.next();
    T t2=l.getValue();
    t1=t1+t2-(t2=t1);
    l.remove();
    l.prev();
    l.remove();
    l.insert(t1);
    l.next();
    l.insert(t2);
    l.prev();
}
int main()
{
    int initSize,maxsize,command,intParam;
    int param,temp;//changes with element type of list
    cin>>initSize;
    cin>>maxsize;
    int a[initSize];//changes with element type of list
    for(int i=0; i<initSize; i++)
        cin>>a[i];
    AList<int> ob(initSize,maxsize,a);//changes with element type of list
    printList(ob);
    while(true)
    {
        cin>>command;
        if(!command)
            break;
        else if(command==1)
        {
            cin>>intParam;
            ob.clear();
            printList(ob);
            cout<<-1<<'\n';
        }

        else if(command==2)
        {
            cin>>param;
            ob.insert(param);
            printList(ob);
            cout<<-1<<'\n';
        }
        else if(command==3)
        {
            cin>>param;
            ob.append(param);
            printList(ob);
            cout<<-1<<'\n';
        }
        else if(command==4)
        {
            cin>>intParam;
            temp=ob.remove();
            printList(ob);
            cout<<temp<<'\n';
        }
        else if(command==5)
        {
            cin>>intParam;
            ob.moveToStart();
            printList(ob);
            cout<<-1<<'\n';
        }

        else if(command==6)
        {
            cin>>intParam;
            ob.moveToEnd();
            printList(ob);
            cout<<-1<<'\n';
        }

        else if(command==7)
        {
            cin>>intParam;
            ob.prev();
            printList(ob);
            cout<<-1<<'\n';
        }

        else if(command==8)
        {
            cin>>intParam;
            ob.next();
            printList(ob);
            cout<<-1<<'\n';
        }

        else if(command==9)
        {
            cin>>intParam;
            printList(ob);
            cout<<ob.length()<<'\n';
        }

        else if(command==10)
        {
            cin>>intParam;
            printList(ob);
            cout<<ob.currPos()<<'\n';
        }

        else if(command==11)
        {
            cin>>intParam;
            ob.moveToPos(intParam);
            printList(ob);
            cout<<-1<<'\n';
        }
        else if(command==12)
        {
            cin>>intParam;
            printList(ob);
            cout<<ob.getValue()<<'\n';
        }

        else if(command==13)
        {
            cin>>param;
            printList(ob);
            cout<<ob.Search(param)<<'\n';
        }
    }
    swap(ob);
    printList(ob);
}
