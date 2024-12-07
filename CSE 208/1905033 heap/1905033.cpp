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
        (z->d)++;
    }
    void consolidate()
    {
//        int size=(int)(log2(n)/log2(1.618));
        float f = (log(n)) / (log(2));
        int size = f;
        cout<<"size:"<<size<<'\n';
        vector<Node<E>*> A(size+1,NULL);
        Node<E>* x=min;
        Node<E>* p;
        do
        {
            int d=x->d;
            cout<<"huh"<<'\n';
            while(A[d]!=NULL)
            {
                cout<<"hi "<<d<<'\n';

                Node<E>* y=A[d];
                ///big key is pointed by y
                if((x->k)>(y->k))
                {

                    p=x;
                    x=y;
                    y=p;
                }
//                cout<<"hi2"<<'\n';
                if(y==min)
                {
                    min=x;
                }
//                cout<<"hi3"<<'\n';

                (y->l)->r=y->r;
                (y->r)->l=y->l;
                y->p=x;
                y->l=y;
                y->r=y;
                x->d=(x->d)+1;
                y->m=false;
//                cout<<"hi4"<<'\n';
                ///making y the child of x
                if(x->c==NULL)
                {
                    x->c=y;
                }
                else
                {
                    y->r=x->c->r;
                    y->l=x->c;
                    (y->r)->l=y;
                    (x->c)->r=y;
                }
//                if (y->k < (x->c)->k)
//                    x->c = y;
                if (x->r == x)
                {
                    min = x;
//                    cout<<"min=x"<<'\n';
                }

                A[d]=NULL;
                d++;

//                cout<<"hi5"<<'\n';
            }
//            cout<<"hi6"<<'\n';
            A[d]=x;
//            cout<<"hi7"<<'\n';
            x=x->r;
//            cout<<"inside consolidate while loop"<<'\n';
        }
        while(x!=min);
//        p=min;
//        do
//        {
//            cout<<p->d<<' '<<p->k<<' ';
//            p=p->r;
//        }while(p!=min);
//        cout<<'\n';
//        cout<<"outside consolidate while loop"<<'\n';
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
                    (A[i]->r)->l=A[i];
                    if(A[i]->k<min->k)
                        min=A[i];
                }
                if (min == NULL)
                min = A[i];
            else if (A[i]->k < min->k)
                min = A[i];
            }
        }
//        p=min;
//        do
//        {
//            cout<<p->d<<' '<<p->k<<' ';
//            p=p->r;
//        }while(p!=min);
//        cout<<"consolidate"<<'\n';

