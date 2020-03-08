#include <stdio.h> 
#include <iostream> 
#include <math.h>
#include<limits.h>
#include <cfloat>
using namespace std;
class tree
{
	struct node
	{
		int value;
		node* big=NULL; 
		node* small=NULL; 
		node* parent=NULL; 
	};
	node *root=NULL;
	int size;
public:
	void print()
	{
		print(this->root);
	}
	void print(node *root, int level=0)
	{
		for(int i=0; i<level-1; i++) cout<<"  |     ";
		if(level!=0) cout<<"  +-----";
		if(root==NULL) 
		{
			cout<<"|NULL|"<<endl;
			return;
		}
		cout<<"|"<<root->value<<"|"<<endl;
		if(root->big==NULL && root->small==NULL) return;
		print(root->big, level+1);
		print(root->small, level+1);
		return;
	}
	node* new_node(node* parent, int value)
	{
		node *tempb=new node;
		tempb->parent=parent;
		tempb->big=NULL, tempb->small=NULL;
		tempb->value=value;
		return tempb;
	}
	void readtree()
	{
		this->root=new_node(NULL, 0);
		this->root=readtree(this->root, 1);
	}
	node* readtree(node *root, int n)
	{
		//base case
		if(n==0) return root;
		this->size++;
		int value, a, b;
		cin>>value>>a>>b;
		root->value=value;		
		if(a!=0)
		{
			root->small=new_node(root, 0);
			readtree(root->small, a);
		}
		else root->small==NULL;
		if(b!=0)
		{
			root->big=new_node(root, 0);
			readtree(root->big, b);
		}
		else root->big==NULL;
		return root;
	}
	void makeskew()
	{
		makeskew(this->root);
	}
	void makeskew(node *root)
	{
		int count=0;
		while(root->small!=NULL)
		{
			rotate_right(root);
			root=root->parent;
		}
		if(root->big!=NULL) makeskew(root->big);
		return;
	}
	void bubbleSort() 
	{ 
		for(int i=0; i<this->size; i++)
		{
			node* j=this->root;
			while(j->big!=NULL)
			{
				if(j->big->value < j->value) swap(j, j->big);
				j=j->big;
				if(j==NULL) break;
			}
		}
	} 

	void swap(node *a, node *b) 
	{ 
	    swap_child(a);
	    rotate_right(a);
	    swap_child(a);
	} 
	void rebalance()
	{
		rebalance(this->root, 1);
	}
	void rebalance(node *tree_root, int sense) //sense 1 for right
	{
		//locate middle
		int size=get_size(tree_root, sense);
		node* temp=tree_root;
		for(int i=0; i<ceil(size/2); i++)
		{
			if(sense>0) temp=temp->big;
			if(sense<0) temp=temp->small;		
		} 
		// cout<<"Middle element: "<<temp->value<<endl;
		if(sense>0)
		{
			while(tree_root->value != temp->value)
			{ 
				rotate_left(tree_root);
				tree_root=tree_root->parent;
			}
		}
		if(sense<0)
		{
			while(tree_root->value != temp->value)
			{ 
				rotate_right(tree_root);
				tree_root=tree_root->parent;
			}
		}
		if(tree_root->big!=NULL) rebalance(tree_root->big, 1);
		if(tree_root->small!=NULL) rebalance(tree_root->small, -1);
	}
	//Utility Functions
	void inorder(node* node) 
	{ 
	    if (node == NULL) return; 
	    inorder(node->small); 
	    cout << node->value << " "; 
	    inorder(node->big); 
	} 
	void preorder(node* node) 
	{ 
	    if (node == NULL) return; 
	    cout << node->value << " "; 
	    preorder(node->small);  
	    preorder(node->big); 
	}  
	void traversal()
	{
		cout<<"Preorder traversal: "<<endl;
		preorder(this->root);
		cout<<endl;
		cout<<"Inorder traversal: "<<endl;
		inorder(this->root);
		cout<<endl;
		return;
	}
	void swap_child(node* root)
	{
		node* temp=root->small;
		root->small=root->big;
		root->big=temp;
		return;
	}
	void rotate_left(node* y)
	{
		node* parent=y->parent;
		node* x=y->big;
		if(x==NULL) return;
		if(parent!=NULL)
		{
			if(parent->big != NULL)
			{
				if(y->value == parent->big->value)
				{
					parent->big=x;
				}
				else
				{
					parent->small=x;
				}
			}
			else //parents big is NULL
			{
				parent->small=x;
			}
			x->parent=parent;
		}
		else //this is the root, update new root
		{
			this->root=x;
			x->parent=NULL;
		}
		y->big=x->small;
		if(x->small!=NULL) x->small->parent=y;

		x->small=y;
		y->parent=x;
	}
	void rotate_right(node* x)
	{
		node* parent=x->parent;
		node* y=x->small;
		if(y==NULL) return;
		if(parent!=NULL)
		{
			if(parent->big!=NULL)
			{
				if(x->value == parent->big->value)
				{
					parent->big=y;
				}
				else
				{
					parent->small=y;
				}
			}
			else //parent big is NULL
			{
				parent->small=y;
			}
			y->parent=parent;
		}
		else //this is the root, update new root
		{
			this->root=y;
			y->parent=NULL;
		}

		x->small=y->big;
		if(y->big!=NULL) y->big->parent=x;
		
		y->big=x;
		x->parent=y;
	}
	int get_size(node *root, int sense)
	{
		if(root==NULL) return 0;
		node* temp=root;
		int count=0;
		while(temp!=NULL)
		{
			++count; 
			if(sense>0) temp=temp->big;
			if(sense<0) temp=temp->small;
		}
		return count;
	}
};
int main()
{
	int n;
	cin>>n;
	tree t1;
	t1.readtree();

	cout<<"----------Initial Tree----------"<<endl;
	t1.print();
	t1.traversal();
	
	cout<<"\n----------Skewed Tree----------"<<endl;
	t1.makeskew();
	t1.traversal();
	t1.print();
	
	// t1.test_swap();
	cout<<"\n----------Bubble Sorted Tree----------"<<endl;
	t1.bubbleSort();
	t1.traversal();
	t1.print();

	cout<<"\n----------Rebalanced Tree----------"<<endl;
	t1.rebalance();
	t1.traversal();
	t1.print();
}