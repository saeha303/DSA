#include<bits/stdc++.h>
using namespace std;
int coin(int c[], int n, int a)
{
    int dp[a+1][a+1];
    memset(dp,-1,sizeof dp);
    for(int i=0; i<=a; i++)
        dp[i][0]=0;///for Y==NULL
    for(int i=0; i<=a; i++)
        dp[0][i]=0;///for X==NULL
    int k=0;
    for(int i=1; i<=a; i++)
    {
        if(i==c[k])
        {
            for(int j=1; j<=a; j++)
            {
                if(j%i)
                {
                    dp[i][j]=dp[i][j-1]+1;
                }
                else
                {
                    dp[i][j]=j/i;
                }

            }
            k++;
        }
    }
    for(int i=1; i<=a; i++)
    {
        for(int j=1; j<=a; j++)
            cout<<dp[i][j]<<" ";
        cout<<'\n';
    }
    return dp[c[n-1]][a];
}
int main()
{
    int c[]= {1,5,6,9};
    cout<<coin(c,4,11);
}
