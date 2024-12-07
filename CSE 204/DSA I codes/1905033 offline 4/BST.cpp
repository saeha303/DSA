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
};
template <typename E>
class BSTNode : public BinNode<E>
{
private:
    E it;
    BSTNode* lc;
    BSTNode* rc;
public:
    BSTNode()
    {
        lc = rc = NULL;
    }
    BSTNode(E e, BSTNode* l =NULL, BSTNode* r =NULL)
    {
        it = e;
        lc = l;
        rc = r;
    }
    ~BSTNode() {}
    E& element()
    {
        return it;
    }
    void setElement(const E& e)
    {
        it = e;
    }
    inline BSTNode* left() const//getLeft
    {
        return lc;
    }
    void setLeft(BinNode<E>* b)
    {
        lc = (BSTNode*)b;
    }
    inline BSTNode* right() const//getRight
    {
        return rc;
    }
    void setRight(BinNode<E>* b)
    {
        rc = (BSTNode*)b;
    }
    bool isLeaf()
    {
        return (lc == NULL) && (rc == NULL);
    }
};
template <typename E>
class BSTOperation
{
private:
    void operator =(const BSTOperation&) {}
    BSTOperation(const BSTOperation&) {}
public:
    BSTOperation() {}
    virtual ~BSTOperation() {}
    virtual void Insert(const E& e) = 0;
    virtual E Delete(const E& e) = 0;
    virtual bool Find(const E& e) const = 0;
    virtual void Traverse(string t)=0;
    virtual int count()=0;
};
template <typename E>
class BST : public BSTOperation<E>
{
private:
    BSTNode<E>* root;
    void clearhelp(BSTNode<E>*);//why root as a parameter, can be accessed directly
    BSTNode<E>* inserthelp(BSTNode<E>*, const E&);
    BSTNode<E>* deletemin(BSTNode<E>*);
    BSTNode<E>* getmin(BSTNode<E>*);
    BSTNode<E>* deletehelp(BSTNode<E>*, const E&);
    bool findhelp(BSTNode<E>*, const E&) const;
    void printhelp(BSTNode<E>*) const;
    void traversehelpin(BSTNode<E>*);
    void traversehelppre(BSTNode<E>*);
    void traversehelppost(BSTNode<E>*);
    int counthelp(BSTNode<E>*);
public:
    BST()
    {
        root = NULL;
    }
    ~BST()
    {
        clearhelp(root);
    }
    void Insert(const E& e)
    {
        root = inserthelp(root,e);
        printhelp(root);
        cout<<'\n';
    }
    E Delete(const E& e)
    {
        E temp = findhelp(root, e);
        if (temp != NULL)
        {
            root = deletehelp(root, e);
            printhelp(root);//count--;
            cout<<'\n';
        }
        else
        {
            cout<<"Invalid Operation"<<'\n';
        }
        return temp;
    }
    bool Find(const E& e) const
    {
        return findhelp(root, e);
    }
    void Traverse(string t)
    {
        if(t=="In")
        {
            traversehelpin(root);
            cout<<'\n';
        }
        else if(t=="Pre")
        {
            traversehelppre(root);
            cout<<'\n';
        }
        else if(t=="Post")
        {
            traversehelppost(root);
            cout<<'\n';
        }
    }
    int count()
    {
        return counthelp(root);
    }
};
template <typename E>
void BST<E>::clearhelp(BSTNode<E>* root)
{
    if (root == NULL)
        return;
    clearhelp(root->left());
    clearhelp(root->right());
    delete root;
}
template <typename E>
BSTNode<E>* BST<E>::inserthelp(BSTNode<E>* root, const E& it)
{
    if (root == NULL)
        return new BSTNode<E>(it, NULL, NULL);
    if (it < root->element())
        root->setLeft(inserthelp(root->left(),it));
    else
        root->setRight(inserthelp(root->right(),it));
    return root;
}
template <typename E>
BSTNode<E>* BST<E>::deletemin(BSTNode<E>* rt)
{
    if (rt->left() == NULL)
        return rt->right();
    else
    {
        rt->setLeft(deletemin(rt->left()));
        return rt;
    }
}
template <typename E>
bool BST<E>::findhelp(BSTNode<E>* root,
                      const E& e) const
{
    if (root == NULL)
        return NULL;
    if (e < root->element())
        return findhelp(root->left(), e);
    else if (e > root->element())
        return findhelp(root->right(), e);
    else
        return true;
}
template <typename E>
BSTNode<E>* BST<E>::deletehelp(BSTNode<E>* rt, const E& e)
{
    if (rt == NULL)
        return NULL;
    else if (e < rt->element())
        rt->setLeft(deletehelp(rt->left(), e));
    else if (e > rt->element())
        rt->setRight(deletehelp(rt->right(), e));
    else
    {
        BSTNode<E>* temp = rt;
        if (rt->left() == NULL)
        {
            rt = rt->right();
            delete temp;
        }
        else if (rt->right() == NULL)
        {
            rt = rt->left();
            delete temp;
        }
        else
        {
            temp = getmin(rt->right());//t
            rt->setElement(temp->element());
            rt->setRight(deletemin(rt->right()));
            delete temp;//t
        }
    }
    return rt;
}

template <typename E>
void BST<E>::printhelp(BSTNode<E>* root) const
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
template <typename E>
BSTNode<E>* BST<E>::getmin(BSTNode<E>* rt)
{
    if (rt->left() == NULL)
        return rt;
    else
        return getmin(rt->left());
}
template <typename E>
void BST<E>::traversehelpin(BSTNode<E>* root)
{
    if (root == NULL)
    {
        return;
    }
    traversehelpin(root->left());
    cout<<root->element()<<" ";
    traversehelpin(root->right());

}
template <typename E>
void BST<E>::traversehelppre(BSTNode<E>* root)
{
    if (root == NULL)
    {
        return;
    }
    cout<<root->element()<<" ";
    traversehelppre(root->left());
    traversehelppre(root->right());

}
template <typename E>
void BST<E>::traversehelppost(BSTNode<E>* root)
{
    if (root == NULL)
    {
        return;
    }
    traversehelppost(root->left());
    traversehelppost(root->right());
    cout<<root->element()<<" ";
}
template <typename E>
int BST<E>::counthelp(BSTNode<E>* root)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->left()==NULL && root->right()==NULL)
    {
        return 1;
    }
    return counthelp(root->left())+counthelp(root->right());
}
int main()
{
    BST<int> tree;
    ifstream file("input.txt");
    char c;
    string s;
    int i;
    while(!file.eof())
    {
        file>>c>>s;
        if(c=='F')
        {
            i=stoi(s);
            cout<<(tree.Find(i)?"TRUE":"FALSE")<<'\n';
        }
        else if(c=='I')
        {
            i=stoi(s);
            tree.Insert(i);
        }
        else if(c=='D')
        {
            i=stoi(s);
            tree.Delete(i);
        }
        else if(c=='T')
        {
            tree.Traverse(s);
        }
        else if(c=='C')
        {
            cout<<tree.count()<<'\n';
        }
    }
    file.close();
}
