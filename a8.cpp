#include<bits/stdc++.h>
#include <complex> 
using namespace std;
class multiheap
{
protected:
	int **data;
	int n_nodes, p, n_keys; //n is the number of nodes, p is each node's capacity
	int n_nodes_max;
public:	
	multiheap(){}
	int get_parent(int node_no)
	{
		if((node_no%2)==0) return (node_no-2)/2;
		if((node_no%2)!=0) return (node_no-1)/2;
	}
	int get_min(int node_no)
	{
		int n_empty= n_nodes*p - n_keys;
		int index= this->p - n_empty;
		
		int min=INT_MAX;
		for(int i=0; i<p; i++)
		{
			if(node_no==(n_nodes-1) && i>=index) break;
			if(min > data[node_no][i]) min=data[node_no][i];
		}
		return min;
	}
	int get_max(int node_no)
	{
		if(n_keys==0) return -1; 
		int n_empty= n_nodes*p - n_keys;
		int index= this->p - n_empty;
		
		int max=INT_MIN;
		for(int i=0; i<p; i++)
		{
			if(node_no==(n_nodes-1) && i>=index) break;
			if(max < data[node_no][i]) max=data[node_no][i];
		}
		return max;
	}
	void print()
	{
		cout<<"Printing Heap"<<endl;
		cout<<"n_nodes: "<<n_nodes<<" n_keys: "<<n_keys<<endl;
		int n_empty= n_nodes*p - n_keys;
		int index= this->p - n_empty;

		for(int i=0; i<n_nodes; i++)
		{
			cout<<"[ ";
			for(int j=0; j<p; j++)
			{
				if(i==(n_nodes-1) && j>=index) cout<<"XXX ";
				else
				{
					cout<<data[i][j]<<" ";
				}
			}
			cout<<"]"<<" ->Node no: "<<i<<endl;
		}
		cout<<endl;
	}
	void initheap(int p, int n_max)
	{
		this->p=p;
		this->n_nodes_max=n_max;
		this->n_nodes=0;
		this->n_keys=0;

		this->data= new int*[n_nodes_max];
		for(int i=0; i<n_nodes_max; i++)
		{
			this->data[i]=new int[p];
		}
	}
	void insert(int key)
	{
		bool empty=false;
		if(n_nodes*p > n_keys) empty=true;
		else empty=false;
		if(empty==true)
		{
			int n_empty= n_nodes*p - n_keys;
			int index= this->p - n_empty;
			assert(index<p);
			this->data[n_nodes-1][index]=key;
			this->n_keys++;
		}
		else if(empty==false)
		{
			assert(n_nodes*p == n_keys);
			this->data[n_nodes][0]=key;
			this->n_nodes++;
			this->n_keys++;
		}
		heapifyUp(this->n_nodes-1);
	}
	void swap(int q_node_no, int child_node_no)
	{
		int n_empty;	
		if(child_node_no==n_nodes-1) n_empty= n_nodes*p - n_keys;
		else n_empty=0;

		vector<int> top_p, rem;
		int temp[2*p-n_empty];
		for(int i=0; i<p; i++) temp[i]=data[child_node_no][i];
		for(int i=0; i<(p-n_empty); i++) temp[i+p]=data[q_node_no][i];
		sort(temp, temp+(2*p-n_empty),greater<int>()); 
		
		for(int i=0; i<p; i++) top_p.push_back(temp[i]);
		for(int i=0; i<(p-n_empty); i++) rem.push_back(temp[i+p]);
		
		for(int i=0; i<top_p.size(); i++) data[child_node_no][i]=top_p[i];
		for(int i=0; i<rem.size(); i++) data[q_node_no][i]=rem[i];
		return;
	}
	void heapifyUp(int q_node_no)
	{
		if(q_node_no==0) return;
		int r_node_no=get_parent(q_node_no);
		int r_min=get_min(r_node_no);
		int q_max=get_max(q_node_no);
		if(r_min >= q_max) return;
		else
		{
			swap(q_node_no, r_node_no);
			heapifyUp(r_node_no);
		}
	}
	void heapifyDown(int q_node_no)
	{
		if(q_node_no>n_nodes-1) return;
		int l_node_no=2*q_node_no+1;
		int r_node_no=2*q_node_no+2;
		
		if(l_node_no>n_nodes-1) return;
		
		int q_min=get_min(q_node_no);
		int l_max=get_max(l_node_no);
		int r_max=get_max(r_node_no);
		
		if(r_node_no>n_nodes-1)
		{
			if(l_max<q_min) swap(l_node_no, q_node_no);
		}
		else
		{
			if(q_min<l_max || q_min<r_max)
			{
				if(l_max>r_max)
				{
					swap(l_node_no, q_node_no);
					heapifyDown(l_node_no);
				}
				else
				{
					swap(r_node_no, q_node_no);
					heapifyDown(r_node_no);
				}
			}
		}
		return;
	}
	int findmax()
	{
		return get_max(0);
	}
	void delmax()
	{
		int n_empty= n_nodes*p - n_keys;
		int index= this->p - n_empty -1;
		
		//to get index of max element in the 0th node
		int max=INT_MIN;
		int max_ind=-1;
		for(int i=0; i<p; i++)
		{
			if(0==(n_nodes-1) && i>index) break;
			if(max < data[0][i]) 
			{
				max=data[0][i];
				max_ind=i;
			}
		}
		if(n_nodes==1)
		{
			assert(n_keys<=p);
			data[0][max_ind]= data[0][n_keys-1] ;
			this->n_keys--;
		}
		else
		{
			assert(max==get_max(0));
			if(index!=0) 
			{
				data[0][max_ind] = data[n_nodes-1][index];
				data[n_nodes-1][index]=0;
				this->n_keys--;
			} 
			else if(index==0) //means that only 1 entry in the last node at 0
			{
				data[0][max_ind] = data[n_nodes-1][index];
				data[n_nodes-1][index]=0;
				this->n_keys--;
				this->n_nodes--;
			}
			heapifyDown(0);
		}
	}
};
int main()
{
	int p, n_input;
	cin>>p;
	cin>>n_input;
	int input[n_input];
	for(int i=0; i<n_input; i++) cin>>input[i];
	multiheap h;
	h.initheap(p, (n_input/p)+1);
	for(int i=0; i<n_input; i++)
	{
		h.insert(input[i]);
	}
	cout<<n_input<<" insertions made"<<endl;
	h.print();

	vector<int> values;
	for(int i=0; i<n_input; i++)
	{
		values.push_back(h.findmax());
		h.delmax();
	}
	cout<<n_input<<" deletions made"<<endl;

	for(int i=0; i<values.size(); i++)
	{
		cout<<values[values.size()-i-1]<<" ";
	}
	cout<<endl; 
}