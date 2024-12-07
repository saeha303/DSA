#include<bits/stdc++.h>
using namespace std;
template <typename E>
class Node
{
public:
    Node *p;
    Node *l;
    Node *r;
    Node *c;
    int d,v;
    E k;
    bool m;
    Node(E k,int v)
    {
        p=NULL;
        l=this;
        r=this;
        c=NULL;
        this->k=k;
        this->v=v;
        d=0;
        m=false;
    }
};
template <typename E>
class fibHeap
{
    Node<E>* min;
    int n;
    vector<Node<E>*> track;
    int Fibonnaci_link(Node<E> *y, Node<E> *z)
    {
        (y->l)->r = y->r;
        (y->r)->l = y->l;
        if (z->r == z)
            min = z;
        y->l = y;
        y->r = y;
        y->p = z;

        if (z->c == NULL)
            z->c = y;

        y->r = z->c;
        y->l = (z->c)->l;
        ((z->c)->l)->r = y;
        (z->c)->l = y;

        if (y->k < (z->c)->k)
            z->c = y;
        z->d++;
    }
    void consolidate()
    {
        int size=floor(log2(n));
        vector<Node<E>*> A(size+1,NULL);
        Node<E>* x=min;
        Node<E>* p;
        while(true)
        {
            int d=x->d;
            while(A[d]!=NULL)
            {

                Node<E>* y=A[d];
                ///big key is pointed by y
                if((x->k)>(y->k))
                {
                    p=x;
                    x=y;
                    y=p;
                }
                if(y==min)
                {
                    min=x;
                }
                y->p=x;
                y->l->r=y->r;
                y->r->l=y->l;
                y->l=y;
                y->r=y;
                x->d=(x->d)+1;
                y->m=false;
                ///making y the child of x
                if(x->c==NULL)
                {
                    x->c=y;
                }
                else
                {
                    y->r=x->c->r;
                    y->l=x->c;
                    x->c->r->l=y;
                    x->c->r=y;
                }
                if (y->k < (x->c)->k)
                    x->c = y;
                if (x->r == x)
                    min = x;
                A[d]=NULL;
                d++;
            }
            A[d]=x;
            x=x->r;
            if(x==min)
                break;
        }
        min=NULL;
        for(int i=0; i<=size; i++)
        {
            if(A[i]!=NULL)
            {
                A[i]->l=A[i];
                A[i]->r=A[i];
                if(min==NULL)
                {
                    min=A[i];
                }
                else
                {
                    A[i]->r=min->r;
                    A[i]->l=min;
                    min->r=A[i];
                    A[i]->r->l=A[i];
                    if(A[i]->k<min->k)
                        min=A[i];
                }
            }
        }
    }
    void cut(Node<E>* x, Node<E>* y)
    {
        if (x == x->r)
            y->c = NULL;
        (x->l)->r = x->r;
        (x->r)->l = x->l;
        if (x == y->c)
            y->c = x->r;
        y->d = y->d - 1;
        x->r = x;
        x->l = x;
        (min->l)->r = x;
        x->r = min;
        x->l = min->l;
        min->l = x;
        x->p = NULL;
        x->m = false;
    }
    void cascadingCut(Node<E>* y)
    {
        Node<E>* z=y->p;
        if(z!=NULL)
        {
            if(y->m==false)
                y->m=true;
            else
            {
                cut(y,z);
                cascadingCut(z);
            }
        }
    }
public:
    fibHeap()
    {
        min=NULL;
        n=0;
    }
    Node<E>* push(E k, int v)
    {
        Node<E>* newNode=new Node<E>(k,v);
        track.push_back(newNode);
        if(min==NULL)
        {
            min=newNode;
        }
        else
        {
            newNode->r=min->r;
            newNode->l=min;
            min->r=newNode;
            newNode->r->l=newNode;

        }
        if(newNode->k<min->k)
        {
            min=newNode;
        }
        n++;
        return newNode;
    }
    E pop()
    {
        Node<E> *p;
        Node<E> *ptr;
        Node<E> *z = min;
        p = z;
        ptr = z;
        if (z == NULL)
            return 0;

        Node<E> *x;
        Node<E> *np;

        x = NULL;

        if (z->c != NULL)
            x = z->c;

        if (x != NULL)
        {
            ptr = x;
            do
            {
                np = x->r;
                (min->l)->r = x;
                x->r = min;
                x->l = min->l;
                min->l = x;
                if (x->k < min->k)
                    min = x;

                x->p = NULL;
                x = np;
            }
            while (np != ptr);
        }

        (z->l)->r = z->r;
        (z->r)->l = z->l;
        min = z->r;

        if (z == z->r && z->c == NULL)
            min = NULL;

        else
        {
            min = z->r;
            consolidate();
        }
        n = n - 1;
        return p->k;
    }
    void decreaseKey(Node<E>* x,E k)
    {
        if(k>x->k)
        {
            cout<<"New key is greater than current key"<<'\n';
            return;
        }
        x->k=k;
        Node<E>* y=x->p;
        if(y!=NULL && x->k<y->k)
        {
            cut(x,y);
            cascadingCut(y);
        }
        if(x->k<min->k)
            min=x;
    }
    E top()
    {
        return min->v;
    }
    bool isEmpty()
    {
        return min==NULL;
    }
    int display()
    {
        Node<E>* p = min;
        if (p == NULL)
        {
            cout << "Empty Heap" << endl;
            return 0;
        }
        cout << "Root Nodes: " << endl;

        do
        {
            cout << p->k;
            p = p->r;
            if (p != min)
            {
                cout << "-->";
            }
        }
        while (p != min && p->r != NULL);
        cout << endl;
    }
    ~fibHeap()
    {
        for(int i=0; i<n; i++)
        {
            delete track[i];
        }
    }
};
template <typename E>
class minHeap
{
private:
    vector<pair<E,int>> arr;
    int count=0;
    int left(int i)
    {
        return i<<1;
    }
    int right(int i)
    {
        return (i<<1)|1;
    }
    void popHelp(int i)///minHeapify
    {
        int l=left(i);
        int r=right(i);
        int smallest=i;
        if(l<=count && arr[l].first<=arr[i].first)
        {
            smallest=l;
        }
        if(r<=count && arr[r].first<arr[smallest].first)
        {
            smallest=r;
        }
        if(smallest!=i)
        {
            swap(arr[i],arr[smallest]);
            popHelp(smallest);
        }
        else
        {
            return;
        }
    }
    void pushhelp(int count)
    {
        ///track[v]=count;
        if(count>1)
        {
            int p=count>>1;
            if(arr[p].first>arr[count].first)
            {

                swap(arr[p],arr[count]);

                pushhelp(p);
            }
            else
                return;
        }
    }
    int search(int v)
    {
        int idx=-1;
        for(int i=1; i<=count; i++)
        {
            if(arr[i].second==v)
            {
                idx=i;
                break;
            }
        }
        return idx;
    }
public:
    minHeap()
    {
        arr.push_back(make_pair(-1,-1));
    }
    void push(const E k,const int v)
    {

        arr.push_back(make_pair(k,v));///key,vertex
        count++;
        pushhelp(count);
    }
    E top()
    {
        if(count>0)
            return arr[1].second;
        return -1;
    }
    E pop()
    {
        E t;
        if(count==1)
        {
            t=arr[1].first;
            count--;
        }
        ///track[arr[1].second]=-1;
        if(count>1)
        {
            t=arr[1].first;
            arr[1]=arr[count];
            count--;
            popHelp(1);
        }
        return t;
    }
    void decreaseKey(int v,E k)
    {
        int s=search(v);
        if(s==-1)
        {
            cout<<"Node is not present in the heap"<<'\n';
            return;
        }
        if(arr[s].first<k)
        {
            cout<<"New key is greater than the old key"<<'\n';
            return;
        }
        arr[s].first=k;
        pushhelp(s);
    }
    bool isEmpty()
    {
        return count==0;
    }
};
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
        adj[v].push_back(Edge(u,w));
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
        E--;
    }
    pair<int,int> DijkstraFH(int, int);
    pair<int,int> DijkstraMH(int, int);
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
pair<int,int> Graph::DijkstraFH(int s1, int s2)///O((V+E)logV), goal is O(VlogV+E)
{
    fibHeap<int> pq;
    ///initialize single source
    vector<int> d(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<int> best(V,0);
    vector<Node<int>*> track(V,NULL);
    Node<int>* p;
    for(int i=0; i<V; i++)
    {
        if(i!=s1)
        {
            p=pq.push(INT_MAX,i);
        }
        else
        {
            p=pq.push(0,i);
        }
        track[i]=p;
    }
    vector<bool> inSP(V,false);
    d[s1] = 0;
    best[s1]=0;
    double ans=0;
    while (!pq.isEmpty())///O(V)
    {
        int u = pq.top();
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
                best[v]=best[u]+1;
                pq.decreaseKey(track[v],d[u]+weight);///O(logV)
                parent[v] = u;
            }
        }
    }
    return make_pair(best[s2],d[s2]);
}
pair<int,int> Graph::DijkstraMH(int s1, int s2)///O((V+E)logV)
{
    minHeap<int> pq;
    double ans=0;
    vector<int> d(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<int> best(V,0);
    vector<bool> inSP(V,false);
    for(int i=0; i<V; i++)
    {
        if(i!=s1)
        {
            pq.push(INT_MAX,i);
        }
        else
        {
            pq.push(0,i);
        }
    }
    d[s1] = 0;
    best[s1]=0;
    while (!pq.isEmpty())///O(V)
    {
        int u = pq.top();
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
                best[v]=best[u]+1;
                pq.decreaseKey(v,d[u]+weight);///O(logV)
                parent[v] = u;
            }
        }
    }
    return make_pair(best[s2],d[s2]);
}
int main()
{
    int V,E;
    int s1,s2,w;
    ifstream file("input1.txt");
    file>>V>>E;
    Graph g(V);
    while(E--)
    {
        file>>s1>>s2>>w;
        g.addEdge(s1,s2,w);
    }
    file.close();
    ifstream file1("input2.txt");
    ofstream ofile("output.txt",ios::out|ios::trunc);
    file1>>w;
    while(w--)
    {
        file1>>s1>>s2;
        clock_t FibHeapTime = clock();
        pair<int,int> p1=g.DijkstraFH(s1,s2);
        ofile<<p1.first<<' '<<p1.second<<' '<<float(clock() - FibHeapTime) / CLOCKS_PER_SEC<<' ';
        clock_t MinHeapTime = clock();
        g.DijkstraMH(s1,s2);
        ofile<<float(clock() - MinHeapTime) / CLOCKS_PER_SEC<<'\n';
    }
    file1.close();
    ofile.close();

    return 0;
}
