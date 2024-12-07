#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
    int N,K;
    cin>>N>>K;
    int t;
    vector<int> A;//int
    for(int i=0;i<N;i++)
    {
        cin>>t;
        A.push_back(t);
    }
    sort(A.begin(),A.end());
    long long price=0;
    int p[K];//int
    for(int i=0;i<K;i++)
    {
        p[i]=0;
    }
    int i=0;
    while(A.size())
    {

        i%=K;
        price+=A.back()*(p[i]+1);
        A.pop_back();
        p[i]++;
        i++;
    }
    cout<<price<<'\n';
}
