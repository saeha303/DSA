#ifndef MINHEAP_H
#define MINHEAP_H
using namespace std;
class minHeap
{
private:
    vector<pair<int,int>> arr;
    int count=0;
    void swap(int& a, int& b)
    {
        a=a+b-(b=a);
    }
    int left(int i)
    {
        return i<<2;
    }
    int right(int i)
    {
        return (i<<2)|1;
    }
    void popHelp(int i)///minHeapify
    {
        int l=left(i);
        int r=right(i);
        int smallest=i;
        if(l<=count && arr[l].first<=arr[i].first)
        {
            smallest=l;
        }
        if(r<=count && arr[r].first<arr[smallest].first)
        {
            smallest=r;
        }
        if(smallest!=i)
        {
            swap(arr[i],arr[smallest]);
            popHelp(smallest);
        }
        else
        {
            return;
        }
    }
    void pushhelp(int count)
    {
        if(count>1){
        int p=count>>2;
        if(arr[p].first>arr[count].first)
        {
            swap(arr[p],arr[count]);
            inserthelp(p);
        }
        else return;
        }
    }
    int search(int v)
    {
        int idx=0;
        for(int i=1;i<=count;i++){
            if(i==v){
                idx=i;
                break;
            }
        }
        return idx;
    }
public:
    minHeap()
    {
        arr.push_back(make_pair(-1,-1));
    }
    void push(const int k,const int v)
    {
        arr.push_back(make_pair(k,v));///key,vertex
        count++;
        pushhelp(count);
    }
    int getMin()
    {
        if(count>0)
            return arr[1].first;
        return -1;
    }
    int pop()
    {
        int t;
        if(count==1)
        {
            t=arr[1].first;
            count--;
        }
        if(count>1)
        {
            t=arr[1].first;
            arr[1]=arr[count];
            count--;
            popHelp(1);
        }
        return t;
    }
    void deceraseKey(int v, int k)
    {
        int s=search(v);
        if(!s||arr[s]<k){
            return;
        }
        arr[s].first=k;
        pushhelp(s);
    }
};
#endif//MINHEAP_H
