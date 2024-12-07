#include<bits/stdc++.h>
#include<ctime>
using namespace std;
int L[100][100];
string X,Y;
int M,N;
string construct(string l)
{
    int idx=L[M][N];
    while(M!=0 && N!=0)
    {
        if(X[M-1]==Y[N-1])
        {
            l[idx-1]=X[M-1];
            M--;
            N--;
            idx--;
        }
        else
        {
            if(L[M-1][N]>L[M][N-1])
            {

            }
        }
    }
}
int DPLCS(int m, int n)
{
    ///calculating length of LCS
    if(m==0)
        return 0;
    if(n==0)
        return 0;
    if(L[m][n]!=-1)
        return L[m][n];
    if(X[m-1]==Y[n-1])
    {
        L[m][n]=1+DPLCS(m-1,n-1);
    }
    else
    {
        L[m][n]=max(DPLCS(m,n-1),DPLCS(m-1,n));
    }
    M=m;
    N=n;
    return L[m][n];
}
int main()
{
    getline(cin,X);
    getline(cin,Y);
    memset(L,-1,sizeof L);
    cout<<DPLCS(X.length(),Y.length())<<'\n';
    string l(L[M][N],' ');
    cout<<construct(l);
}
