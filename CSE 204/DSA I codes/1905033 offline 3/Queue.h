#ifndef QUEUE_H
#define QUEUE_H
template <typename E>
class Queue
{
void operator =(const Queue&) {}
Queue(const Queue&) {}
public:
Queue() {}
virtual ~Queue() {}
virtual void clear() = 0;
virtual void enqueue(const E) = 0;
virtual E dequeue() = 0;
virtual int length()= 0;
virtual const E frontValue()= 0;
virtual const E rearValue()= 0;
virtual const E leaveQueue()= 0;
};
#endif // QUEUE_H