//int d, i;
//    float f = (log(n)) / (log(2));
//    int D = f;
//    Node<E> *A[D+1];
//
//    for (i = 0; i <= D; i++)
//        A[i] = NULL;
//
//    Node<E> *x = min;
//    Node<E> *y;
//    Node<E> *np;
//    Node<E> *pt = x;
//
//    do
//    {
//        pt = pt->r;
//
//        d = x->d;
//
//        while (A[d] != NULL)
//
//        {
//            y = A[d];
//
//            if (x->k > y->k)
//
//            {
//                np = x;
//
//                x = y;
//
//                y = np;
//            }
//
//            if (y == min)
//                min = x;
//            Fibonnaci_link(y, x);
//            if (x->r == x)
//                min = x;
//            A[d] = NULL;
//            d = d + 1;
//        }
//
//        A[d] = x;
//        x = x->r;
////        display();
//    }
//
//    while (x != min);
//    min = NULL;
//    cout<<"inside consolidate before loop"<<'\n';
//    for (int j = 0; j <= D; j++)
//    {
//        if (A[j] != NULL)
//        {
//            A[j]->l = A[j];
//            A[j]->r = A[j];
//            if (min != NULL)
//            {
//                (min->l)->r = A[j];
//                A[j]->r = min;
//                A[j]->l = min->l;
//                min->l = A[j];
//                if (A[j]->k < min->k)
//                    min = A[j];
//            }
//            else
//            {
//                min = A[j];
//            }
//            if (min == NULL)
//                min = A[j];
//            else if (A[j]->k < min->k)
//                min = A[j];
//        }
//    }
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
    Node<E>* push(E k, int v)///OK
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
        Node<E> *z = min;
        if (z == NULL)
            return 0;
        Node<E> *x=NULL;
        if (z->c != NULL)
        {
            x = z->c;
            Node<E> *np;
            while(true)
            {
                np = x->r;
                min->c=np;
                x->l->r=x->r;
                x->r->l=x->l;
                x->r=min->r;
                x->l=min;
                x->p = NULL;
                min->r=x;
                x->r->l=x;

                if(x->k<min->k)
                    min=x;
                if(min->c==np&&np==x){
                    min->c=NULL;
                    break;
                }
                x = np;
//                cout<<"inside loop"<<'\n';
            }
//            cout<<"outside loop"<<'\n';
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
//        cout<<"pop"<<'\n';
        return z->k;

//        Node<E>* z=min;
//        if (z == NULL)
//            return 0;
//        Node<E> *x=NULL;
//        if(z->c!=NULL)
//        {
//            x = z->c;
//            Node<E> *np;
//            Node<E> *ptr = x;
//            do
//            {
//                np = x->r;
//                ///making the right one current child of z
//
//                z->c=t->r;
//
//                ///changing the child list, removing t from child list
//                t->l->r=t->r;
//                t->r->l=t->l;
//                ///changing t,the child,taking it to root list, on the right side of min
//                t->r=min->r;
//                t->l=min;
//                t->p=NULL;
//                ///changing the 2 nodes min and min->right to place t
//                min->r=t;
//                t->r->l=t;
//                ///
//                if(t->k<min->k)
//                    min=t;
//            }while (np != ptr);
//        }
//        z->r->l=z->l;
//        z->l->r=z->r;
//        z->c=NULL;
//
//        if(z==z->r && z->c==NULL)
//        {
//            min=NULL;
//        }
//        else
//        {
//            min=z->r;
//            cout<<"consolidate"<<'\n';
//            consolidate();
//        }
//        n--;
//        return k;
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
//        cout<<"decrease key"<<'\n';
//        Node<E> *p=min;
//        do
//        {
//            cout<<p->d<<' '<<p->k<<' ';
//            p=p->r;
//        }while(p!=min);
//        cout<<'\n';
    }
    E top()
    {
        return min->v;
    }
    bool isEmpty()
    {
        return min==NULL;
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
    void popHelp(int i,vector<int>& track)
    {
        track[arr[i].second]=i;
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
            track[arr[i].second]=i;
            popHelp(smallest,track);
        }
        else
        {
            return;
        }
    }
    void pushhelp(int count,vector<int>& track)
    {
        track[arr[count].second]=count;
        if(count>1)
        {
            int p=count>>1;
            if(arr[p].first>arr[count].first)
            {

                swap(arr[p],arr[count]);
                track[arr[count].second]=count;
                pushhelp(p,track);
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
    void push(const E k,const int v,vector<int>& track)
    {

        arr.push_back(make_pair(k,v));///key,vertex
        count++;
        pushhelp(count,track);
    }
    E top()
    {
        if(count>0)
            return arr[1].second;
        return -1;
    }
    E pop(vector<int>& track)
    {
        E t;
        if(count==1)
        {
            t=arr[1].first;
            count--;
        }
        if(count>1)
        {
            t=arr[1].first;
            arr[1]=arr[count];
            count--;
            popHelp(1,track);
        }
        return t;
    }
    void decreaseKey(int v,E k,vector<int>& track)
    {

        if(track[v]==-1)
        {
            cout<<"Node is not present in the heap"<<'\n';
            return;
        }
        if(arr[track[v]].first<k)
        {
            cout<<"New key is greater than the old key"<<'\n';
            return;
        }
        arr[track[v]].first=k;
        pushhelp(track[v],track);
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
    fibHeap<long> pq;
    ///initialize single source
    vector<long> d(V, INT_MAX);
    vector<long> best(V,0);
    vector<Node<long>*> track(V,NULL);
    Node<long>* p;
    for(int i=0; i<V; i++)
    {
        if(i!=s1)
        {
            p=pq.push(LONG_MAX,i);
        }
        else
        {
            p=pq.push(0,i);
        }
        track[i]=p;
    }
    d[s1] = 0;
    best[s1]=0;
    while (!pq.isEmpty())///O(V)
    {
        int u = pq.top();
//        cout<<"u"<<'\n';
        pq.pop();///O(logV)
        vector< Edge >::iterator i;
        int v;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)///O(E)
        {

            v = (*i).getDest();
            double weight = (*i).getWeight();
            if (d[v] >d[u]+ weight)
            {
                d[v] = d[u]+weight;
                best[v]=best[u]+1;
                pq.decreaseKey(track[v],d[u]+weight);///O(logV)
            }
        }
    }
    return make_pair(best[s2],d[s2]);
}
pair<int,int> Graph::DijkstraMH(int s1, int s2)///O((V+E)logV)
{
    minHeap<int> pq;
    vector<int> d(V, INT_MAX);
    vector<int> best(V,0);
    vector<int> track(V,-1);
    for(int i=0; i<V; i++)
    {
        if(i!=s1)
        {
            pq.push(INT_MAX,i,track);
        }
        else
        {
            pq.push(0,i,track);
        }
    }
    d[s1] = 0;
    best[s1]=0;
    while (!pq.isEmpty())///O(V)
    {
        int u = pq.top();
        pq.pop(track);///O(logV)
        vector< Edge >::iterator i;
        int v;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)///O(E)
        {

            v = (*i).getDest();
            double weight = (*i).getWeight();
            if (d[v] >d[u]+ weight)
            {
                d[v] = d[u]+weight;
                best[v]=best[u]+1;
                pq.decreaseKey(v,d[u]+weight,track);///O(logV)
            }
        }
    }
    return make_pair(best[s2],d[s2]);
}
int main()
{
    int V,E;
    int s1,s2,w;
    ifstream file("heap1.txt");
    file>>V>>E;
    Graph g(V);
    while(E--)
    {
        file>>s1>>s2>>w;
        g.addEdge(s1,s2,w);
    }
    file.close();
    ifstream file1("heap2.txt");
    ofstream ofile("out.txt",ios::out|ios::trunc);
    file1>>w;
    while(w--)
    {
        file1>>s1>>s2;
        clock_t FibHeapTime = clock();
        pair<int,int> p1=g.DijkstraMH(s1,s2);
        cout<<p1.first<<' '<<p1.second<<'\n';
        ofile<<p1.first<<' '<<p1.second<<' '<<float(clock() - FibHeapTime) / CLOCKS_PER_SEC<<' ';
        clock_t MinHeapTime = clock();
        p1=g.DijkstraFH(s1,s2);
        cout<<p1.first<<' '<<p1.second<<'\n';
        ofile<<float(clock() - MinHeapTime) / CLOCKS_PER_SEC<<'\n';
    }
    file1.close();
    ofile.close();

    return 0;
}
