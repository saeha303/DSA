#include<iostream>
#include<assert.h>
#include"Stack.h"
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
// Linked stack implementation
template <typename E>
class LStack: public Stack<E>
{
private:
    Node<E>* top; // Pointer to first element
    int size; // Number of elements
public:
    LStack(E* arr=NULL,int ignore=0) // Constructor
    {
        top = NULL;
        size = 0;
    }
    ~LStack()
    {
        clear();    // Destructor
    }
    void clear()   // Reinitialize
    {
        while (top != NULL)   // Delete Node nodes
        {
            Node<E>* temp = top;
            top = top->next;
            delete temp;
        }
        size = 0;
    }
    void push(const E it)   // Put "it" on stack
    {
        top = new Node<E>(it, top);
        size++;
    }
    E pop()   // Remove "it" from stack
    {
        assert(top != NULL);
        E it = top->element;
        Node<E>* ltemp = top->next;
        delete top;
        top = ltemp;
        size--;
        return it;
    }
    E topValue() // Return top value
    {
        assert(top != 0);
        return top->element;
    }
    int length()
    {
        return size;    // Return length
    }
    void setDirection(int dir)
    {

    }
};
template <typename E>
void printList(LStack<E>& ob)
{
    int top=ob.length();
    int a[top];

    for(int i=0; i<top; i++)
    {
        a[i]=ob.pop();
    }
    cout<<"<";
    for(int i=top-1; i>=0; i--)
        cout<<a[i]<<" ";
    cout<<">"<<'\n';
    ob.clear();
    for(int i=top-1; i>=0; i--)
    {
        ob.push(a[i]);
    }
}
int main()
{
    int size,command,param,intParam;
    int elem;
    cin>>size;
    LStack<int> ob;
    for(int i=0; i<size; i++)
    {
        cin>>elem;
        ob.push(elem);
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
            printList(ob);
            cout<<-1<<'\n';
        }
        else if(command==2)
        {
            cin>>param;
            ob.push(param);
            printList(ob);
            cout<<-1<<'\n';
        }
        else if(command==3)
        {
            cin>>intParam;
            int t=ob.pop();
            printList(ob);
            cout<<t<<'\n';
        }
        else if(command==4)
        {
            cin>>intParam;
            printList(ob);
            cout<<ob.length()<<'\n';
        }
        else if(command==5)
        {
            cin>>intParam;
            printList(ob);
            cout<<ob.topValue()<<'\n';
        }
        else if(command==6)
        {
            cin>>intParam;
            ob.setDirection(intParam);
            printList(ob);
            cout<<-1<<'\n';
        }
    }
}
