#ifndef STACK_H
#define STACK_H
template <typename E>
class Stack{
void operator=(const Stack<E>&);
Stack(const Stack<E>&);
public:
    Stack(){}
    virtual ~Stack(){}
    virtual void clear()=0;
    virtual void push(E)=0;
    virtual E pop()=0;
    virtual int length()=0;
    virtual E topValue()=0;
    virtual void setDirection(int)=0;
};
#endif // STACK_H

