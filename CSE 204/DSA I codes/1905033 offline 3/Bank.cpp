#include<iostream>
#include"Arr.cpp"
#include"LL.cpp"
using namespace std;
class customer
{

public:
    int e,s,l;
    customer() {}
    customer(int e, int s, int l)
    {
        this->e=e;
        this->s=s;
        this->l=l;
    }
//    void setE(int t){e=t;}
//    void setS(int t){s=t;}
//    void setL(int t){l=t;}
//    int getE(){return e;}
//    int getS(){return s;}
//    int getL(){return l;}
};

int main()
{
    int c;
    cin>>c;
    int e,s,l;
    int b1rl,b2rl;

    AQueue<customer> b1(c),b2(c);

//    customer* arr1=new customer[c+1];
//    customer* arr2=new customer[c+1];
//    AQueue<customer> b1(arr1,c),b2(arr2,c);

//    LQueue<customer> b1,b2;

    for(int i=0; i<c; i++)
    {
        cin>>e>>s;
        if(!b1.length())
        {
            b1.enqueue(customer(e,s,e+s));
        }
        else if(!b2.length())
        {
            b2.enqueue(customer(e,s,e+s));
        }
        else
        {
            if(b1.frontValue().l<=e)
            {
                b1.dequeue();
                b1.enqueue(customer(e,s,b1.rearValue().l+s));
            }
            else if(b2.frontValue().l<=e)
            {
                b2.dequeue();
                b2.enqueue(customer(e,s,b2.rearValue().l+s));
            }
            else if(b1.length()<=b2.length())
            {
                if(b1.rearValue().l>e)
                    b1.enqueue(customer(e,s,b1.rearValue().l+s));
                if(b1.frontValue().l<e)
                    b1.dequeue();
            }
            else if(b1.length()>b2.length())
            {
                if(b2.rearValue().l>e)
                    b2.enqueue(customer(e,s,b2.rearValue().l+s));
                if(b2.frontValue().l<e)
                    b2.dequeue();
            }
        }
    }

    while(b1.length()||b2.length())
    {

        if(b1.length()==1&&b2.length()==1)
        {
            break;
        }
        if(b1.length()&&b2.length()&&b1.frontValue().l<=b2.frontValue().l)
        {
            b1rl=b1.rearValue().l;
            b1.dequeue();
        }
        else if(b1.length()&&b2.length()&&b2.frontValue().l<b1.frontValue().l)
        {
            b2rl=b2.rearValue().l;
            b2.dequeue();
        }
        if(b2.length()<=b1.length()-2)
        {
            b2.enqueue(customer(b1.rearValue().e,b1.rearValue().s,b2rl+b1.rearValue().s));
            b1.leaveQueue();

        }
        else if(b1.length()<=b2.length()-2)
        {
            b1.enqueue(customer(b2.rearValue().e,b2.rearValue().s,b1rl+b2.rearValue().s));
            b2.leaveQueue();
        }
    }
    cout<<"Booth 1 finishes service at t="<<b1.frontValue().l<<'\n';
    cout<<"Booth 2 finishes service at t="<<b2.frontValue().l<<'\n';
}

