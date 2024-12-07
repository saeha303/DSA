#include<bits/stdc++.h>
using namespace std;
int n;
int fc,fr;
int l,o;
class package
{
public:
    char mat[20][20];
    int bound;
    int level;
    int order;
    bool operator< (const package & p)const
    {
        if(bound==p.bound)
        {
            if(level==p.level)
            {
                return order>p.order;
            }
            else
            {
                return level>p.level;
            }
        }
        else
        {
            return bound<p.bound;
        }
    }
    void takeInput()
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                cin>>mat[i][j];
            }
        }
    }
    void print()
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                cout<<mat[i][j]<<' ';
            }
            cout<<'\n';
        }
    }
};
priority_queue<package> pq;
int boundOfUnfixed(package &p1)///OK
{
    int uc=fc+1;
    int ur=fr+1;
    int cm=0,rm=0,count=0;
    for(int i=uc; i<n; i++)
    {
        for(int j=ur; j<n; j++)
        {
            if(p1.mat[j][i]=='X')
            {
                count++;
            }

        }
        int t=floor((count+1)/2);
        if(t>cm)
        {
            cm=t;
        }
        count=0;
    }
    count=0;
    for(int i=ur; i<n; i++)
    {
        for(int j=uc; j<n; j++)
        {
            if(p1.mat[i][j]=='X')
            {
                count++;
            }

        }
        int t=floor((count+1)/2);
        if(t>rm)
        {
            rm=t;
        }
        count=0;
    }
    return max(cm,rm);
}
int boundOfFixed(package &p1)
{
    if(fc==-1 && fr==-1)
    {
        return 0;
    }
    int temp;
    int cf=1,cu=0,columnMax=0;
    for(int i=0; i<=fc; i++)
    {
        for(int j=i-1; j>=0; j--)
        {
            if(p1.mat[j][i]=='X')
            {
                cf++;
            }
        }
        if(fr<i)
        {
            temp=0;
        }
        else
        {
            temp=1;
        }
        for(int j=i+temp; j<n; j++)
        {
            if(j<=fr)
                cu++;
            if(j>fr && p1.mat[j][i]=='X')
            {
                cu++;
            }
        }
        int t=max(cf,cu);
        if(t>columnMax)
        {
            columnMax=t;
        }
        cf=1;
        cu=0;
    }
    int rf=1,ru=0,rowMax=0;
    for(int i=0; i<=fr; i++)
    {
        for(int j=i-1; j>=0; j--)
        {
            if(p1.mat[i][j]=='X')
            {
                rf++;
            }
        }
        if(fc>i)
        {
            temp=1;
        }
        else
        {
            temp=0;
        }
        for(int j=i+temp; j<n; j++)
        {
            if(j<=fc)
                ru++;
            if(j>fc && p1.mat[i][j]=='X')
            {
                ru++;
            }
        }
        int t=max(rf,ru);
        if(t>rowMax)
        {
            rowMax=t;
        }
        rf=1;
        ru=0;
    }
    return max(columnMax,rowMax);
}
int fixCol(package &p1,int fc, int o)
{
    char t[n];
    for(int i=0; i<n; i++)
    {
        t[i]=p1.mat[i][fc];
    }
    for(int i=0; i<n; i++)
    {
        p1.mat[i][fc]=p1.mat[i][o];
    }
    for(int i=o; i>=fc+1; i--)
    {
        for(int j=0; j<n; j++)
        {
            if(i==fc+1)
            {
                p1.mat[j][i]=t[j];
            }
            else
                p1.mat[j][i]=p1.mat[j][i-1];

        }

    }
}
int fixRow(package &p1,int fr, int o)
{
    char t[n];
    for(int i=0; i<n; i++)
    {
        t[i]=p1.mat[fr][i];
    }
    for(int i=0; i<n; i++)
    {
        p1.mat[fr][i]=p1.mat[o][i];
    }
    for(int i=o; i>=fr+1; i--)
    {
        for(int j=0; j<n; j++)
        {
            if(i==fr+1)
            {
                p1.mat[i][j]=t[j];
            }
            else
                p1.mat[i][j]=p1.mat[i-1][j];
        }
    }
}
void fix(package &p1)
{
    int ub=boundOfUnfixed(p1);
    int fb=boundOfFixed(p1);
    int mb=max(ub,fb);
    p1.bound=mb;
    p1.level=l;
    p1.order=o;
    pq.push(p1);
}
int BnB()
{
    while(true)
    {
        if(fc==fr)
        {
            fc++;
        }
        else
        {
            fr++;
        }
        if(fc==n-1 && fr==n-1)
        {
            package p=pq.top();
            ofstream file("output.txt");
            file<<p.bound<<'\n';
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    file<<p.mat[i][j]<<' ';
                }
                file<<'\n';
            }
            file.close();
            break;//just print here the whole thing
        }
        package p=pq.top();
        pq.pop();
        if(fc>fr)
        {
            for(int i=fc; i<n; i++)
            {
                package tp=p;
                fixCol(tp,fc,i);
                fix(tp);
                o++;
            }
            l++;
            o=1;
        }
        if(fc==fr)
        {
            for(int i=fr; i<n; i++)
            {
                package tp=p;
                fixRow(tp,fr,i);
                fix(tp);
                o++;
            }
            l++;
            o=1;
        }
    }

}

int main()
{
    ifstream file("input.txt");
    file>>n;
    int t=n;
    package p1;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            file>>p1.mat[i][j];
        }
    }
    file.close();
    fc=-1;
    fr=-1;
    l=1;
    o=1;
    fix(p1);
    l++;
    BnB();
    return 0;
}
