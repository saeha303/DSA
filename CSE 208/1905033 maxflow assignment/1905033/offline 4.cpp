#include <bits/stdc++.h>
using namespace std;
class league
{
private:
    int n;
    vector<string> names;
    vector<int> w, l, r;//win,loss,residual
    vector<vector<int>> g;
public:
    league(int n,vector<string> &names,vector<int> &w, vector<int> &l, vector<int> &r,vector<vector<int>> &g)
    {
        this->n = n;
        this->names = names;
        this->w = w;
        this->l = l;
        this->r = r;
        this->g = g;
    }

    int getN()
    {
        return this->n;
    }

    vector<string> getNames()
    {
        return this->names;
    }

    vector<int> getW()
    {
        return this->w;
    }

    vector<int> getL()
    {
        return this->l;
    }

    vector<int> getR()
    {
        return this->r;
    }

    vector<vector<int>> getG()
    {
        return this->g;
    }
    int getIdx(string s)
    {
        for(int i=0;i<n;i++)
            if(names[i]==s)
                return i;
    }
};

class flowNetwork
{
private:
    int n, curTeam, numGames;
    vector<string> nodes;///for name of nodes
    vector<vector<int>> capMat, edges;///capMat=residual flow network,edges=adjacency list
public:
    flowNetwork(league &l, int curTeam)
    {
        cout<<curTeam<<'\n';
        this->curTeam = curTeam;
        this->numGames = (l.getN() - 1) * (l.getN() - 2) / 2;///except curTeam,game nodes
        this->n= (l.getN() - 1 )+ numGames + 2;///+s+t
        cout<<this->n<<'\n';
        vector<vector<int>> cap(n, vector<int>(n, 0));///original flow network
        vector<vector<int>> e(n);///adjacency list for easy bfs traversal
        vector<string> nod(n, "");///name of the nodes
        nod[0] = "s";
        nod[n - 1] = "t";
        int k = 1, add = 0;
        for (int i = 0; i <l.getN() ; i++)
        {
            if (i == curTeam)
                continue;
            vector<int> temp = l.getG()[i];///number of games left against each team
            for (int j = i + 1; j < l.getN() ; j++)
            {
                            cout<<"hi1"<<'\n';

                if(j==curTeam)
                    continue;
                cap[0][k]=temp[j];
                e[0].push_back(k);
                nod[k] = to_string(i) + "-" + to_string(j);
                if (i < curTeam)
                    add = 1;
                else
                    add = 0;
                cap[k][numGames+i+add]=INT_MAX;
                e[k].push_back(numGames+i+add);
                nod[numGames+i+add]=l.getNames()[i];
                if (j < curTeam)
                    add = 1;
                else
                    add = 0;
                cap[k][numGames+j+add]=INT_MAX;
                e[k].push_back(numGames+j+add);
                nod[numGames+j+add]=l.getNames()[j];

                if(i+j-2<0){
//                                                                            cout<<"hi3"<<'\n';

                    cap[k+numGames][n-1]=l.getW()[curTeam]+l.getR()[curTeam]-l.getW()[0];

                }
                else{
//                                                                            cout<<cap[k+numGames][n-1]<<'\n';

                    cap[k+numGames][n-1]=l.getW()[curTeam]+l.getR()[curTeam]-l.getW()[i+j-2];

                }
                e[k+numGames].push_back(n-1);
                k++;
                cout<<k<<'\n';

            }
            for(int j=0;j<n;j++){
                  for(int ii=0;ii<n;ii++)
                cout<<cap[j][ii]<<' ';
            cout<<'\n';
            }

        }
        this->nodes = nod;
        this->capMat = cap;
        this->edges = e;
    }
    vector<int> bfs(vector<vector<int>> &resNet)
    {
        vector<int> path(resNet.size(), INT_MIN);///parent array
        vector<bool> visited(resNet.size(), false);
        queue<int> q;
        visited[0] = true;
        q.push(0);
        while (!q.empty())
        {
            int i = q.front();
            q.pop();
            for (int j = 0; j < this->edges[i].size(); j++)
            {
                if (!visited[edges[i][j]] && resNet[i][edges[i][j]])
                {
                    visited[edges[i][j]] = true;
                    path[edges[i][j]] = i;
                    q.push(edges[i][j]);
                    if (visited[this->n - 1])
                        return path;
                }
            }
        }
        return path;
    }
    void dfs(vector<vector<int>> &resNet, int s, vector<bool> &visited)
    {
        visited[s] = true;
        for (int i = 0; i < n; i++)
            if (resNet[s][i] && !visited[i])
                dfs(resNet, i, visited);
    }
    void Edmond_Karp(league &l)
    {
        vector<int> path;
        vector<vector<int>> resNet(this->n, vector<int>(this->n, 0));///residual network
        int maxFlow = 0, saturation = 0;
        resNet = this->capMat;
        for (int j = 0; j < this->n; j++)
            saturation += this->capMat[0][j];
        path = this->bfs(resNet);
        while (path[this->n - 1] != INT_MIN)///zero flow in all the paths to target
        {
            int bottleneck = INT_MAX;
            for (int i = this->n - 1; i > 0; i = path[i])
                bottleneck = bottleneck < resNet[path[i]][i] ? bottleneck : resNet[path[i]][i];///to find out the narrowest path
            for (int i = this->n - 1; i > 0; i = path[i])
            {
                resNet[path[i]][i] -= bottleneck;
                resNet[i][path[i]] += bottleneck;
            }
            maxFlow += bottleneck;
            path = this->bfs(resNet);
        }
        if (saturation == maxFlow)
            return;
        else
        {
            vector<bool> visited(this->n, false);
            dfs(resNet, 0, visited);
            vector<int> inR;
            cout << l.getNames()[curTeam] << " is eliminated.\nThey can win at most " << l.getW()[curTeam] << " + " << l.getR()[curTeam] << " = " << l.getW()[curTeam] + l.getR()[curTeam] << " games.\n";

                for (int i = 0; i < n; i++)
                {
                    if (i>numGames && visited[i])
                        inR.push_back(i);
                }
            int i=0,wins=0,size=inR.size(),remains=0;
            int temp=size;
            for(auto x:inR)
            {
                int skip;
                if(i<curTeam)
                    skip=1;
                else
                    skip=0;
                temp--;
                cout<<nodes[x]<<' ';
                if(temp)
                    cout<<"and ";
                wins+=l.getW()[x-numGames-skip];
                i++;
            }
            for(auto x:inR)
                for(auto y:inR)
                {
                    remains+=l.getG()[l.getIdx(nodes[x])][l.getIdx(nodes[y])];
                }
            remains/=2;
            cout << " have won a total of " << wins << " games.\nThey play each other " << remains << " times.\nSo on average, each of the team wins " << wins + remains << "/" << size << " = " << float(wins + remains) / float(size) << " games.\n\n";
        }
    }
};

