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
	node *head=NULL;
	int size;
public:
	void print()
	{
		print(this->head);
	}
	void print(node *head, int level=0)
	{
		for(int i=0; i<level-1; i++) cout<<"  |     ";
		if(level!=0) cout<<"  +-----";
		if(head==NULL) 
		{
			cout<<"|NULL|"<<endl;
			return;
		}
		cout<<"|"<<head->value<<"|"<<endl;
		if(head->big==NULL && head->small==NULL) return;
		print(head->big, level+1);
		print(head->small, level+1);
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
		this->head=new_node(NULL, 0);
		this->head=readtree(this->head, 1);
	}
	node* readtree(node *head, int n)
	{
		//base case
		if(n==0) return head;
		this->size++;
		int value, a, b;
		cin>>value>>a>>b;
		head->value=value;		
		if(a!=0)
		{
			head->small=new_node(head, 0);
			readtree(head->small, a);
		}
		else head->small==NULL;
		if(b!=0)
		{
			head->big=new_node(head, 0);
			readtree(head->big, b);
		}
		else head->big==NULL;
		return head;
	}
	void makeskew()
	{
		makeskew(this->head);
	}
	void makeskew(node *head)
	{
		int count=0;
		while(head->small!=NULL)
		{
			rotate_right(head);
			head=head->parent;
		}
		if(head->big!=NULL) makeskew(head->big);
		return;
	}
	void bubbleSort() 
	{ 
		for(int i=0; i<this->size; i++)
		{
			node* j=this->head;
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
		rebalance(this->head, 1);
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
		preorder(this->head);
		cout<<endl;
		cout<<"Inorder traversal: "<<endl;
		inorder(this->head);
		cout<<endl;
		return;
	}
	void swap_child(node* head)
	{
		node* temp=head->small;
		head->small=head->big;
		head->big=temp;
		return;
	}
	void rotate_left(node* y)
	{
		node* parent=y->parent;
		node* x=y->big;
		if(x==NULL) return;
		if(parent!=NULL)
		{
			if(y->value == parent->big->value)
			{
				parent->big=x;
			}
			else
			{
				parent->small=x;
			}
			x->parent=parent;
		}
		else //this is the head, update new head
		{
			this->head=x;
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
			if(x->value == parent->big->value)
			{
				parent->big=y;
			}
			else
			{
				parent->small=y;
			}
			y->parent=parent;
		}
		else //this is the head, update new head
		{
			this->head=y;
			y->parent=NULL;
		}

		x->small=y->big;
		if(y->big!=NULL) y->big->parent=x;
		
		y->big=x;
		x->parent=y;

	}
	int get_size(node *head, int sense)
	{
		if(head==NULL) return 0;
		node* temp=head;
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