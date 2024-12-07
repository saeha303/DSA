#include<iostream>
#include<fstream>
#include<queue>
using namespace std;
class Square
{
public:
    int sqrNo;
    int dist;
    int p;
    Square(int n, int d,int parent)
    {
        sqrNo=n;
        dist=d;
        p=parent;
    }
    Square() {}
};
void write(ofstream& file,bool visited[], int X,queue<Square>& q,int parent[])
{
    if(!q.empty())
    {
        file<<q.front().dist<<'\n';
        int t=q.front().sqrNo;
        vector<int> p;
        p.push_back(t);
        while(t!=-1)
        {
            p.push_back(parent[t-1]);
            t=parent[t-1];
        }
        file<<1;
        for(int i=p.size()-3; i>=0; i--)
        {
            file<<" -> "<<p[i];
        }
        file<<'\n';
        file<<"All reachable"<<'\n';
    }
    else
    {
        file<<-1<<'\n';
        file<<"No solution"<<'\n';
        int idx;
        for(int i=X-1; !visited[i]; i--)
            idx=i;
        for(int i=idx; i<X; i++)
        {
            file<<i+1<<" ";
        }
        file<<'\n';
    }
    file<<'\n';
}
void leastRollNo(int board[],bool visited[], int X, int n,queue<Square>& q, int parent[])
{
    Square s(1,0,-1);
    q.push(s);
    parent[0]=-1;
    for(int i=0; i<X; i++)
        visited[i]=false;
    visited[0]=true;
    Square u;
    while(!q.empty())
    {
        u.sqrNo=q.front().sqrNo;
        u.dist=q.front().dist;
        u.p=q.front().p;
        int no=u.sqrNo;
        if(no==X)
        {
            break;
        }
        q.pop();
        for(int i=no+1; i<=no+n; i++)///going to each adjacent square
        {
            if(!visited[i-1] && i<=X)
            {
                visited[i-1]=true;
                if(board[i-1]!=-1)
                {
                    Square v(board[i-1],u.dist+1,i);
                    if(parent[board[i-1]-1]==-2)
                        parent[board[i-1]-1]=i;
                    if(parent[i-1]==-2)
                        parent[i-1]=i-1;
                    q.push(v);
                }
                else
                {
                    Square v(i,u.dist+1,no);
                    if(parent[i-1]==-2)
                        parent[i-1]=no;
                    q.push(v);
                }
            }
        }
    }
}
int main()
{
    ofstream ofile;
    ofile.open("output.txt",ios::out|ios::trunc);
    ifstream file("input.txt");
    int in;
    int t,n,X,l,s;
    int* board=NULL;
    bool* visited=NULL;
    int* parent=NULL;
    int i=1;
    int idx_1,idx_2,temp=0;
    file>>in;
    t=in;
    while(true)
    {
        if(i==1)
        {
            t=in;
        }
        else if(i==2)
        {
            n=in;
        }
        else if(i==3)
        {
            X=in;
            if(board!=NULL)
                delete[] board;
            board=new int[X];
            if(visited!=NULL)
                delete[] visited;
            visited=new bool[X];
            if(parent!=NULL)
                delete[] parent;
            parent=new int[X];
            for(int j=0; j<X; j++)
            {
                board[j]=-1;
                parent[j]=-2;
            }
        }
        else if(i==4)
        {
            l=in;
        }
        else if(i>=5 && i<=5+2*l-1)
        {

            if(i%2)
                idx_1=in;
            else
                board[idx_1-1]=in;
            idx_2=5+2*l;
        }
        else if(i==idx_2)
        {
            s=in;
        }
        else if(i>=(idx_2+1) && i<=(idx_2+1+2*s-1))
        {
            if(i%2==0)
            {
                idx_1=in;
            }
            else
            {
                board[idx_1-1]=in;
            }
            if(i==idx_2+1+2*s-1)
            {
                i=1;
                queue<Square> q;
                leastRollNo(board,visited,X,n,q,parent);
                write(ofile,visited,X,q,parent);
                temp++;
            }
        }
        file>>in;
        i++;
        if(temp==t)
            break;
    }
    delete[] board;
    delete[] visited;
    delete[] parent;
    file.close();
    ofile.close();
}
