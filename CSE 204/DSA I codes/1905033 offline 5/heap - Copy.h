#ifndef HEAP_H
#define HEAP_H
using namespace std;
class Heap
{
private:
    int* arr;
    int count=0;
    int left(int i)
    {
        return 2*i;
    }
    int right(int i)
    {
        return 2*i+1;
    }
    void deleteKeyHelp(int i)
    {
        int l=left(i);
        int r=right(i);
        int largest=i;
        if(l<=count && arr[l]>=arr[i])
        {
            largest=l;
        }
        if(r<=count && arr[r]>arr[largest])
        {
            largest=r;
        }
        if(largest!=i)
        {
            arr[i]=arr[i]+arr[largest]-(arr[largest]=arr[i]);
            deleteKeyHelp(largest);
        }
        else
        {
            return;
        }
    }
    void inserthelp(int count)
    {
        if(count>1)
        {
            int p=(int)(count/2);
            if(arr[p]<=arr[count])
            {
                swap(arr[p],arr[count]);
                inserthelp(p);
            }
            else
                return;
        }
    }
public:
    Heap(int size)
    {
        arr=new int[size+1];
    }
    Heap(vector<int>& v, bool flag=true)
    {
        arr=new int[v.size()+1];
        for(int i=0; i<v.size(); i++)
        {
            insert(v[i]);
        }
        if(!flag)
        {
            for(int i=0;i<v.size();i++)
                v[i]=arr[i+1];
        }
    }
    ~Heap()
    {
        delete[] arr;
    }
    void insert(const int it)
    {
        arr[++count]=it;
        inserthelp(count);
    }
    int getMax()
    {
        if(count>0)
            return arr[1];
        return -1;
    }
    int deleteKey()
    {
        int t;
        if(count==1)
        {
            t=arr[1];
            count--;
        }
        if(count>1)
        {
            t=arr[1];
            arr[1]=arr[count];
            count--;
            deleteKeyHelp(1);
        }
        return t;
    }
    int size()
    {
        return count;
    }
    int getMin()
    {
        int min=arr[count/2];
        for(int i=1+count/2;i<=count;i++)
        {
            min=max(min,arr[i]);
        }
        return min;
    }
};
void maxHeapify(vector<int>& v, int i)
{
        int l=2*i+1;
        int r=2*i+2;
        int Largest;
        if(l<v.size() && v[l]>v[i])
        {
            Largest=l;
        }
        else Largest=i;
        if(r<v.size() && v[r]>v[Largest])
        {
            Largest=r;
        }
        if(Largest!=i)
        {
            v[i]=v[i]+v[Largest]-(v[Largest]=v[i]);
            maxHeapify(v,Largest);
        }
}
//void minHeapify(vector<int>& v, int i)
//{
//        int l=2*i+1;
//        int r=2*i+2;
//        int Smallest;
//        if(l<v.size() && v[l]<v[i])
//        {
//            Smallest=l;
//        }
//        else Smallest=i;
//        if(r<v.size() && v[r]<v[Smallest])
//        {
//            Smallest=r;
//        }
//        if(Smallest!=i)
//        {
//            v[i]=v[i]+v[Smallest]-(v[Smallest]=v[i]);
//            minHeapify(v,Smallest);
//        }
//}
//void buildMinHeap(vector<int>& v)
//{
//    for(int i=0;i<v.size();i++) cout<<v[i]<<" ";
//    cout<<'\n';
//    for(int i=(v.size()>>1)-1; i>=0; i--)
//    {
//        minHeapify(v,i);
//    }
//    for(int i=0;i<v.size();i++) cout<<v[i]<<" ";
//    cout<<'\n';
//}
void buildMaxHeap(vector<int>& v)
{
    for(int i=(v.size()>>1)-1; i>=0; i--)
    {
        maxHeapify(v,i);
    }
}
void heapsort(vector<int>& v)
{
//    buildMinHeap(v);
//    int length=v.size();
//    vector<int> t;
////    int i=0;
//    while(length>0)
//    {
//        v[length-1]=v[length-1]+v[0]-(v[0]=v[length-1]);
//        t.push_back(v[length-1]);
//        v.pop_back();
//        length--;
////        i++;
//        minHeapify(v,0);
//    }
//    v=t;


//    Heap temp(v,false);
////    for(int i=0;i<v.size();i++) cout<<v[i]<<" ";
////    cout<<'\n';
//    vector<int> t;
//    int length=v.size();
//    while(length>0)
//    {
//        t.push_back(v[0]);
//        v[length-1]=v[length-1]+v[0]-(v[0]=v[length-1]);
//        v.pop_back();
//        length--;
//        maxHeapify(v,0);
//    }
//    v=t;


//    buildMaxHeap(v);
//    int length=v.size();
//    vector<int> t;
//    while(length>0)
//    {
//        v[length-1]=v[length-1]+v[0]-(v[0]=v[length-1]);
//        t.push_back(v[length-1]);
//        v.pop_back();
//        length--;
//        maxHeapify(v,0);
//    }
//    v=t;

    Heap h(v);
    int l=v.size();
    for(int i=0;i<l;i++)
    {
        v[i]=h.deleteKey();
    }
}
#endif//HEAP_H
