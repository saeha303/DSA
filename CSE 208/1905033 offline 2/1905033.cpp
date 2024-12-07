#include<bits/stdc++.h>
using namespace std;
class Edge
{
    int dest,weight;
public:
    Edge(int d, int w):dest(d),weight(w) {}
    int getDest()
    {
        return dest;
    }
    int getWeight()
    {
        return weight;
    }
    int& setDest()
    {
        return dest;
    }
    int& setWeight()
    {
        return weight;
    }
};
class Graph
{
    int V,E;
    vector<Edge> *adj;
public:
    Graph(int V, int E);
    void addEdge(int u, int v, int w=1)
    {
        adj[u].push_back(Edge(v,w));
        E++;
    }
    void deleteEdge(int v, int w)
    {
        int i=0;
        for(auto x:adj[v])
        {

            if(x.getDest()==w)
            {
                adj[v].erase(adj[v].begin()+i);
                break;
            }
            i++;
        }
    }
    void Dijkstra(int, int);
    void Bellman_Ford(int, int);
    ~Graph()
    {
        delete[] adj;
    }
};

Graph::Graph(int V,int E=0)
{
    this->V = V;
    this->E = E;
    adj = new vector<Edge>[V];
}
void Graph::Dijkstra(int s1, int s2)///O((V+E)logV)
{
    priority_queue< pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>> > pq;///d,vertex
    double ans=0;
    vector<int> d(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inSP(V,false);
    pq.push(make_pair(0, s1));
    d[s1] = 0;

    while (!pq.empty())///O(V)
    {
        int u = pq.top().second;
        cout<<u<<'\n';
        pq.pop();///O(logV)
        if(inSP[u])
            continue;
        inSP[u]=true;
        vector< Edge >::iterator i;
        int v;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)///O(E)
        {

            v = (*i).getDest();
            double weight = (*i).getWeight();
            if (!inSP[v]&&d[v] >d[u]+ weight)
            {
                d[v] = d[u]+weight;
                pq.push(make_pair(d[v], v));///O(logV)
                parent[v] = u;
            }
        }
    }
    if(d[s2]!=INT_MAX)
    {
        cout<<"Shortest path cost: ";
        cout <<d[s2]<<'\n';
        stack<int> s;
        s.push(s2);
        while(true)
        {
            s.push(parent[s2]);
            s2=parent[s2];
            if(parent[s2]==-1)
                break;
        }
        while(!s.empty())
            cout<<s.top()<<"->",s.pop();

        cout<<"\b\b";
        cout<<"  ";
        cout<<'\n';
    }
    else
    {
        cout<<"Destination vertex is not reachable"<<'\n';
    }
}
void Graph::Bellman_Ford(int s1, int s2)
{
    vector<int> d(V, INT_MAX);
    vector<int> parent(V, -1);
    d[s1] = 0;
    int v;
    vector< Edge >::iterator k;
    for(int i=1; i<V; i++)
    {
        for(int j=0; j<V; j++)
        {
            for (k = adj[j].begin(); k != adj[j].end(); ++k)
            {

                v = (*k).getDest();
                double weight = (*k).getWeight();
                if (d[v] >d[j]+ weight)
                {
                    d[v] = d[j]+weight;
                    parent[v] = j;
                }
            }
        }
    }
    bool flag=false;
    for(int j=0; j<V; j++)
    {
        for (k = adj[j].begin(); k != adj[j].end(); ++k)
        {

            v = (*k).getDest();
            double weight = (*k).getWeight();
            if (d[v] >d[j]+ weight)
            {
                d[v] = d[j]+weight;
                flag=true;
                break;
            }
        }
    }
    if(!flag)
    {
        cout<<"The graph does not contain a negative cycle"<<'\n';
        cout<<"Shortest path cost: ";
        cout <<d[s2]<<'\n';
        stack<int> s;
        s.push(s2);
        while(true)
        {
            s.push(parent[s2]);
            s2=parent[s2];
            if(parent[s2]==-1)
                break;
        }
        while(!s.empty())
            cout<<s.top()<<"->",s.pop();

        cout<<"\b\b";
        cout<<"  ";
        cout<<'\n';
    }
    else
        cout<<"The graph contains a negative cycle"<<'\n';
}
int main()
{
    int V,E;
    int s1,s2,w;
    cin>>V>>E;
    Graph g(V),rg(V);
    while(E--)
    {

        cin>>s1>>s2>>w;
        g.addEdge(s1,s2,w);
    }
    cin>>s1>>s2;

    g.Dijkstra(s1,s2);

    g.Bellman_Ford(s1,s2);
    return 0;
}
