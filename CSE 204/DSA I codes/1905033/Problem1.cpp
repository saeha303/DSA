#include<iostream>
#include<ctime>
using namespace std;
void DPLCS(string X, string Y)
{
    ///calculating length of LCS
    int m=X.length(),n=Y.length();
    srand(time(0));
    int L[m+1][n+1],D[m][n];///L contains length of LCS for X[0...i-1] and Y[0...j-1]
    for(int i=0; i<=m; i++)
        L[i][0]=0;///for Y==NULL
    for(int i=0; i<=n; i++)
        L[0][i]=0;///for X==NULL
    for(int i=1; i<=m; i++)///top to bottom approach
    {
        for(int j=1; j<=n; j++)
        {
            L[i][j]=max(L[i-1][j],max(L[i][j-1],L[i-1][j-1]));///common last character+lcs of the remaining strings
            D[i-1][j-1]=-1;
        }
    }
    ///constructing the LCS
    int idx=L[m][n];
    int len=idx;
    string lcs(idx,' ');
    while(m!=0 && n!=0)
    {
        if(X[m-1]==Y[n-1])
        {
            lcs[idx-1]=X[m-1];
            idx--;
        }
            m--;
            n--;
    }
    cout<<len<<'\n';
    cout<<lcs<<'\n';
}
int main()
{
    string X,Y;
    getline(cin,X);
    getline(cin,Y);
    DPLCS(X,Y);
}
