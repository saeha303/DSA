#include<iostream>
#include<assert.h>
#include "List.h"
using namespace std;
template <typename E>
class Node
{
public:
    E element;///hashItem
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
class LList: public List<E>
{
private:
    Node<E>* head;
    Node<E>* tail;
    Node<E>* curr;
    int cnt,currentPos;
    void init(int size=0)
    {
        curr = tail = head = new Node<E>;
        cnt=size;
        currentPos = 0;
    }
    void removeAllNodes()
    {
        while(head != NULL)
        {
            curr = head;
            head = head->next;
            delete curr;
        }
    }
    void enterElements(E a[])
    {
        curr=new Node<E>(a[0],NULL);
        head->next=curr;
        tail=curr;
        for(int i=1; i<cnt; i++)
        {
            curr=new Node<E>(a[i],NULL);
            tail->next=curr;
            tail=curr;
        }
        curr=head;
    }

public:
    LList(int size, int ignore, E a[])
    {
        init(size);
        enterElements(a);
    }
    LList()
    {
        init();
    }
    ~LList()
    {
        removeAllNodes();
    }
    void clear()
    {
        removeAllNodes();
        init();
    }
    void insert(const E it)
    {
        curr->next = new Node<E>(it, curr->next);
        if (tail == curr)//when head=curr=tail
            tail = curr->next;
        cnt++;
    }
    void append(const E it)
    {
        tail = tail->next = new Node<E>(it, NULL);
        cnt++;
    }
    E remove()
    {
        assert(curr->next != NULL);
        E it = curr->next->element;
        Node<E>* temp = curr->next;
        if (tail == curr->next)
            tail = curr;
        curr->next = curr->next->next;
        delete temp;
        cnt--;
        return it;
    }
    void moveToStart()
    {
        curr = head;
        currentPos=0;
    }
    void moveToEnd()
    {
        curr = head;
        while(curr->next!=NULL)//curr->next->next
            curr=curr->next;
        currentPos=cnt-1;
    }

    void prev()
    {
        if (curr == head)
            return;
        Node<E>* temp = head;
        while (temp->next!=curr)
            temp=temp->next;
        curr = temp;
        if(currentPos>0)
            currentPos--;
    }
    void next()
    {
        if (curr != tail)
            curr = curr->next;
        if(currentPos<cnt)
            currentPos++;
    }
    int length()
    {
        return cnt;
    }

    int currPos()
    {
        return currentPos;
    }
    void moveToPos(int pos)
    {
        assert ((pos>=0)&&(pos<=cnt));
        curr = head;
        for(int i=0; i<pos; i++)
            curr = curr->next;
        currentPos=pos;
    }
    const E& getValue()
    {
        assert(curr->next != NULL);
        return curr->next->element;
    }
    const E Search(const E item)
    {
        Node<E>* temp=head->next;
        while(temp != NULL)
        {
            if(temp->element==item)
            {
                return 1;
            }
            temp=temp->next;
        }
        return -1;
    }
//    friend ostream &operator<< <>(ostream &out, const LList<E>& ob);
};
//template <typename T>
//ostream& operator<<(ostream &out,const LList<T>& ob)
//{
//    Node<T>* temp;
//    temp=ob.head->next;
//    for(int i=0; i<ob.cnt; i++)
//    {
//        if(i==ob.currentPos)
//            out<<"| ";
//        out<<temp->element<<" ";
//        temp=temp->next;
//    }
//    if(ob.currentPos==ob.cnt)
//        out<<"| ";
//    out<<'\n';
//    return out;
//}
template <typename T>
void printList(LList<T>& ob)
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
int main()
{
    int initSize,maxsize,command,intParam;
    int param,temp;//changes with element type of list
    cin>>initSize;
    cin>>maxsize;
    int a[initSize];//changes with element type of list
    for(int i=0; i<initSize; i++)
        cin>>a[i];
    LList<int> ob(initSize,maxsize,a);//changes with element type of list
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

}