void eliminateTeams(league &l)
{
    int maxpos = 0, max = l.getW()[0];///team that has max win
    for (int i = 1; i < l.getN(); i++)
    {
        if (l.getW()[i] > max)
        {
            max = l.getW()[i];
            maxpos = i;
        }
    }
    for (int i = 0; i < l.getN(); i++)
    {
        if (l.getW()[i] + l.getR()[i] < l.getW()[maxpos])
            cout << l.getNames()[i] << " is eliminated.\nThey can win at most " << l.getW()[i] << " + " << l.getR()[i] << " = " << l.getW()[i] + l.getR()[i] << " games.\n" << l.getNames()[maxpos] << " has won a total of " << l.getW()[maxpos] << " games.\nThey play each other 0 times.\nSo on average, each of the teams in this group wins " << l.getW()[maxpos] << "/1 = " << l.getW()[maxpos] << " games.\n\n";
        else
        {
            flowNetwork fn(l, i);
            fn.Edmond_Karp(l);
        }
    }
}

int main()
{
    int n;
    cin>>n;
    vector<string> names(n);
    vector<int> w(n,0),l(n,0),r(n,0);
    vector<vector<int>> g(n,vector<int> (n,0));
    string t;
    int temp;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(j==0)
                cin>>t,names[i]=t;
            if(j==1)
                cin>>temp,w[i]=temp;
            if(j==2)
                cin>>temp,l[i]=temp;
            if(j==3)
                cin>>temp,r[i]=temp;
        }
        for(int j=0; j<n; j++)
        {
            cin>>g[i][j];
        }
    }
//    for(int i=0; i<n; i++)
//    {
//        for(int j=0; j<4; j++)
//        {
//            if(j==0)
//                cout<<names[i];
//            if(j==1)
//                cout<<w[i];
//            if(j==2)
//                cout<<l[i];
//            if(j==3)
//                cout<<r[i];
//        }
//        for(int j=0; j<n; j++)
//        {
//            cout<<g[i][j];
//        }
//    }
    league ll(n,names,w,l,r,g);
    eliminateTeams(ll);

}
