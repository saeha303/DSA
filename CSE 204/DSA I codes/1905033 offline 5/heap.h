#ifndef HEAP_H
#define HEAP_H
using namespace std;
class Heap
{
private:
    int* arr;
    int count=0;
    void deleteKeyHelp(int i)
    {
        int l=2*i;
        int r=2*i+1;
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
    }
    void inserthelp(int count)
    {
        cout<<"isHeap: "<<isHeap()<<'\n';
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
    Heap(vector<int>& v)
    {
        arr=new int[v.size()+1];
        for(int i=0; i<v.size(); i++)
        {
            insert(v[i]);
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
    bool isHeap()
    {
        int i;
        for(i=count;i>0;i--)
        {
            if(arr[i]>arr[i/2])
                break;
        }
        if(!i)
            return true;
        return false;
    }
};
void heapsort(vector<int>& v)
{
    Heap h(v);
    int l=v.size();
    for(int i=0;i<l;i++)
    {
        v[i]=h.deleteKey();
    cout<<v[i]<<" ";
    }
    cout<<'\n';
}
#endif//HEAP_H
