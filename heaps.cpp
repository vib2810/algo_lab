#include<bits/stdc++.h>
#include <complex> 
using namespace std;

class heap
{
protected:
	double *data;
	int data_length;
	int length;
public:
	void print()
	{
		cout<<"Length of Heap="<<this->length<<endl;
		for(int i=0; i<this->length; i++) cout<<data[i]<<" ";
		cout<<endl;
	}
	int get_parent(int node_no)
	{
		if((node_no%2)==0) return (node_no-2)/2;
		if((node_no%2)!=0) return (node_no-1)/2;
	}
	void swap(int parent, int node_no)
	{
		double temp=data[parent];
		data[parent]=data[node_no];
		data[node_no]=temp;
	}
	void ensure_capacity()
	{
		if(this->length > this->data_length)
		{
			double *data_new=new double[this->data_length+100];
			for(int i=0; i<this->data_length; i++)  data_new[i]=this->data[i];
			free(this->data);
			this->data=data_new;
			this->data_length+=100;
		}
	}
	void insert(double ins);
	double pop();
};
class minheap: public heap
{
public:
	minheap()
	{
		this->data=new double[100]; //initialize the heap with 100 size initially
		this->length=0;
		this->data_length=100;
	}
	//for node 0, children are on 2*0+1 and 2*0+2
	void insert(double ins)
	{
		this->length++;
		ensure_capacity();
		this->data[length-1]=ins;
		heapifyUp(this->length-1);
	}
	double pop()
	{
		if(this->length==0)
		{
			cout<<"Empty"<<endl;
			return -1;
		}
		double ans=data[0];
		data[0]=data[length-1];
		this->length--;
		heapifyDown(0);
		return ans;
	}
	void heapifyUp(int node_no)
	{
		if(node_no==0) return;
		int parent=get_parent(node_no);
		// cout<<"heapifyUp "<<data[node_no]<<" Parent"<<data[node_no]<<" ->"<<data[parent]<<endl;
		if(data[parent]>data[node_no]) 
		{
			swap(parent, node_no);
			heapifyUp(parent);
		}
	}
	void heapifyDown(int node_no)
	{
		if(node_no>length-1) return;
		int left=2*node_no+1;
		int right=2*node_no+2;
		if(left>length-1) return;
		if(right>length-1)
		{
			if(data[left]<data[node_no]) swap(left, node_no);
		}
		else
		{
			if(data[node_no]>data[left] || data[node_no]>data[right])
			{
				if(data[left]<data[right])
				{
					swap(left, node_no);
					heapifyDown(left);
				}
				else
				{
					swap(right, node_no);
					heapifyDown(right);
				}
			}
		}
		return;
	}
};
class maxheap: public heap
{
public:
	maxheap()
	{
		this->data=new double[100]; //initialize the heap with 100 size initially
		this->length=0;
		this->data_length=100;
	}
	//for node 0, children are on 2*0+1 and 2*0+2
	void insert(double ins)
	{
		this->length++;
		ensure_capacity();
		this->data[length-1]=ins;
		heapifyUp(this->length-1);
	}
	double pop()
	{
		if(this->length==0)
		{
			cout<<"Empty"<<endl;
			return -1;
		}
		double ans=data[0];
		data[0]=data[length-1];
		this->length--;
		heapifyDown(0);
		return ans;
	}
	void heapifyUp(int node_no)
	{
		if(node_no==0) return;
		int parent=get_parent(node_no);
		if(data[parent]<data[node_no]) 
		{
			swap(parent, node_no);
			heapifyUp(parent);
		}
	}
	void heapifyDown(int node_no)
	{
		if(node_no>length-1) return; //out of bounds
		int left=2*node_no+1;
		int right=2*node_no+2;
		if(left>length-1) return; //out of bounds
		if(right>length-1)
		{
			if(data[left]>data[node_no]) swap(left, node_no);
		}
		else
		{
			if(data[node_no]<data[left] || data[node_no]<data[right])
			{
				if(data[left]>data[right])
				{
					swap(left, node_no);
					heapifyDown(left);
				}
				else
				{
					swap(right, node_no);
					heapifyDown(right);
				}
			}
		}
		return;
	}
};

int main()
{
	minheap m1;
	maxheap m2;
	for(int i=0; i<999; i++) 
	{
		double rand=(random()%100000)/(10000.0);
		m1.insert(rand);
		m2.insert(rand);
	}
	for(int i=0; i<1000; i++) 
	{
		double pop1=m1.pop();
		double pop2=m2.pop();
		if(pop1==pop2) cout<<"samamama";
		cout<<"Popped: "<<pop1<<" "<<pop2<<endl;
	}
}