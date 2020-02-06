#include <stdio.h> 
#include <iostream> 
#include <math.h>
#include<limits.h>
#include <cfloat>
using namespace std;
class rbtree
{
	struct node
	{
		bool color; //0-Black 1-Red
		int value;
		node* big=NULL; 
		node* small=NULL; 
		node* parent=NULL; 
	};
	node *root=NULL;
public:
	void print()
	{
		print(this->root);
	}
	void print(node *head, int level=0)
	{
		if(head==NULL) return;
		for(int i=0; i<level; i++) cout<<"\t";
		if(head->color==1) cout<<"|R ";
		else cout<<"|B ";
		cout<<head->value<<"|"<<endl;
		print(head->big, level+1);
		print(head->small, level+1);
		return;
	}
	void insert(int value)
	{
		if(root==NULL)
		{
			root= new node;
			root->value=value;
			root->parent=NULL;
			root->big=NULL, root->small=NULL;
			return;
		}
		node *temp=root;
		while(1)
		{
			if(temp->value < value && temp->big!=NULL) temp=temp->big;
			else if(temp->value >= value && temp->small!=NULL) temp=temp->small;
			else break;
		}
		if(temp->value < value) //insert at big
		{
			node *tempb=new node;
			tempb->parent=temp;
			tempb->big=NULL, tempb->small=NULL;
			tempb->value=value;
			temp->big=tempb;
		}
		if(temp->value >= value) //insert at small
		{
			node *temps=new node;
			temps->parent=temp;
			temps->big=NULL, temps->small=NULL;
			temps->value=value;
			temp->small=temps;
		}
		return;
	}
	void rotate_left(node* y)
	{
		node* parent=y->parent;
		node* x=y->big;
		if(x==NULL) return;
		if(parent!=NULL)
		{
			if(y->value > parent->value)
			{
				parent->big=x;
			}
			else
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
			if(y->value > parent->value)
			{
				parent->big=y;
			}
			else
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
	void rot()
	{
		rotate_right(this->root->big);
		cout<<"right"<<endl;
		print();

		rotate_left(this->root->big);
		cout<<"left"<<endl;
		print();
	}
	bool remove(int value)
	{
		// if(this->root->value==value)
		// {
		// 	this->root->big
		// 	this->root->small
		// }
	}
};
int main()
{
	rbtree t1;
	t1.insert(12);
	t1.insert(1);
	t1.insert(11);
	t1.insert(9);
	t1.insert(10);
	t1.insert(2);
	for(int i=0; i<10; i++) t1.insert(rand()%50);
	t1.print();
	t1.rot();
}