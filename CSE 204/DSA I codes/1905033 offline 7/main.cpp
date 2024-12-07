#include<iostream>
#include<ctime>
#include<vector>
#include<chrono>
#include<algorithm>
#include<fstream>
#include "mergesort.h"
#include "quicksort.h"
#include "randomizedqsort.h"
#include "inssort.h"
using namespace std;
int main()
{
    int n[]= {5,10,100,1000,10000,100000};
    ofstream file("output.txt",ios::out);
    if(file.is_open())
    {
        file<<"n,Merge Sort,Quicksort,Randomized Quicksort,Insertion Sort,Quicksort with sorted input,Randomized Quicksort with sorted input,STL sort() function,"<<'\n';
    }
    int* arr=NULL;
    int* sorted=NULL;
    double time[6][7];
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<7; j++)
        {
            time[i][j]=0;
        }
    }
    long double t=0,temp=0;
    vector<int> varr;
    for(int i=0; i<sizeof(n)/sizeof(n[0]); i++)
    {
        arr=new int[n[i]];
        sorted=new int[n[i]];
        clock_t start_time;
        for(int k=0; k<20; k++)
        {
            for(int j=0; j<5; j++)
            {
                srand(33+i+k);
                for(int l=0; l<n[i]; l++)
                {
                    arr[l]=rand();

                    if(j==4)
                    {
                        varr.push_back(arr[l]);
                    }
                }
                if(j==0)
                {
                    start_time=clock();
                    mergesort<int>(arr,sorted,0,n[i]-1);
                    t=(double)(clock()-start_time)/CLOCKS_PER_SEC;
                    time[i][j]+=t;
                }
                else if(j==1)
                {
                    start_time=clock();
                    qsort<int>(arr,0,n[i]-1);
                    t=(double)(clock()-start_time)/CLOCKS_PER_SEC;
                    time[i][j]+=t;
                }
                else if(j==2)
                {
                    start_time=clock();
                    rqsort<int>(arr,0,n[i]-1);
                    t=(double)(clock()-start_time)/CLOCKS_PER_SEC;
                    time[i][j]+=t;
                }
                else if(j==3)
                {
                    start_time=clock();
                    inssort<int>(arr,n[i]);
                    t=(double)(clock()-start_time)/CLOCKS_PER_SEC;
                    time[i][j]+=t;
                }
                else if(j==4)
                {
                    start_time=clock();
                    sort(varr.begin(),varr.end());
                    t=(double)(clock()-start_time)/CLOCKS_PER_SEC;
                    time[i][6]+=t;
                    varr.clear();
                }
            }
        }
        for(int k=0; k<20; k++)
        {
            for(int j=0; j<2; j++)
            {
                if(j==0)
                {
                    start_time=clock();
                    qsort<int>(arr,0,n[i]-1);
                    t=(double)(clock()-start_time)/CLOCKS_PER_SEC;
                    time[i][4]+=t;
                }
                else if(j==1)
                {
                    start_time=clock();
                    rqsort<int>(arr,0,n[i]-1);
                    t=(double)(clock()-start_time)/CLOCKS_PER_SEC;
                    time[i][5]+=t;
                }
            }
        }

        if(file.is_open())
        {
            file<<n[i]<<",";
            for(int l=0; l<7; l++)
        {
            time[i][l]=(time[i][l]*1000)/20;
            file<<time[i][l]<<",";
        }
        file<<'\n';
        }

        delete[] arr;
        delete[] sorted;
    }
    file.close();
}
