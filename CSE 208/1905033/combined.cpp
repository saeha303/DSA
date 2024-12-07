#include<bits/stdc++.h>
#include "List.h"
#include "hash.h"
using namespace std;
const string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";
int MyLen;
char RandomStr()
{
    return CHARACTERS.at(rand() % 26);
}
void loadFactor(int i,double &lf)
{
    if(i==0)
    {
        lf=0.4;
    }
    else if(i==1)
    {
        lf=0.5;
    }
    else if(i==2)
    {
        lf=0.6;
    }
    else if(i==3)
    {
        lf=0.7;
    }
    else if(i==4)
    {
        lf=0.8;
    }
    else if(i==5)
    {
        lf=0.9;
    }
}
void sep_chain(int &size, double &lf, ofstream &ofile)
{
    hashTable h(size);
    srand(time(0));
    vector<int> arr(size);
    MyLen=size*lf;
    int p=MyLen*0.1;
    vector<string> random_string_arr;
    int k=0;
    while(k<MyLen)
    {
        string random_string;
        for(int m = 0; m < 7; m++)
        {
            random_string+=RandomStr();
        }
        if(find(random_string_arr.begin(),random_string_arr.end(),random_string)!=random_string_arr.end())
            continue;
        else
        {
            random_string_arr.push_back(random_string);
            k++;
        }
    }

    for(int j=0; j<MyLen; j++)
    {
        h.insertKeySeperateChaining(random_string_arr[j],j+1);
    }

    vector<bool> deleted(MyLen,false);
    auto sTime = chrono::high_resolution_clock::now();
    for(int i=0; i<p; i++)
    {
        h.searchKeySeperateChaining(random_string_arr[rand()%MyLen]);
    }

    auto fTime = chrono::high_resolution_clock::now();

    ofile<<(chrono::duration_cast<std::chrono::nanoseconds>(fTime-sTime).count())/p<<" ns"<<"\t\t"<<"N/A"<<"\t\t\t";
    for(int i=0; i<p; i++)
    {
        int t=rand()%MyLen;
        h.deleteKeySeperateChaining(random_string_arr[t]);
        deleted[t]=true;
    }
    int j=0;
    k=0;
    sTime = chrono::high_resolution_clock::now();
    int itr=0;
    while(j<p/2 || k<p/2||itr<MyLen)
    {
        if(deleted[itr] && j<p/2)///creates problem if equal to or more than half deleted are deleted again
        {
            j++;
            h.searchKeySeperateChaining(random_string_arr[itr]);
        }
        else if(!deleted[itr] && k<p/2)
        {
            k++;
            h.searchKeySeperateChaining(random_string_arr[itr]);
        }
        itr++;
    }
    fTime = chrono::high_resolution_clock::now();
    ofile<<(chrono::duration_cast<std::chrono::nanoseconds>(fTime-sTime).count())/p<<" ns"<<"\t\t"<<"N/A"<<'\n';
}
void linaerProbing(int &size, double &lf, ofstream &ofile)
{
    hashTable h(size);
    srand(time(0));
    vector<int> arr(size);
    MyLen=size*lf;
    int p=MyLen*0.1;
    vector<string> random_string_arr;
    int k=0;
    while(k<MyLen)
    {
        string random_string;
        for(int m = 0; m < 7; m++)
        {
            random_string+=RandomStr();
        }
        if(find(random_string_arr.begin(),random_string_arr.end(),random_string)!=random_string_arr.end())
            continue;
        else
        {
            random_string_arr.push_back(random_string);
            k++;
        }
    }

    for(int j=0; j<MyLen; j++)
    {
        h.insertKeyLinearProbing(random_string_arr[j],j+1);
    }

    vector<bool> deleted(MyLen,false);
    auto sTime = chrono::high_resolution_clock::now();
    int prob=0;
    for(int i=0; i<p; i++)
    {
        prob+=h.searchKeyLinearProbing(random_string_arr[rand()%MyLen]);
    }

    auto fTime = chrono::high_resolution_clock::now();

    ofile<<(chrono::duration_cast<std::chrono::nanoseconds>(fTime-sTime).count())/p<<" ns"<<"\t\t"<<prob/p<<"\t\t\t";
    for(int i=0; i<p; i++)
    {
        int t=rand()%MyLen;
        h.deleteKeyLinearProbing(random_string_arr[t]);
        deleted[t]=true;
    }
    int j=0;
    k=0;
    sTime = chrono::high_resolution_clock::now();
    int itr=0;
    while(j<p/2 || k<p/2||itr<MyLen)
    {
        if(deleted[itr] && j<p/2)
        {
            j++;
            prob+=h.searchKeyLinearProbing(random_string_arr[itr]);
        }
        else if(!deleted[itr] && k<p/2)
        {
            k++;
            prob+=h.searchKeyLinearProbing(random_string_arr[itr]);
        }
        itr++;
    }
    fTime = chrono::high_resolution_clock::now();
    ofile<<(chrono::duration_cast<std::chrono::nanoseconds>(fTime-sTime).count())/p<<" ns"<<"\t\t"<<prob/p<<'\n';
}
void quadProbing(int &size, double &lf, ofstream &ofile)
{
    hashTable h(size);
    srand(time(0));
    vector<int> arr(size);
    MyLen=size*lf;
    int p=MyLen*0.1;
    vector<string> random_string_arr;
    int k=0;
    while(k<MyLen)
    {
        string random_string;
        for(int m = 0; m < 7; m++)
        {
            random_string+=RandomStr();
        }
        if(find(random_string_arr.begin(),random_string_arr.end(),random_string)!=random_string_arr.end())
            continue;
        else
        {
            random_string_arr.push_back(random_string);
            k++;
        }
    }

    for(int j=0; j<MyLen; j++)
    {
        h.insertKeyQuadProbing(random_string_arr[j],j+1);
    }

    vector<bool> deleted(MyLen,false);
    auto sTime = chrono::high_resolution_clock::now();
    int prob=0;
    for(int i=0; i<p; i++)
    {
        prob+=h.searchKeyQuadProbing(random_string_arr[rand()%MyLen]);
    }

    auto fTime = chrono::high_resolution_clock::now();

    ofile<<(chrono::duration_cast<std::chrono::nanoseconds>(fTime-sTime).count())/p<<" ns"<<"\t\t"<<prob/p<<"\t\t\t";
    for(int i=0; i<p; i++)
    {
        int t=rand()%MyLen;
        h.deleteKeyQuadProbing(random_string_arr[t]);
        deleted[t]=true;
    }
    int j=0;
    k=0;
    sTime = chrono::high_resolution_clock::now();
    int itr=0;
    while(j<p/2 || k<p/2||itr<MyLen)
    {
        if(deleted[itr] && j<p/2)
        {
            j++;
            prob+=h.searchKeyQuadProbing(random_string_arr[itr]);
        }
        else if(!deleted[itr] && k<p/2)
        {
            k++;
            prob+=h.searchKeyQuadProbing(random_string_arr[itr]);
        }
        itr++;
    }
    fTime = chrono::high_resolution_clock::now();
    ofile<<(chrono::duration_cast<std::chrono::nanoseconds>(fTime-sTime).count())/p<<" ns"<<"\t\t"<<prob/p<<'\n';
}
void doubleHashing(int &size, double &lf, ofstream &ofile)
{
    hashTable h(size);
    srand(time(0));
    vector<int> arr(size);
    bool flag=false;
    MyLen=size*lf;
    int p=MyLen*0.1;
    vector<string> random_string_arr;
    int k=0;
    while(k<MyLen)
    {
        string random_string;
        for(int m = 0; m < 7; m++)
        {
            random_string+=RandomStr();
        }
        if(find(random_string_arr.begin(),random_string_arr.end(),random_string)!=random_string_arr.end())
            continue;
        else
        {
            random_string_arr.push_back(random_string);
            k++;
        }
    }

    for(int j=0; j<MyLen; j++)
    {
        h.insertKeyDoubleHashing(random_string_arr[j],j+1);
    }

    vector<bool> deleted(MyLen,false);
    auto sTime = chrono::high_resolution_clock::now();
    int prob=0;
    for(int i=0; i<p; i++)
    {
        prob+=h.searchKeyDoubleHashing(random_string_arr[rand()%MyLen]);
    }

    auto fTime = chrono::high_resolution_clock::now();

    ofile<<(chrono::duration_cast<std::chrono::nanoseconds>(fTime-sTime).count())/p<<" ns"<<"\t\t"<<prob/p<<"\t\t\t";
    for(int i=0; i<p; i++)
    {
        int t=rand()%MyLen;
        h.deleteKeyDoubleHashing(random_string_arr[t]);
        deleted[t]=true;
    }
    int j=0;
    k=0;
    sTime = chrono::high_resolution_clock::now();
    int itr=0;
    while(j<p/2 || k<p/2||itr<MyLen)
    {
        if(deleted[itr] && j<p/2)
        {
            j++;
            prob+=h.searchKeyDoubleHashing(random_string_arr[itr]);
        }
        else if(!deleted[itr] && k<p/2)
        {
            k++;
            prob+=h.searchKeyDoubleHashing(random_string_arr[itr]);
        }
        itr++;
    }
    fTime = chrono::high_resolution_clock::now();
    ofile<<(chrono::duration_cast<std::chrono::nanoseconds>(fTime-sTime).count())/p<<" ns"<<"\t\t"<<prob/p<<'\n';
}
int main()
{
    int size;
    cin>>size;
    double lf;
    ofstream ofile("combined.txt");
    for(int l=0; l<6; l++)
    {
        loadFactor(l,lf);
        ofile<<"For load factor "<<lf<<'\n';
        ofile<<"\t\t\t"<<"Before deletion\t\t\t\t\t"<<"After deletion"<<'\n';
        ofile<<"Method\t\t\t"<<"Avg search time\t\tAvg number of probes\t"<<"Avg search time\t\tAvg number of probes"<<'\n';
        for(int i=0; i<4; i++)
        {
            if(i==0)
            {
                ofile<<"Separate chaining"<<"\t";
                sep_chain(size,lf,ofile);
            }

            else if(i==1)
            {
                ofile<<"Linear Probing"<<"\t\t";
                linaerProbing(size,lf,ofile);
            }
            else if(i==2)
            {
                ofile<<"Quadratic Probing"<<"\t";
                quadProbing(size,lf,ofile);
            }
            else if(i==3)
            {
                ofile<<"Double Hashing"<<"\t\t";
                doubleHashing(size,lf,ofile);
            }
        }
        ofile<<"\n\n";
    }
    ofile.close();
}
