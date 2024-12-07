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
int main()
{
    int size;
    cin>>size;
    double lf;
    ofstream ofile("separate chaining.txt");
    ofile<<"\t\t"<<"Before deletion\t\t"<<"After deletion"<<'\n';
    ofile<<"Load factor\t"<<"Avg search time\t\t"<<"Avg search time"<<'\n';
    for(int i=0; i<6; i++)
    {
        loadFactor(i,lf);
        ofile<<lf<<"\t\t";
        hashTable h(size);
        srand(time(0));
        vector<int> arr(size);
        bool flag=false;
        MyLen=floor(size*lf);
        int p=floor(MyLen*0.1);
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
        ofile<<(chrono::duration_cast<std::chrono::nanoseconds>(fTime-sTime).count())/p<<" ns"<<"\t\t";
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
            if(deleted[itr] && j<p/2)
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
        ofile<<(chrono::duration_cast<std::chrono::nanoseconds>(fTime-sTime).count())/p<<" ns"<<"\n";
    }
    ofile.close();
}
