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
		for(int i=0; i<level-1; i++) cout<<"   |     ";
		if(level!=0) cout<<"   +-----";
		if(head==NULL) 
		{
			cout<<"|B NULL|"<<endl;
			return;
		}
		if(head->color==1) cout<<"|R ";
		else cout<<"|B ";
		cout<<head->value<<"|"<<endl;
		if(head->big==NULL && head->small==NULL) return;
		print(head->big, level+1);
		print(head->small, level+1);
		return;
	}
	node* uncle(node* data)
	{
		if(data==NULL || data->parent==NULL || data->parent->parent==NULL) return NULL;
		if(data->parent->value > data->parent->parent->value) return data->parent->parent->small;
		return data->parent->parent->big;
	}
	void fix_violation(node* ins)
	{
		if(ins==this->root) 
		{
			ins->color=0;
			return;
		}
		// cout<<"RAW for vio_fix: "<<ins->value<<endl;
		// print();
		//detect violation
		if(ins->parent->color == ins->color)
		{
			// cout<<"violation detected"<<endl;
			node* uncle_p=uncle(ins);
			bool col_uncle;
			if(uncle_p==NULL) col_uncle=0;
			else col_uncle=uncle_p->color;
			if(col_uncle==1) //uncle is red
			{
				// cout<<"Uncle is red "<<endl;
				//recolor parent, gp, uncle
				ins->parent->color=!ins->parent->color;
				ins->parent->parent->color=!ins->parent->parent->color;
				uncle_p->color=!uncle_p->color;
				fix_violation(ins->parent->parent);
			}
			if(col_uncle==0) //uncle is black
			{
				// cout<<"Uncle is black "<<endl;
				bool res1=ins->parent->value > ins->value, res2=ins->parent->value > ins->parent->parent->value;
				if((res1==1 && res2==1)||(res1==0 && res2==0)) //case triangle
				{
					if(res1==1)
					{ 
						// cout<<"Case Triangle Rotate right"<<endl;
						rotate_right(ins->parent);
						fix_violation(ins->big);
					}
					else
					{
						// cout<<"Case Triangle Rotate left"<<endl;
						rotate_left(ins->parent);
						fix_violation(ins->small);
					}
				}
				else //case line
				{
					if(res2==1) //parent right of grand, rotate rotate_left
					{
						// cout<<"Case right line, rotate left"<<endl;
						rotate_left(ins->parent->parent);
						ins->parent->color=!ins->parent->color;
						ins->parent->small->color=!ins->parent->small->color;
					}
					if(res2==0) //parent to left of grand, rotate right
					{
						// cout<<"Case left line, rotate_right"<<endl;
						rotate_right(ins->parent->parent);
						ins->parent->color=!ins->parent->color;
						ins->parent->big->color=!ins->parent->big->color;
					}
				}
			}
		}
	}
	void insert(int value)
	{
		node *ins=insert(value, 1, this->root);
	}
	void insertrbt(int value)
	{
		node *ins=insert(value, 1, this->root);
		if(ins!=NULL) fix_violation(ins);
		else return;
	}
	node* insert(int value, bool color, node* head)
	{
		if(this->root==NULL)
		{
			root= new node;
			root->value=value;
			root->color=color;
			root->parent=NULL;
			root->big=NULL, root->small=NULL;
			return this->root;
		}
		if(head->value < value && head->big!=NULL) return insert(value, color, head->big);
		else if(head->value > value && head->small!=NULL) return insert(value, color, head->small); 
		else if(head->value ==  value) return NULL;
		if(head->value < value && head->big==NULL)
		{
			node *tempb=new node;
			tempb->parent=head;
			tempb->color=color; //red
			tempb->big=NULL, tempb->small=NULL;
			tempb->value=value;
			head->big=tempb;
			return tempb;
		}
		if(head->value >= value && head->small==NULL) //insert at small
		{
			node *temps=new node;
			temps->parent=head;
			temps->color=color; //red
			temps->big=NULL, temps->small=NULL;
			temps->value=value;
			head->small=temps;
			return temps;
		}
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
};
int main()
{
	rbtree t1;
	for(int i=0; i<200; i++) t1.insertrbt(rand()%3000);
	t1.print();
}