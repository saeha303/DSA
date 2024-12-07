#include<iostream>
#include<fstream>
#include<queue>
using namespace std;
class Square
{
public:
    int sqrNo;
    int dist;
    Square(int n, int d)
    {
        sqrNo=n;
        dist=d;
    }
};
void write(ofstream& file,int rollNo,bool visited[], int X)
{
    if(visited[X-1])
    {
        file<<rollNo<<'\n';
        for(int i=0; i<X-1; i++)
        {
            if(visited[i])
                file<<i+1<<" -> ";
        }
        file<<X;
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
int leastRollNo(int board[],bool visited[], int X, int n)
{
    int rollNo=0;
    queue<Square> q;
    Square s(1,0);
    q.push(s);
    int max_l=0;///to track the ladder that leads to the highest numbered square
    bool nlflag=false;///if there is no ladder in adjacent squares
    for(int i=0; i<X; i++)
        visited[i]=false;
    visited[0]=true;
    while(!q.empty())
    {
        Square u=q.front();
        q.pop();
        if(u.sqrNo==X)
        {
            visited[u.sqrNo-1]=true;
            break;
        }
        for(int i=1; i<=n; i++)///going to each adjacent square
        {
            if(u.sqrNo+i-1<X)
            {
                if(board[u.sqrNo+i-1]!=-1 && (u.sqrNo+i)<board[u.sqrNo+i-1] && board[max_l]<board[u.sqrNo+i-1])//searching for ladder
                {
                    max_l=u.sqrNo+i-1;
                    nlflag=false;
                }
                if(i==n && max_l==0)///when there is no ladder in adjacent squares, either snake or nothing
                    nlflag=true;
            }
            else
                break;
        }
        if(nlflag)
        {
            if(u.sqrNo+n<=X)
            {
            if(board[u.sqrNo+n-1]<u.sqrNo+n && board[u.sqrNo+n-1]!=-1)///when there is no ladder or empty squares in adjacent squares, only snake
            {
                visited[u.sqrNo-1]=true;
                visited[u.sqrNo+n-1]=true;
                break;
            }
                Square v(u.sqrNo+n,u.dist+1);///when there is no ladder in adjacent squares, only empty squares or snake and empty squares mixed
                q.push(v);
            }
            else
            {
                Square v(X,u.dist+1);///when there is no ladder in adjacent squares, only empty squares or snake and empty squares mixed
                q.push(v);
                visited[X-1]=true;
            }
            visited[u.sqrNo-1]=true;
            rollNo++;
        }
        else if(!nlflag && max_l)///there is a ladder in one adjacent square
        {
            Square v(board[max_l],u.dist+2);
            q.push(v);
            visited[u.sqrNo-1]=true;
            visited[max_l]=true;
            rollNo++;
        }
        max_l=0;///initializing for the next square
    }
    return rollNo;
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
            for(int j=0; j<X; j++)
            {
                board[j]=-1;
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
                int rollNo=leastRollNo(board,visited,X,n);
                write(ofile,rollNo,visited,X);
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
    file.close();
    ofile.close();
}
