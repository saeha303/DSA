#include <iostream>
#include "Arr.cpp"
#include "LL.cpp"
using namespace std;
template <typename E>
void printQueue(AQueue<E>& ob)
{

    int len=ob.length();
    E arr[len];
    for(int i=len-1;i>=0;i--)
    {
        arr[i]=ob.leaveQueue();
    }
    cout<<"<";
    for(int i=0;i<len;i++)
        cout<<arr[i]<<" ";
    cout<<">"<<'\n';
    ob.clear();
    for(int i=0; i<len; i++)
    {
        ob.enqueue(arr[i]);
    }
}
template <typename E>
void printQueue(LQueue<E>& ob)
{

    int len=ob.length();
    E arr[len];
    for(int i=len-1;i>=0;i--)
    {
        arr[i]=ob.leaveQueue();
    }
    cout<<"<";
    for(int i=0;i<len;i++)
        cout<<arr[i]<<" ";
    cout<<">"<<'\n';
    ob.clear();
    for(int i=0; i<len; i++)
    {
        ob.enqueue(arr[i]);
    }
}
int main()
{
    int size,command,intParam;
    int param,elem;//changes with type
    cin>>size;

//    int* arr=new int[size+1];
//    AQueue<int> ob(arr,size);

//    AQueue<int> ob(size);

    LQueue<int> ob;

    for(int i=0; i<size; i++)
    {
        cin>>elem;
        ob.enqueue(elem);
    }
    while(true)
    {
        cin>>command;
        if(!command)
            break;
        else if(command==1)
        {
            cin>>intParam;
            ob.clear();
            printQueue(ob);
            cout<<-1<<'\n';
        }
        else if(command==2)
        {
            cin>>param;
            ob.enqueue(param);
            printQueue(ob);
            cout<<-1<<'\n';
        }
        else if(command==3)
        {
            cin>>intParam;
            int t=ob.dequeue();//changes with type
            printQueue(ob);
            cout<<t<<'\n';
        }
        else if(command==4)
        {
            cin>>intParam;
            printQueue(ob);
            cout<<ob.length()<<'\n';
        }
        else if(command==5)
        {
            cin>>intParam;
            printQueue(ob);
            cout<<ob.frontValue()<<'\n';
        }
        else if(command==6)
        {
            cin>>intParam;
            printQueue(ob);
            cout<<ob.rearValue()<<'\n';
        }
        else if(command==7)
        {
            cin>>intParam;
            int t=ob.leaveQueue();//changes with type
            printQueue(ob);
            cout<<t<<'\n';
        }
    }
}

