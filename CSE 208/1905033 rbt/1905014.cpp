#include<bits/stdc++.h>
using namespace std;

class node{
public:
    int priority;
    node *parent;
    node *left;
    node *right;
    int color;
    int subtreeSize;
    node()
    {
        this->parent=NULL;
        this->color=2;
        this->subtreeSize=1;
    }
    node(int x)
    {
        this->priority=x;
        this->parent=NULL;
        this->color=2;
        this->subtreeSize=1;
    }
};

class redblackTree
{
    node* root;
    node* TNIL;
    void leftRotate(node* x);
    void rightRotate(node* x);
    void insertFix(node* x);
    node* searchNodeHelp(node* x,int y);
    node* successor(node* x);
    void deletionFix(node* x);
    int countNodes(node* x, int priority);
    void printHelper(node* root, string indent, bool last);
    void rbTransplant(node* x, node* y);
public:
    redblackTree()
    {
        TNIL=new node();
        TNIL->color=0;
        TNIL->left=NULL;
        TNIL->right=NULL;
        TNIL->subtreeSize=0;
        root=TNIL;
    }
    int insert(int priority);
    int searchNode(int priority);
    int deletion(int priority);
    int lesser(int priority);
    void prettyPrint();
};

void redblackTree::leftRotate(node* x)
{
    node* y=x->right;
    x->right=y->left;

    if(y->left!=TNIL)
        y->left->parent=x;
    y->parent=x->parent;

    if(x->parent==NULL)
        root=y;
    else if(x==x->parent->left)
        x->parent->left=y;
    else
        x->parent->right=y;

    y->left=x;
    x->parent=y;

    x->subtreeSize=1+x->left->subtreeSize+x->right->subtreeSize;
    y->subtreeSize=1+y->left->subtreeSize+y->right->subtreeSize;
}

void redblackTree::rightRotate(node* x)
{
    node* y=x->left;
    x->left=y->right;

    if(y->right!=TNIL)
        y->right->parent=x;
    y->parent=x->parent;
    if(x->parent==NULL)
        root=y;
    else if(x==x->parent->right)
        x->parent->right=y;
    else
        x->parent->left=y;
    y->right=x;
    x->parent=y;

    x->subtreeSize=1+x->left->subtreeSize+x->right->subtreeSize;
    y->subtreeSize=1+y->left->subtreeSize+y->right->subtreeSize;
}

void redblackTree::insertFix(node* x)
{
    node* y;//uncle node
    while(x->parent->color==2)
    {
        if(x->parent == x->parent->parent->right)//parent of x is a right child
        {
            y=x->parent->parent->left;//find uncle
            if(y->color==2)
            {
                y->color=1;
                x->parent->color=1;
                x->parent->parent->color=2;
                x=x->parent->parent;
            }
            else
            {
                if(x==x->parent->left)
                {
                    x=x->parent;
                    rightRotate(x);
                }
                x->parent->color=1;
                x->parent->parent->color=2;
                leftRotate(x->parent->parent);
            }
        }
        else
        {
            y=x->parent->parent->right;
            if(y->color==2)
            {
                y->color=1;
                x->parent->color=1;
                x->parent->parent->color=2;
                x=x->parent->parent;
            }
            else
            {
                if(x==x->parent->right)
                {
                    x=x->parent;
                    leftRotate(x);
                }
                x->parent->color=1;
                x->parent->parent->color=2;
                rightRotate(x->parent->parent);
            }
        }
        if(x==root)
            break;
    }
    root->color=1;
}

node* redblackTree::searchNodeHelp(node* x,int y)
{
    while(x!=TNIL)
    {
        if(x->priority==y)
            return x;
        else if(x->priority<y)
            x=x->right;
        else
            x=x->left;
    }
    return x;

}

int redblackTree::insert(int priority)
{
    node* findN=searchNodeHelp(root, priority);
    if(findN!=TNIL)
        return 0;

    node* newNode=new node(priority);
    newNode->left=TNIL;
    newNode->right=TNIL;
    node* x=root;
    node* y=NULL;

    while(x!=TNIL)
    {
        y=x;
        if(newNode->priority<x->priority)
            x=x->left;
        else
            x=x->right;
    }

    newNode->parent=y;
    if(y==NULL){
        newNode->color=1;
        root=newNode;
    }

    else if(newNode->priority<y->priority)
        y->left=newNode;
    else
        y->right=newNode;

    node* fix=newNode->parent;
    while(fix!=NULL)
    {
        fix->subtreeSize++;
        fix=fix->parent;
    }

    if(newNode->parent==NULL)
    {
        newNode->color=1;
        return 1;
    }
    if(newNode->parent->parent==NULL)
        return 1;

    insertFix(newNode);
    return 1;
}

node* redblackTree::successor(node* x)
{
    x=x->right;
    while(x->left!=TNIL)
        x=x->left;

    return x;
}

void redblackTree::rbTransplant(node* x, node* y){
		if (x->parent==NULL) {
			root=y;
		} else if (x==x->parent->left){
			x->parent->left=y;
		} else {
			x->parent->right=y;
		}
		y->parent=x->parent;
	}

