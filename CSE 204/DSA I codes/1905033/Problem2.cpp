#include<bits/stdc++.h>
using namespace std;
int cost[11][11];
int dp[11][1<<11];///costs are saved here
int solve(int i, int mask, int &n)///current city i
{
    if(i==n)
        return 0;
    if(dp[i][mask]!=-1)
        return dp[i][mask];
    int ans=INT_MAX;
    for(int j=0; j<n; j++)///if jth city is visited
    {
        int t=0;
        if(mask&(1<<j))
        {
            for(int k=0; k<n; k++)
            {
                if(!(mask&(1<<k)))
                {
                    t+=cost[j][k];
                }
            }
            ans=min(ans,cost[j][j]+t+solve(i+1,(mask^(1<<j)),n));
        }
    }
    return dp[i][mask]=ans;
}
int main()
{
    int t,n,m,x,i,j,k,q;
    t=1;
    memset(dp,-1,sizeof dp);
    while(t--)
    {
        cin>>n;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                cin>>cost[i][j];
            }
        }
        cout<<solve(0,(1<<n)-1,n)<<'\n';
    }
}

