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
    int fc;
    int fr;
    package()
    {

    }
    bool operator< (const package & p)const
    {
        if(bound==p.bound)
        {
            if(level==p.level)
            {
                return order<p.order;
            }
            else
            {
                return level<p.level;
            }
        }
        else
        {
            return bound>p.bound;
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
int boundOfUnfixed(package &p1)
{
    int uc=p1.fc+1;
    int ur=p1.fr+1;
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
    if(p1.fc==-1 && p1.fr==-1)
    {
        return 0;
    }
    int cf=0,cu=0,columnMax=0;
    int temp;
    for(int i=0; i<=p1.fc; i++)
    {
        if(i>p1.fr)
        {
            temp=1;
        }
        else
            temp=0;
        for(int j=0; j<=i-temp; j++)///i>fr
        {
            if(p1.mat[j][i]=='X')
            {
                cf=i-j+1;
                break;
            }
        }
        bool flag=false;
        for(int j=p1.fr+1; j<n; j++)
        {
            if(p1.mat[j][i]=='X')
            {
                flag=true;
                break;
            }
        }
        if(flag)
        {
            cu=p1.fr-i+1;
            for(int j=p1.fr+1; j<n; j++)
            {

                if(p1.mat[j][i]=='X')
                {
                    cu++;
                }
            }
        }
        else
        {
            for(int j=p1.fr; j>=i; j--)
            {
                if(p1.mat[j][i]=='X')
                {
                    cu=j-i+1;
                    break;
                }
            }
        }

//        }

        int t=max(cf,cu);
        if(t>columnMax)
        {
            columnMax=t;
        }
        cf=0;
        cu=0;
    }

    ///for row
    int rf=0,ru=0,rowMax=0;
    for(int i=0; i<=p1.fr; i++)
    {
        for(int j=0; j<=i; j++)
        {
            if(p1.mat[i][j]=='X')
            {
                rf=i-j+1;
                break;
            }
        }
        bool flag=false;
        for(int j=p1.fc+1; j<n; j++)
        {
            if(p1.mat[i][j]=='X')
            {
                flag=true;
                break;
            }
        }
        if(flag)
        {
            ru=p1.fc-i+1;
            for(int j=p1.fc+1; j<n; j++)
            {
                if(p1.mat[i][j]=='X')
                {
                    ru++;
                }
            }
        }
        else
        {
            for(int j=p1.fc; j>=i; j--)
            {
                if(p1.mat[i][j]=='X')
                {
                    ru=j-i+1;
                }
            }
        }
        int t=max(rf,ru);
        if(t>rowMax)
        {
            rowMax=t;
        }
        rf=0;
        ru=0;
    }
    return max(columnMax,rowMax);
}
int fixCol(package &p1,int o)///OK
{
    char t[n];
    for(int i=0; i<n; i++)
    {
        t[i]=p1.mat[i][p1.fc];
    }
    for(int i=0; i<n; i++)
    {
        p1.mat[i][p1.fc]=p1.mat[i][o];
    }
    for(int i=o; i>=p1.fc+1; i--)
    {
        for(int j=0; j<n; j++)
        {
            if(i==p1.fc+1)
            {
                p1.mat[j][i]=t[j];
            }
            else
                p1.mat[j][i]=p1.mat[j][i-1];

        }

    }
}
int fixRow(package &p1,int o)///OK
{
    char t[n];
    for(int i=0; i<n; i++)
    {
        t[i]=p1.mat[p1.fr][i];
    }
    for(int i=0; i<n; i++)
    {
        p1.mat[p1.fr][i]=p1.mat[o][i];
    }
    for(int i=o; i>=p1.fr+1; i--)
    {
        for(int j=0; j<n; j++)
        {
            if(i==p1.fr+1)
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
    pq.push(p1);
}
int BnB()
{
    while(true)
    {
        o=1;
        package p=pq.top();
        pq.pop();
        p.order=o;
        if(p.fc==p.fr)
        {
            p.fc++;
        }
        else
        {
            p.fr++;
        }
        if(p.fc==n-1 && p.fr==n-1)
        {
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
        if(p.fc>p.fr)
        {
            for(int i=p.fc; i<n; i++)
            {
                package tp=p;
                fixCol(tp,i);
                fix(tp);
                p.order++;
            }
            p.level++;
        }
        if(p.fc==p.fr)
        {
            for(int i=p.fr; i<n; i++)
            {
                package tp=p;
                fixRow(tp,i);
                fix(tp);
                p.order++;
            }
            p.level++;
        }
    }

}

int main()
{
    ifstream file("input.txt");
    file>>n;
    package p1;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            file>>p1.mat[i][j];
        }
    }
    file.close();
    p1.fc=-1;
    p1.fr=-1;
    p1.level=1;
    p1.order=1;
    fix(p1);
    l++;
    BnB();
    return 0;
}
