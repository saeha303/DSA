#ifndef LIST_H
#define LIST_H

template <typename E>
class List
{
private:
    void operator =(const List&) {}
    List(const List&) {}
public:
    List() {}
    virtual ~List(){}
    virtual void clear()=0;
    virtual void insert(const E)=0;
    virtual void append(const E)=0;
    virtual E remove()=0;
    virtual void moveToStart()=0;
    virtual void moveToEnd()=0;
    virtual void prev()=0;
    virtual void next()=0;
    virtual int length()=0;
    virtual int currPos()=0;
    virtual void moveToPos(int)=0;
    virtual const E& getValue()=0;
    virtual const int Search(const E)=0;
};
#endif // LIST_H