void redblackTree::deletionFix(node* x)
{
    node* y;
    while(x!=root && x->color==1)
    {
        if(x==x->parent->left)
        {
            y=x->parent->right;
            if(y->color==2)//case 1
            {
                y->color=1;
                x->parent->color=2;
                leftRotate(x->parent);
                y=x->parent->right;
            }

            if(y->left->color==1 && y->right->color==1)//case 2
            {
                y->color=2;
                x=x->parent;
            }
            else
            {
                if(y->right->color==1)//case 3
                {
                    y->left->color=1;
                    y->color=2;
                    rightRotate(y);
                    y=x->parent->right;
                }
                y->color=x->parent->color;//case 4
                x->parent->color=1;
                y->right->color=1;
                leftRotate(x->parent);
                x=root;
            }
        }
        else
        {
            y=x->parent->left;
            if(y->color==2)
            {
                y->color=1;
                x->parent->color=2;
                rightRotate(x->parent);
                y=x->parent->left;
            }

            if(y->right->color==1 && y->left->color==1)
            {
                y->color=2;
                x=x->parent;
            }
            else
            {
                if(y->left->color==1)
                {
                    y->right->color=1;
                    y->color=2;
                    leftRotate(y);
                    y=x->parent->left;
                }
                y->color=x->parent->color;
                x->parent->color=1;
                y->left->color=1;
                rightRotate(x->parent);
                x=root;
            }
        }
    }
    if(x!=NULL){
        x->color=1;root->color=1;
    }

}

void redblackTree::printHelper(node* root, string indent, bool last) {
		// print the tree structure on the screen
	   	if (root != TNIL) {
		   cout<<indent;
		   if (last) {
		      cout<<"R----";
		      indent += "     ";
		   } else {
		      cout<<"L----";
		      indent += "|    ";
		   }

           string sColor = (root->color==2)?"RED":"BLACK";
		   cout<<root->priority<<"("<<sColor<<")"<<endl;
		   printHelper(root->left, indent, false);
		   printHelper(root->right, indent, true);
		}
		// cout<<root->left->data<<endl;
	}
void redblackTree::prettyPrint() {
    if (root) {
        printHelper(this->root, "", true);
    }
}

int redblackTree::deletion(int priority)
{
    node* findN=searchNodeHelp(root, priority);
    if(findN==TNIL)
        return 0;

    node *x, *y;
    y = findN;
		int y_original_color = y->color;
		if (findN->left == TNIL)
        {
			x = findN->right;
			rbTransplant(findN, findN->right);
		}
		else if (findN->right == TNIL)
		{
			x = findN->left;
			rbTransplant(findN, findN->left);
		}
		else
		{
			y = successor(findN);
			y_original_color = y->color;
			if(y->left!=NULL)
            x=y->left;
        else
			x = y->right;
			if (y->parent == findN)
				x->parent = y;
			else
			{
				rbTransplant(y, y->right);
				y->right = findN->right;
				y->right->parent = y;
			}

			rbTransplant(findN, y);
			y->left = findN->left;
			y->left->parent = y;
			y->color = findN->color;
		}
		 node* fix=y->parent;
    while(fix!=NULL)
    {
        fix->subtreeSize--;
        fix=fix->parent;
    }
		if (y_original_color==1){
            cout<<"HI 1"<<'\n';
			deletionFix(x);
		}
    cout<<"HI 2"<<'\n';
    return 1;
}

int redblackTree::countNodes(node* x, int priority)
{
    if(x==NULL)
        return 0;
    if(x->priority < priority){
        if(x->left!=NULL)
            return (1 + x->left->subtreeSize + countNodes(x->right, priority));
        else
            return (1+countNodes(x->right, priority));
    }
    else if(x->priority==priority){
        if(x->left!=NULL)
            return x->left->subtreeSize;
        else
            return 0;
    }
    else
        return countNodes(x->left, priority);
}

int redblackTree::searchNode(int priority)
{
    node* x;
    x=searchNodeHelp(root, priority);
    if(x==TNIL)
        return 0;
    return 1;
}

int redblackTree::lesser(int priority)
{
    int total=0;
    total=countNodes(root, priority);
    return total;
}

int main()
{
    int t, op, val;
    redblackTree rbt;
    cin>>t;
    for(int i=0; i<t; i++)
    {
        cin>>op;
        cin>>val;
        if(op==0){
            cout<<op<<" "<<val<<" "<<rbt.deletion(val)<<endl;
            rbt.prettyPrint();
            cout<<endl;
        }
        else if(op==1){
            cout<<op<<" "<<val<<" "<<rbt.insert(val)<<endl;
            rbt.prettyPrint();
            cout<<endl;
        }
        else if(op==2)
            cout<<op<<" "<<val<<" "<<rbt.searchNode(val)<<endl;
        else if(op==3)
            cout<<op<<" "<<val<<" "<<rbt.lesser(val)<<endl;
        else
            cout<<"Wrong operation"<<endl;
    }

    return 0;
}
