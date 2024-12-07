#include <bits/stdc++.h>
using namespace std;
class DisjointSet
{
    int* parent;
    int n;
public:
    DisjointSet(int n)
    {
        parent = new int[n];
        this->n=n;
        makeSet();
    }
    void makeSet()
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return find(parent[i]);
    }
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);
        if (s1 != s2)
        {
            parent[s1] = s2;
        }
    }
};
class Edge
{
    int src, dest;
    double wt;
public:
    Edge(int s, int d, double w):src(s),dest(d),wt(w) {}
    int getSrc()
    {
        return src;
    }
    int getDest()
    {
        return dest;
    }
    double getWt()
    {
        return wt;
    }
    bool operator<(const Edge& e) const
    {
        return wt<e.wt;
    }
};
class Graph
{
    vector<Edge> edgelist;
    int V;
public:
    Graph(int V)
    {
        this->V = V;
    }
    void addEdge(int x, int y, double w)
    {
        edgelist.push_back(Edge(x, y, w));
    }
    void kruskals_mst()
    {
        sort(edgelist.begin(), edgelist.end());
        DisjointSet s(V);
        queue<pair<int,int>> q;
        for (auto edge : edgelist)
        {
            double w = edge.getWt();
            int x = edge.getSrc();
            int y = edge.getDest();
            if (s.find(x) != s.find(y))
            {
                s.unite(x, y);
                q.push(make_pair(x,y));
            }
        }
        cout << "List of edges selected by Kruskal's:{";
        while(q.size())
        {
            cout<<'('<<q.front().first<<','<<q.front().second<<"),";
            q.pop();
        }
        cout<<"\b";
        cout<<"}\n";
    }
    void primMST()
    {
        priority_queue< pair<double, int>, vector <pair<double, int>>, greater<pair<double, int>> > pq;
        int src = 0;
        double ans=0;
        vector<double> key(V, INT_MAX);
        vector<int> parent(V, -1);
        vector<bool> inMST(V, false);
        pq.push(make_pair(0, src));
        key[src] = 0;
        while (!pq.empty())
        {
            int u = pq.top().second;
            cout<<u<<' ';
            pq.pop();
            if(inMST[u] == true)
            {
                continue;
            }
            inMST[u] = true;
            vector< Edge >::iterator i;
            int v;
            for (i = edgelist.begin(); i != edgelist.end(); ++i)
            {
                if((*i).getSrc()==u || (*i).getDest()==u)
                {
                    if((*i).getSrc()==u)
                        v = (*i).getDest();
                    else
                        v=(*i).getSrc();
                    double weight = (*i).getWt();
                    if (inMST[v] == false && key[v] > weight)
                    {
                        key[v] = weight;
                        pq.push(make_pair(key[v], v));
                        parent[v] = u;
                    }
                }
            }
        }
        cout<<'\n';
        for(int i=0; i<V; i++)
            ans+=key[i];
        cout << "Cost of the minimum spanning tree: " <<(double) ans<<'\n';
        cout << "List of edges selected by Prim's:{";
        for(int i=1; i<V; i++)
            cout<<'('<<parent[i]<<','<<i<<"),";

        cout<<"\b";
        cout<<"}\n";
    }
};
int main()
{
    int V,E;
    int s1,s2;
    double w;
    ifstream file("mst.txt");
    file>>V>>E;
    Graph g(V);
    while(E--)
    {
        file>>s1>>s2>>w;
        g.addEdge(s1,s2,w);
    }
    file.close();
    g.primMST();
    g.kruskals_mst();
    return 0;
}
