#include<bits/stdc++.h>
#include<ctime>
#include<cstdlib>
using namespace std;
void DPSCS(string X, string Y)
{
    ///calculating length of LCS
    int m=X.length(),n=Y.length();
    srand(time(0));
    int L[m+1][n+1],D[m][n];
    for(int i=0; i<=m; i++)
        L[i][0]=0;
    for(int i=0; i<=n; i++)
        L[0][i]=0;
    for(int i=1; i<=m; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(X[i-1]==Y[j-1])
            {
                L[i][j]=L[i-1][j-1]+1;
                D[i-1][j-1]=1;
            }
            else
            {
                if(L[i-1][j]>L[i][j-1])
                {
                    L[i][j]=L[i-1][j];
                    D[i-1][j-1]=2;
                }
                else
                {
                    if(L[i-1][j]==L[i][j-1])
                    {
                        D[i-1][j-1]=(rand()%2)+2;
                        L[i][j]=L[i][j-1];
                    }
                    else
                    {
                        D[i-1][j-1]=3;
                        L[i][j]=L[i][j-1];
                    }
                }
            }
        }
    }

    ///constructing the LCS
    int idx=m+n-L[m][n];
    int len=idx;
    string lcs(len,' ');
    while(m!=0 && n!=0)
    {
        if(D[m-1][n-1]==1)
        {
            lcs[idx-1]=X[m-1];
            m--;
            n--;
            idx--;
        }
        else if(D[m-1][n-1]==2)
        {
            lcs[idx-1]=X[m-1];
            idx--;
            m--;

        }

        else if(D[m-1][n-1]==3)
        {
            lcs[idx-1]=Y[n-1];
            idx--;
            n--;
        }


    }
    while(m>0)
    {
        lcs[idx-1]=X[m-1];
        idx--;m--;
    }
    while(n>0)
    {
        lcs[idx-1]=Y[n-1];
        idx--;n--;
    }
    cout<<len<<'\n';
    cout<<lcs<<'\n';
}
int main()
{
    string X,Y;
    getline(cin,X);
    getline(cin,Y);
    DPSCS(X,Y);
}
