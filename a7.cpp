#include <stdio.h> 
#include <iostream> 
#include <math.h>
#include<limits.h>
#include <cfloat>
#include <vector>
#include <assert.h>
typedef long long int ll;
using namespace std;

void print_vec(vector<ll> data)
{
	for(ll i=0; i<data.size(); i++) cout<<data[i]<<" ";
	cout<<endl;
}
ll fact(ll n)
{
	if(n==0 || n==1) return 1;
	return n*fact(n-1);
}
ll ncr(ll n, ll r)
{
	return fact(n)/(ll)(fact(n-r)*fact(r));
}
ll countseq(vector<ll> data, ll n)
{
	if(n<=2) return 1;
	ll l=0;
	for(ll i=0; i<n; i++) if(data[i]<data[0]) l++;
	ll r=n-1-l;
	vector<ll> al;
	vector<ll> ar;

	for(ll i=1; i<n; i++)
	{
		if(data[i]<data[0])
		{
			al.push_back(data[i]);
		}
		else if(data[i]>data[0])
		{
			ar.push_back(data[i]);
		}
	}

	ll iso_l=countseq(al, l);
	ll iso_r=countseq(ar, r);
	ll isodata= iso_l*iso_r*ncr(n-1, l);
	return isodata;
}
vector<ll> get_bin_seq(ll no, ll size)
{
	vector<ll> ans(size);
	ll temp=no;
	for(ll i=0; i<size; i++)
	{
		ans[size-i-1]=temp%2;
		temp=temp/2;
	}
	return ans;
}
ll n_zeros(vector<ll> data)
{
	ll ans=0;
	for(ll i=0; i<data.size(); i++)
	{
		if(data[i]==0) ++ans;
	}
	return ans;
}
vector<vector<ll> > findallseq(vector<ll> data, ll n)
{
	if(n<=2)
	{
		vector<vector<ll> > ans;
		vector<ll> seq;
		for(ll i=0; i<data.size(); i++) seq.push_back(data[i]);
		ans.push_back(seq);
		return ans;
	}
	vector<ll> al;
	vector<ll> ar;
	for(ll i=1; i<n; i++)
	{
		if(data[i]<data[0])
		{
			al.push_back(data[i]);
		}
		else if(data[i]>data[0])
		{
			ar.push_back(data[i]);
		}
	}
	ll l=al.size(), r=ar.size();
	assert(l+r==n-1);

	vector<vector<ll> > iso_l=findallseq(al, l);
	vector<vector<ll> > iso_r=findallseq(ar, r);
	vector<vector<ll> > ans;
	for(ll i=0; i<pow(2, l+r); i++)
	{
		vector<ll> seq=get_bin_seq(i, l+r);
		if(n_zeros(seq)==r) //Number of 0s is r
		{
			for(ll j=0; j<iso_l.size(); ++j)
			{
				for(ll k=0; k<iso_r.size(); ++k)
				{
					vector<ll> to_push;
					to_push.push_back(data[0]);
					ll counter1=0, counter2=0;
					for(ll l=0; l<seq.size(); l++)
					{
						if(seq[l]==0)
						{
							to_push.push_back(iso_r[k][counter1]);
							++counter1;	
						} 
						else if(seq[l]==1)
						{
							to_push.push_back(iso_l[j][counter2]);
							++counter2;	
						} 
					}
					ans.push_back(to_push);
				}
			}
		}
	}
	return ans;
}
class tree
{
public:
	struct node
	{
		ll value;
		node* big=NULL; 
		node* small=NULL; 
		node* parent=NULL; 
	};
	node *root=NULL;
	ll size;

	void print()
	{
		print(this->root);
	}
	void print(node *root, ll level=0)
	{
		for(ll i=0; i<level-1; i++) cout<<"  |     ";
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
	node* new_node(node* parent, ll value)
	{
		node *tempb=new node;
		tempb->parent=parent;
		tempb->big=NULL, tempb->small=NULL;
		tempb->value=value;
		return tempb;
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
};

class bst_tree: public tree
{
public:
	void bst_ins(ll value)
	{
		if(this->root==NULL)
		{
			this->root=new_node(NULL, value);
			return;
		}
		bst_ins(this->root, value);
		return;
	}
	void bst_ins(node* node, ll value)
	{
		if(value > node->value)
		{
			if(node->big==NULL)
			{
				node->big = new_node(node, value);
			}
			else bst_ins(node->big, value);
		}
		if(value < node->value)
		{
			if(node->small==NULL)
			{
				node->small = new_node(node, value);
			}
			else bst_ins(node->small, value);
		}
		return;
	}

	void bst_cons(vector<ll> data, ll n)
	{	
		assert(data.size()==n);
		for(ll i=0; i<n; i++) bst_ins(data[i]);
		return;
	}
	void bst_prn()
	{
		this->print();
		this->traversal();
	}
	void bst_free()
	{
		bst_free(this->root);
	}
	void bst_free(node* node)
	{
		if(node->big!=NULL) bst_free(node->big);
		if(node->small!=NULL) bst_free(node->small);
		delete node;
		return;
	}
};
bool bst_same(tree::node *t1, tree::node* t2)
{
	if(t1==NULL && t2==NULL) return true;
	if(t1==NULL && t2!=NULL) return false;
	if(t1!=NULL && t2==NULL) return false;
	if(t1->value!=t2->value) return false;
	if(bst_same(t1->small, t2->small)==true && bst_same(t1->big, t2->big)==true) return true;
}
bool checkall(vector<vector<ll> > sequences, vector<ll> data, int n)
{
	bst_tree t1;
	t1.bst_cons(data, n);

	bool flag = true; //assume all trees identical
	for(ll i=0; i<sequences.size(); i++)
	{
		bst_tree t2;
		t2.bst_cons(sequences[i], n);
		if(bst_same(t1.root, t2.root)==true) 
		{
			t2.bst_free();
		}
		else 
		{
			flag=false; //trees not same, set flag false
			t2.bst_free();
		}
	}
	return flag;
}
int main()
{
	ll n;
	cin>>n;
	vector<ll> data(n);
	for(ll i=0; i<n; i++) cin>>data[i];
	
	cout<<"Input n= "<<n<<endl;
	cout<<"Data: ";
	for(ll i=0; i<n; i++) cout<<data[i]<<" ";
	cout<<endl<<endl;

	ll countiso=countseq(data, n);
	cout<<"Sequence count: "<<endl;
	cout<<"Total number of sequences= "<<countiso<<endl;
	cout<<endl;

	vector<vector<ll> > sequences=findallseq(data, n); 
	cout<<"All sequences"<<endl;
	for(ll i=0; i<sequences.size(); i++)
	{
		cout<<"Sequence "<<i+1<<": ";
		print_vec(sequences[i]);
	}
	cout<<endl;

	cout<<"Tree constructed from initial sequence"<<endl;
	bst_tree t1;
	t1.bst_cons(data, n);
	t1.bst_prn();
	cout<<endl;

	bool flag = checkall(sequences, data, n);
	if(flag==true)
	{
		cout<<"All trees are same"<<endl;
	}
	else cout<<"All trees are not same"<<endl;
	return 0;
}