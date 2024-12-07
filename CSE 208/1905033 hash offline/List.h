#ifndef LIST_H
#define LIST_H
#include<assert.h>
using namespace std;
template <typename E>
class List
{
private:
    void operator =(const List&) {}
    List(const List<E> &) {}
public:
    List() {}
    virtual ~List(){}
    virtual void clear()=0;
    virtual void insert(E)=0;
    virtual void append(E)=0;
    virtual E remove()=0;
    virtual void moveToStart()=0;
    virtual void moveToEnd()=0;
    virtual void prev()=0;
    virtual void next()=0;
    virtual int length()=0;
    virtual int currPos()=0;
    virtual void moveToPos(int)=0;
    virtual const E& getValue()=0;
    virtual int Search(E)=0;
    virtual bool isEmpty(E)=0;
    virtual bool isDeleted(E)=0;
    virtual void setEmpty(E)=0;
    virtual void setDeleted(E)=0;
};
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
        curr = tail = head = new Node<E>();
        cnt=size;
        currentPos = 0;
    }
    void init(E item,int size=0)
    {
        curr = tail = head = new Node<E>(item);
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
    LList(int size=0)///ok
    {
        init(size);
    }
    LList(E item)
    {
        init(item);
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
    void insert(E it)
    {
        curr->next = new Node<E>(it, curr->next);
        if (tail == curr)//when head=curr=tail
            tail = curr->next;
        cnt++;
    }
    void append(E it)
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
    int Search(E item)
    {
        moveToStart();
        while(curr->next != NULL)
        {

            if(curr->next->element==item)
            {
                return 1;
            }
            curr=curr->next;
        }
        return -1;
    }
    bool isEmpty(E s)
    {
        return head->element==s&&head->next==NULL;
    }
    bool isDeleted(E s)
    {
        return head->element==s&&head->next==NULL;
    }
    void setEmpty(E s)
    {
        head->element=s;
    }
    void setDeleted(E s)
    {
        head->element=s;
    }
    void print()
    {
        Node<E>* t=head->next;
        if(t!=NULL){
            cout<<(t->element);
        t=t->next;
        while(t!=NULL)
        {
            cout<<"->";
            cout<<(t->element);
            t=t->next;
        }
        cout<<'\n';
        }

    }
};
#endif // LIST_H
