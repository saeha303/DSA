#ifndef HASH_H
#define HASH_H
#include<bits/stdc++.h>
#include "List.h"
using namespace std;
class hashItem
{
public:
    string k;
    int v;
    hashItem() {}
    hashItem(string k, int v)
    {
        this->k=k;
        this->v=v;
    }
    bool operator == (const hashItem &h )
    {
        return this->k==h.k;
    }
    friend ostream &operator<<(ostream &out, hashItem &ob);

};
ostream &operator<<(ostream &out, hashItem &ob)
{
    out<<"("<<ob.k<<","<<ob.v<<")";
    return out;
}
class hashTable
{
    LList<hashItem> **a;
    int bucket;
    int *isPrime;
    int PRIME;

    void sieveOfEratosthenes()
    {
        isPrime[0] = isPrime[1] = 1;
        for(long long i = 2; i*i <= bucket; i++)
            if(isPrime[i] == 0)
                for(long long j = i*i; j <= bucket; j += i)
                    isPrime[j] = 1;
    }
public:
    hashTable(int size)
    {
        bucket=size;
        isPrime=new int[bucket];
        sieveOfEratosthenes();
        a=new LList<hashItem>*[bucket];
        for(int i=0; i<bucket; i++)
            a[i]=new LList<hashItem>(hashItem("empty",0));
        PRIME = bucket - 1;
        while(isPrime[PRIME] == 1)
            PRIME--;
    }
    ~hashTable()
    {
        for(int i=0; i<bucket; i++)
        {
            delete a[i];
        }
        delete[] a;
        delete[] isPrime;
    }
    int h1(string s)
    {
        unsigned int h = 0;
        for (int i = 0; i < s.length(); i++)
        {
            h = (h << 2) | (h >> 30);
            h += (unsigned int) s.at(i);
        }
        return int(h);
    }
    int h2(string s)
    {
        int h=h1(s);
        return PRIME - (h%PRIME);
    }
    int singleHashCode(string k)
    {
        return h1(k);
    }
    int doubleHashCode(string k,int i)
    {
        return h1(k)+i*h2(k);
    }

    ///SeperateChaining
    int compressionSeperateChaining(string k)
    {
        return singleHashCode(k)%bucket;
    }
    void insertKeySeperateChaining(string k, int v)
    {
        int t=compressionSeperateChaining(k);
        a[t]->insert(hashItem(k,v));
    }
    void deleteKeySeperateChaining(string k)
    {
        int t=compressionSeperateChaining(k);
        if(a[t]->Search(hashItem(k,0))==1)
            a[t]->remove();
        else
            cout<<"Invalid key"<<'\n';
    }
    int searchKeySeperateChaining(string k)
    {
        if(a[compressionSeperateChaining(k)]->Search(hashItem(k,0))==1)
            cout<<"Key found"<<'\n';
        else
            cout<<"Key not found"<<'\n';
    }

    ///LinearProbing
    int compressionLinearProbing(string k,int i)
    {
        return (singleHashCode(k)+i)%bucket;
    }
    void insertKeyLinearProbing(string k, int v)
    {
        int i=0;
        while(i<bucket){
            int j=compressionLinearProbing(k,i);
            if(a[j]->isEmpty(hashItem("empty",0))||a[j]->isDeleted(hashItem("deleted",0))){
                a[j]->insert(hashItem(k,v));
                return;
            }
            else
            i+=1;
        }
        cout<<"Hash table overflow"<<'\n';
    }
    void deleteKeyLinearProbing(string k)
    {
        int i=0;
        while(i<bucket){
            int j=compressionLinearProbing(k,i);
            if(a[j]->Search(hashItem(k,0))==1){
                a[j]->remove();
                a[j]->setDeleted(hashItem("deleted",0));
                return;
            }
            i+=1;
        }
        cout<<"Invalid key"<<'\n';
    }
    int searchKeyLinearProbing(string k)
    {
        int i=0;
        int j=compressionLinearProbing(k,i);
        while(a[j]->isEmpty(hashItem("empty",0))||i<bucket){
            if(a[j]->Search(hashItem(k,0))==1){
                cout<<"Key found"<<'\n';
                return i;
            }
            i+=1;
            j=compressionLinearProbing(k,i);
        }
        cout<<"Key not found"<<'\n';
        return i;
    }

    ///QuadProbing
    int compressionQuadProbing(string k,int i)
    {
        return (singleHashCode(k)+i*i+i)%bucket;
    }
    void insertKeyQuadProbing(string k, int v)
    {
        int i=0;
        while(i<bucket){
            int j=compressionQuadProbing(k,i);
            if(a[j]->isEmpty(hashItem("empty",0))||a[j]->isDeleted(hashItem("deleted",0))){
                a[j]->insert(hashItem(k,v));
                return;
            }
            else
            i+=1;
        }
        cout<<"Hash table overflow"<<'\n';
    }
    void deleteKeyQuadProbing(string k)
    {
        int i=0;
        while(i<bucket){
            int j=compressionQuadProbing(k,i);
            if(a[j]->Search(hashItem(k,0))==1){
                a[j]->remove();
                a[j]->setDeleted(hashItem("deleted",0));
                return;
            }
            i+=1;
        }
        cout<<"Invalid key"<<'\n';
    }
    int searchKeyQuadProbing(string k)
    {
        int i=0;
        int j=compressionQuadProbing(k,i);
        while(a[j]->isEmpty(hashItem("empty",0))||i<bucket){
            if(a[j]->Search(hashItem(k,0))==1){
                cout<<"Key found"<<'\n';
                return i;
            }
            i+=1;
            j=compressionQuadProbing(k,i);
        }
        cout<<"Key not found"<<'\n';
        return i;
    }

    ///DoubleHashing
    int compressionDoubleHashing(string k, int i)///double hashing
    {
        return doubleHashCode(k,i)%bucket;
    }

    void insertKeyDoubleHashing(string k, int v)
    {
        int i=0;
        while(i<bucket)
        {
            int j=compressionDoubleHashing(k,i);
            if(a[j]->isEmpty(hashItem("empty",0))||a[j]->isDeleted(hashItem("deleted",0)))
            {
                a[j]->insert(hashItem(k,v));
                return;
            }
            else
                i+=1;
        }
        cout<<"Hash table overflow"<<'\n';
    }

    void deleteKeyDoubleHashing(string k)
    {
        int i=0;
        while(i<bucket)
        {
            int j=compressionDoubleHashing(k,i);
            if(a[j]->Search(hashItem(k,0))==1)
            {
                a[j]->remove();
                a[j]->setDeleted(hashItem("deleted",0));
                return;
            }
            i+=1;
        }
        cout<<"Invalid key"<<'\n';
    }
    int searchKeyDoubleHashing(string k)///double hashing
    {
        int i=0;
        int j=compressionDoubleHashing(k,i);
        while(a[j]->isEmpty(hashItem("empty",0))||i<bucket)
        {
            if(a[j]->Search(hashItem(k,0))==1)
            {
                cout<<"Key found"<<'\n';
                return i;
            }
            i+=1;
            j=compressionDoubleHashing(k,i);
        }
        cout<<"Key not found"<<'\n';
        return i;
    }

    void printHashTable()
    {
        for(int i=0; i<bucket; i++)
        {
            a[i]->print();
        }
    }
};
#endif // HASH_H
