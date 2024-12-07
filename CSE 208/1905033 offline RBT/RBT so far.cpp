#include<iostream>
#include<fstream>
using namespace std;
template <typename E> class BinNode
{
public:
    virtual ~BinNode() {}
    virtual E& element() = 0;//getElement
    virtual void setElement(const E&) = 0;
    virtual BinNode* left() const = 0;
    virtual void setLeft(BinNode*) = 0;
    virtual BinNode* right() const = 0;
    virtual void setRight(BinNode*) = 0;
    virtual bool isLeaf() = 0;
    virtual BinNode* parent() const=0;
    virtual void setParent(BinNode*) = 0;
    virtual char color() const=0;
    virtual void setColor(char) = 0;
    virtual int countSmaller() const=0;
    virtual void setCountSmaller(const int &) = 0;
};
template <typename E>
class RBTNode : public BinNode<E>
{
private:
    E k;
    RBTNode<E>* lc;
    RBTNode<E>* rc;
    RBTNode<E>* p;
    char c;
    int smallerCount;
public:
    RBTNode()
    {
        lc =NULL;
        rc = NULL;
        p=NULL;
        smallerCount=0;
    }
    RBTNode(E e, RBTNode<E>* l =NULL, RBTNode<E>* r =NULL)
    {
        k = e;
        lc = l;
        rc = r;
        p=NULL;
        c='R';
        smallerCount=0;
    }
    ~RBTNode() {}
    E& element()
    {
        return k;
    }
    void setElement(const E& e)
    {
        k = e;
    }
    inline RBTNode<E>* left() const//getLeft
    {
        return lc;
    }
    void setLeft(BinNode<E>* b)
    {
        lc = (RBTNode*)b;
    }
    inline RBTNode<E>* right() const//getRight
    {
        return rc;
    }
    void setRight(BinNode<E>* b)
    {
        rc = (RBTNode*)b;
    }
    bool isLeaf()
    {
        return (lc == NULL) && (rc == NULL);
    }
    BinNode<E>* parent() const
    {
        return p;
    }
    void setParent(BinNode<E>* b)
    {
        p=(RBTNode*)b;
    }
    char color() const
    {
        return c;
    }
    void setColor(char c)
    {
        this->c=c;
    }
    int countSmaller() const
    {
        return smallerCount;
    }
    void setCountSmaller(const int &c)
    {
        this->smallerCount=c;
    }
};
template <typename E>
class RBTOperation
{
private:
    void operator =(const RBTOperation&) {}
    RBTOperation(const RBTOperation&) {}
public:
    RBTOperation() {}
    virtual ~RBTOperation() {}
    virtual RBTNode<E>* Insert(const E& e) = 0;
    virtual RBTNode<E>* Delete(const E& e) = 0;
    virtual bool Find(const E& e) const = 0;
    virtual int count(const E& e)=0;
};
template <typename E>
class RBT : public RBTOperation<E>
{
private:
    RBTNode<E>* root;
    void clearhelp(RBTNode<E>*);
    RBTNode<E>* inserthelp(RBTNode<E>*);
    RBTNode<E>* getmin(RBTNode<E>*);
    RBTNode<E>* deletehelp(RBTNode<E>*);
    RBTNode<E>* findhelp(RBTNode<E>*, const E&) const;
    int counthelp(RBTNode<E>*,const E&);
    void Left_rotate(RBTNode<E>*);
    void Right_rotate(RBTNode<E>*);
    void printhelp(RBTNode<E>*) const;
public:
    RBT()
    {
        root = NULL;
    }
    ~RBT()
    {
        clearhelp(root);
    }
    RBTNode<E>* Insert(const E& e)
    {
        RBTNode<E>* temp = findhelp(this->root, e);
        if(temp==NULL)
        {
            RBTNode<E>* z=new RBTNode<E>(e, NULL, NULL);
            RBTNode<E>* y=NULL;
            RBTNode<E>* x=root;
            while(x!=NULL)
            {
                y=x;
                if(z->element()<x->element())
                    x->setCountSmaller(x->countSmaller()+1),x=x->left();
                else
                    x=x->right();
            }
            z->setParent(y);
            if(y==NULL)
            {
                root=z;
            }
            else if(z->element()<y->element())
                y->setLeft(z);
            else
                y->setRight(z);
            inserthelp(z);
        }
        printhelp(root);
        cout<<'\n';
        cout<<root->countSmaller()<<'\n';
        return temp;
    }
    RBTNode<E>* Delete(const E& e)
    {
        RBTNode<E>* t=root;
        RBTNode<E> *x,*y;
        RBTNode<E>* z = findhelp(t, e);
        cout<<"hi 1"<<'\n';
        if(z==NULL)
        {
            return z;
        }
        if((z->left())==NULL || (z->right())==NULL)
        {
            cout<<"hi 4"<<'\n';
            y=z;
        }

        else{
            y=getmin(z->right());
            cout<<"smaller: "<<z->countSmaller()<<'\n';
            y->setCountSmaller(z->countSmaller());
            cout<<"hi 3"<<'\n';

        }

        cout<<"hi 2"<<'\n';
        if(y->left()!=NULL)
            x=y->left();
        else
            x=y->right();///z->right() in slide
        if(x!=NULL)
            x->setParent(y->parent());

        if(y->parent()==NULL)
            cout<<"hi 5"<<'\n',root=x;
        else if(y==y->parent()->left())
            y->parent()->setLeft(x);
        else
            y->parent()->setRight(x);

        if(y!=z)
        {
            z->setColor(y->color());
            z->setElement(y->element());
        }

        if(y->color()=='B')
        {
            cout<<"hi 7"<<'\n';
            deletehelp(x);
        }

        cout<<"hi 6"<<'\n';
        return y;
    }
    bool Find(const E& e) const
    {
        return findhelp(root, e);
    }
    int count(const E& e)
    {
        counthelp(root,e);
    }
};
template <typename E>
void RBT<E>::Left_rotate(RBTNode<E>* x)
{
    if(x->right()==NULL)
        return;
    RBTNode<E>* y=x->right();

    x->setRight(y->left());
    if(y->left()!=NULL)
        y->left()->setParent(x);
    if(x->parent()!=NULL)
        y->setParent(x->parent());
    if(x->parent()==NULL)
        root=y;
    else if(x==x->parent()->left())
        x->parent()->setLeft(y);
    else
        x->parent()->setRight(y);
    y->setLeft(x);
    x->setParent(y);
}
template <typename E>
void RBT<E>::Right_rotate(RBTNode<E>* x)
{
    if(x->left()==NULL)
        return;
    RBTNode<E>* y=x->left();
    x->setLeft(y->right());
    if(y->right()!=NULL)
        y->right()->setParent(x);
    if(x->parent()!=NULL)
        y->setParent(x->parent());
    if(x->parent()==NULL)
        root=y;
    else if(x==x->parent()->left())
        x->parent()->setLeft(y);
    else
        x->parent()->setRight(y);
    y->setRight(x);
    x->setParent(y);
}
template <typename E>
void RBT<E>::clearhelp(RBTNode<E>* root)
{
    if (root == NULL)
        return;
    clearhelp(root->left());
    clearhelp(root->right());
    delete root;
}
template <typename E>
RBTNode<E>* RBT<E>::inserthelp(RBTNode<E>* z)
{
    if(z!=root)
    {
        if(z->parent()==NULL)
        while(z->parent()!=NULL && ((z->parent())->color())=='R')
        {
            if(z->parent()==z->parent()->parent()->left())
            {
                if(z->parent()->parent()->right()!=NULL)
                {
                    RBTNode<E>* y=(RBTNode<E>*)z->parent()->parent()->right();///uncle
                    if(y->color()=='R')
                    {
                        z->parent()->setColor('B');
                        y->setColor('B');
                        z->parent()->parent()->setColor('R');
                        z=(RBTNode<E>*)z->parent()->parent();
                    }
                }

                else
                {
                    if(z==z->parent()->right())
                    {
                        z=(RBTNode<E>*)z->parent();
                        Left_rotate(z);
                    }
                    z->parent()->setColor('B');
                    z->parent()->parent()->setColor('R');
                    Right_rotate((RBTNode<E>*)z->parent()->parent());
                }
            }
            else
            {
                if(z->parent()->parent()->left()!=NULL)
                {
                    RBTNode<E>* y=(RBTNode<E>*)z->parent()->parent()->left();///uncle
                    if(y->color()=='R')
                    {
                        z->parent()->setColor('B');
                        y->setColor('B');
                        z->parent()->parent()->setColor('R');
                        z=(RBTNode<E>*)z->parent()->parent();
                    }
                }
                else
                {
                    if(z==z->parent()->left())
                    {
                        z=(RBTNode<E>*)z->parent();
                        Right_rotate(z);
                    }
                    z->parent()->setColor('B');
                    z->parent()->parent()->setColor('R');
                    Left_rotate((RBTNode<E>*)z->parent()->parent());
                }
            }
            this->root->setColor('B');
        }
    }
    (this->root)->setColor('B');
}
template <typename E>
RBTNode<E>* RBT<E>::findhelp(RBTNode<E>* root,
                             const E& e) const
{
    if (root == NULL)
        return NULL;
    if (e < root->element())
        return findhelp(root->left(), e);
    else if (e > root->element())
        return findhelp(root->right(), e);
    else
        return root;
}
template <typename E>
RBTNode<E>* RBT<E>::deletehelp(RBTNode<E>* x)
{
    cout<<"enter"<<'\n';
    while(x!=root && x->color()=='B')
    {
        cout<<x->color()<<'\n';
        if(x==x->parent()->left())
        {
            RBTNode<E>* w=(RBTNode<E>*)x->parent()->right();
            if(w->color()=='R')
            {
                w->setColor('B');
                x->parent()->setColor('R');
                Left_rotate((RBTNode<E>*)x->parent());
                w=(RBTNode<E>*)x->parent()->right();
            }
            if(w->left()->color()=='B' && w->right()->color()=='B')
            {
                w->setColor('R');
                x=(RBTNode<E>*)x->parent();
            }
            else
            {
                if(w->right()->color()=='B')
                {
                    w->left()->setColor('B');
                    w->setColor('R');
                    Right_rotate(w);
                    w=(RBTNode<E>*)x->parent()->right();
                }
                w->setColor(x->parent()->color());
                x->parent()->setColor('B');
                w->right()->setColor('B');
                Left_rotate((RBTNode<E>*)x->parent());
                x=root;
            }
        }
        else
        {
            RBTNode<E>* w=(RBTNode<E>*)x->parent()->left();
            if(w->color()=='R')
            {
                w->setColor('B');
                x->parent()->setColor('R');
                Right_rotate((RBTNode<E>*)x->parent());
                w=(RBTNode<E>*)x->parent()->left();
            }
            if(w->right()->color()=='B' && w->left()->color()=='B')
            {
                w->setColor('R');
                x=(RBTNode<E>*)x->parent();
            }
            else
            {
                if(w->left()->color()=='B')
                {
                    w->right()->setColor('B');
                    w->setColor('R');
                    Left_rotate(w);
                    w=(RBTNode<E>*)x->parent()->left();
                }
                w->setColor(x->parent()->color());
                x->parent()->setColor('B');
                w->left()->setColor('B');
                Right_rotate((RBTNode<E>*)x->parent());
                x=root;
            }
        }
    }
    cout<<"print"<<'\n';
//    cout<<x->color()<<'\n';
    if(x!=NULL){
        x->setColor('B');
        root->setColor('B');///
    }

}
template <typename E>
RBTNode<E>* RBT<E>::getmin(RBTNode<E>* rt)
{
    if (rt->left() == NULL)
        return rt;
    else
        return getmin(rt->left());
}
template <typename E>
int RBT<E>::counthelp(RBTNode<E>* root,const E& t)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->element()>=t)
    {
        return counthelp(root->left(),t);
    }
    if(root->element()<t)
        return 1+root->countSmaller()+counthelp(root->right(),t);
}
template <typename E>
void RBT<E>::printhelp(RBTNode<E>* root) const
{
    if (root == NULL)
        return;
    cout<<root->element()<<" ";
    if(!root->isLeaf())
    {
        cout<<"(";
        printhelp(root->left());
        cout<<")";
        cout<<"(";
        printhelp(root->right());
        cout<<")";

    }
}
int main()
{
    RBT<int> tree;
    ifstream file("in.txt");
    ofstream ofile("out.txt");
    int t,c,s;
    file>>t;
    ofile<<t<<'\n';
    while(t--)
    {
        file>>c>>s;
        if(c==0)
        {
            RBTNode<int>* i=tree.Delete(s);
            ofile<<c<<' '<<s<<' '<<(i==NULL?0:1)<<'\n';
        }
        else if(c==1)
        {
            RBTNode<int>* i=tree.Insert(s);
            ofile<<c<<' '<<s<<' '<<(i==NULL?1:0)<<'\n';
        }
        else if(c==2)
        {
            bool i=tree.Find(s);
            ofile<<c<<' '<<s<<' '<<(i?1:0)<<'\n';
        }
        else if(c==3)
        {
            int i=tree.count(s);
            ofile<<c<<' '<<s<<' '<<i<<'\n';
        }
    }
    file.close();
    ofile.close();
}
