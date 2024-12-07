#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a=20;
    int *x=&a;
    int* np=x;
    int b=30;
    x=&b;
    cout<<*np<<'\n';
    cout<<*x<<'\n';
}
