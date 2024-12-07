#include<iostream>
#include "Arr.cpp"
#include "LL.cpp"
using namespace std;
void swap(int& a, int& b)
{
    a=a+b-(b=a);
}
void sort(int arr[],int size)
{
    int min;
    for(int i=0;i<size-1;i++){
            min=arr[i];
        for(int j=i+1;j<size;j++){
            if(arr[j]<arr[i])
            swap(arr[i],arr[j]);
        }
    }
}
void prep_arrays(int arr[],int size)
{
    int input;
    for(int i=0; i<size; i++)
    {
        cin>>input;
        arr[i]=input;
    }
    sort(arr,size);
}
void printList(LList<int>& list,int size)
{
    int j,curr=list.currPos(),len=list.length(),k=0;
    list.moveToStart();
    for(int i=0; i<size; i++)
    {
        if(k<len)
            j=list.getValue();
        if(j==i)
        {
            cout<<j<<",";
            list.next();
            k++;
        }

        else
        {
            cout<<",";
        }

    }
    cout<<"\b";
    cout<<" ";
    cout<<"\n";
    list.moveToPos(curr);
}
void printList(AList<int>& list,int size)
{
    int j,curr=list.currPos(),len=list.length(),k=0;
    list.moveToStart();
    for(int i=0; i<size; i++)
    {
        if(k<len)
            j=list.getValue();
        if(j==i)
        {
            cout<<j<<",";
            list.next();
            k++;
        }

        else
        {
            cout<<",";
        }

    }
    cout<<"\b";
    cout<<" ";
    cout<<"\n";
    list.moveToPos(curr);
}

int main()
{
    int noOfRS,noOfBS,noOfTS,taskNo;

    cin>>noOfRS;
    int arrRS[noOfRS]= {-1};
    for(int i=0; i<noOfRS; i++)
        arrRS[i]=i;

    cin>>noOfBS;
    int arrBS[noOfBS]= {-1};
    prep_arrays(arrBS,noOfBS);

    cin>>noOfTS;
    int arrTS[noOfTS]= {-1};
    prep_arrays(arrTS,noOfTS);

    cin>>taskNo;

    LList<int> RS(noOfRS,noOfRS,arrRS);
    LList<int> BS(noOfBS,noOfRS,arrBS);
    LList<int> TS(noOfTS,noOfRS,arrTS);

//    AList<int> RS(noOfRS,noOfRS,arrRS);
//    AList<int> BS(noOfBS,noOfRS,arrBS);
//    AList<int> TS(noOfTS,noOfRS,arrTS);

    printList(RS,noOfRS);
    printList(BS,noOfRS);
    printList(TS,noOfRS);
}
