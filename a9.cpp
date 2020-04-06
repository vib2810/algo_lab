#include<bits/stdc++.h> 
using namespace std; 
template <typename T>
ostream& operator<<(ostream& out, const pair<T,T>& p)
{
    out << "(" << p.first << "," << p.second << ")";
    return out;
}
void print_arr(int data[], int n)
{
	cout<<"Printing array: ";
	for(int i=0; i<n; i++)
	{
		cout<<data[i]<<" ";
	}
	cout<<endl;
}

template <typename T>
void print_vec(vector<T> data)
{
	cout<<"[ ";
	for(int i=0; i<data.size(); i++)
	{
		cout<<data[i]<<" ";
	}
	cout<<"]"<<endl;
}
class graph
{
public:
    int n; //no of nodes
    vector< vector<int> > adj; //adjacency list    
    vector<bool> color; //color[node_no]==1 means blue
    vector<int> orignal_node_nos;

public:
	graph(){};
    graph(int n, vector<bool> color)
    {
    	assert(color.size()==n);
        this->n=n;
        this->color=color;
        this->adj.resize(n);
    }
    graph(int n, vector<bool> color, vector<int> orignal_node_nos)
    {
    	assert(color.size()==n);
        this->n=n;
        this->color=color;
        this->adj.resize(n);
        this->orignal_node_nos=orignal_node_nos;
    }
    void addEdge(pair<int, int> edge)
    { 
    	bool flag1=true, flag2=true;
    	for(int i=0; i<adj[edge.first].size(); i++)
    	{
    		if(adj[edge.first][i]==edge.second) {flag1=false; break;}
    	}
    	for(int i=0; i<adj[edge.second].size(); i++)
    	{
    		if(adj[edge.second][i]==edge.first) {flag2=false; break;}
    	}
        if(flag1==true) adj[edge.first].push_back(edge.second); 
        if(flag2==true) adj[edge.second].push_back(edge.first); 
    } 
    void print()
    { 
        cout<<"No of Nodes: "<<this->n<<endl;
        for (int i=0; i<n; i++) 
        { 
        	if(color[i]==1) cout<<"[b] ";
        	else cout<<"[r] ";
            cout <<i<<"-> "; 
            for (int j=0; j<adj[i].size(); j++) 
            {
            	if(j!=0) cout << ", "; 
            	cout << adj[i][j];
            } 
            cout<<endl;
        } 
    } 
    void print_mono()
    { 
        cout<<"No of Nodes: "<<this->n<<endl;
        for (int i=0; i<n; i++) 
        { 
        	if(color[i]==1) cout<<"[b] ";
        	else cout<<"[r] ";
            cout <<orignal_node_nos[i]<<"-> "; 
            for (int j=0; j<adj[i].size(); j++) 
            {
            	if(j!=0) cout << ", "; 
            	cout << orignal_node_nos[adj[i][j]];
            } 
            cout<<endl;
        } 
    } 
    graph getcolgraph(bool col)
    {
    	vector<int> orignal_node_nos;
    	vector<bool> color;
		vector<pair<int,int> > edges_ans;
    	map<int, int> temp; //to retrieve sub-node nos from original ones; temp[orig]=sub
    	int n=0;
    	for(int i=0; i<this->n; i++)
    	{
    		if(this->color[i]==col)
    		{
    			color.push_back(col);
    			orignal_node_nos.push_back(i);
    			temp[i]=n;
    			n++;
    		}
    	}
    	graph ans(n, color, orignal_node_nos);
    	for(int i=0; i<this->n; i++)
    	{
    		for(int j=0; j<this->adj[i].size(); j++)
    		{
    			if(this->color[i]==col && this->color[this->adj[i][j]]==col)
    			{
    				edges_ans.push_back(make_pair(temp[i], temp[this->adj[i][j]])); //make edges with sub-node nos
    			}
    		}
    	}
    	for(int i=0; i<edges_ans.size(); i++)
	    {
	    	ans.addEdge(edges_ans[i]);
	    }
    	return ans;
    }
    vector<int> back_track(vector<int> parents, int new_node, int child)
    {
    	vector<int> ans;
    	ans.push_back(new_node);
    	while(1)
    	{
    		ans.push_back(parents[new_node]);
    		new_node=parents[new_node];
    		if(new_node==child) break;
    	}
    	return ans;
    }

    //visited =0 node hasnt been explored yer
    //visited =1 node is in stack, not yet popped
    //visited =2 node has been popped from the stack
    void dfs1(int new_node, vector<int> &parents, vector< vector<int> > &cycles, vector<int>& visited)
    {
		if(visited[new_node]==2) return;
		visited[new_node]=1;
    	for(int i=0; i<adj[new_node].size(); i++) 
        {
            int child=adj[new_node][i];
            if(visited[child]==0) //if child hasnt been expored yet 
            {
            	parents[child]=new_node;
            	dfs1(child, parents, cycles, visited);
            }
            else if(visited[child]==1) //child has been visited
            {
				if(parents[new_node]==child) 
				{
					//2 member cycle
					continue;
				}
				//back edge
            	vector<int> new_cycle= back_track(parents, new_node, child);
            	cycles.push_back(new_cycle);
            }
        }
        visited[new_node]=2;
    }

    vector<pair<int,int> > cycles() //returns the forrest_edges
    {
    	vector<pair<int,int> > forrest_edges;
		vector<int> parents(n);
        for(int i=0; i<parents.size(); i++) parents[i]=-1;

    	vector< vector<int> > cycles;
    	vector<int> visited(n);
        for(int i = 0; i < this->n; ++i) visited[i]=0;

    	for(int i=0; i<n; i++) 
    	{
    		this->dfs1(i, parents, cycles, visited);
			for(int j=0; j<parents.size(); j++)
			{
				if(parents[j]!=-1)
				{
					forrest_edges.push_back( make_pair(orignal_node_nos[j], orignal_node_nos[parents[j]] ));
					parents[j]=-1;
				}
			}
    	}

    	for(int i=0; i<cycles.size(); i++)
        {
        	cout<<"( ";
        	for(int j=0; j<cycles[i].size(); j++)
        	{
        		cout<<orignal_node_nos[cycles[i][j]]<<" ,";
        	}
        	cout<<" ) ->colors={ ";
	       	for(int j=0; j<cycles[i].size(); j++)
        	{
        		if(color[cycles[i][j]]==1) cout<<"[b] ,";
        		else cout<<"[r] ,";
        	}
        	cout<<" }"<<endl;
        }
        // for(int i=0; i<parents.size(); i++)
        // {
        // 	if(parents[i]==-1) cout<<orignal_node_nos[i]<<"->-1"<<" ";
        // 	else cout<<orignal_node_nos[i]<<"->"<<orignal_node_nos[parents[i]]<<" ";
        // } 
        return forrest_edges;
    }
    void cycles_void()
    {
		vector<int> parents(n);
        for(int i=0; i<parents.size(); i++) parents[i]=-1;

    	vector< vector<int> > cycles;
    	vector<int> visited(n);
        for(int i = 0; i < this->n; ++i) visited[i]=0;

    	for(int i=0; i<n; i++) 
    	{
    		this->dfs1(i, parents, cycles, visited);
			for(int j=0; j<parents.size(); j++)
			{
				if(parents[j]!=-1)
				{
					parents[j]=-1;
				}
			}
    	}

    	for(int i=0; i<cycles.size(); i++)
        {
        	cout<<"( ";
        	for(int j=0; j<cycles[i].size(); j++)
        	{
        		cout<<cycles[i][j]<<" ,";
        	}
        	cout<<" ) ->colors={ ";
	       	for(int j=0; j<cycles[i].size(); j++)
        	{
        		if(color[cycles[i][j]]==1) cout<<"[b] ,";
        		else cout<<"[r] ,";
        	}
        	cout<<" }"<<endl;
        }
        // for(int i=0; i<parents.size(); i++)
        // {
        // 	if(parents[i]==-1) cout<<i<<"->-1"<<" ";
        // 	else cout<<i<<"->"<<parents[i]<<" ";
        // }
    }

	vector<pair<int,int> > get_two_col_edges()
	{
		vector<pair<int,int> > ans;
		for(int i=0; i<adj.size(); i++)
		{
			for(int j=0; j<adj[i].size(); j++)
			{
				if( (color[adj[i][j]]==0 && color[i]==1) || (color[adj[i][j]]==1 && color[i]==0) )  
				{
					ans.push_back(make_pair(i,adj[i][j]));
				}
			}
		}
		return ans;
	}
};

int main() 
{ 
	int n;
	cin>>n;
	//input graph
	vector<bool> color;
	for(int i=0; i<n; i++) 
	{
		char col;
		cin>>col;
		if(col=='b') color.push_back(1); //blue is 1
		else color.push_back(0);
	}
	vector<pair<int,int> > edges;
	while(1)
	{
		int temp;
		cin>>temp;
		if(temp==-1) break;
		else
		{
			int temp2;
			cin>>temp2;
			edges.push_back(make_pair(temp, temp2));
		}
	}

	//make graph
    graph g(n, color); // Total 5 vertices in graph 
    for(int i=0; i<edges.size(); i++)
    {
    	g.addEdge(edges[i]);
    }
    cout<<"Original Graph: "<<endl;
    g.print(); 
    cout<<endl;

    //make sub-graphs
    graph gr=g.getcolgraph(0);
    graph gb=g.getcolgraph(1);
    
    cout<<"Red Sub-Graph: "<<endl;
    gr.print_mono();
    cout<<endl;
    cout<<"Blue Sub-Graph: "<<endl;
    gb.print_mono();
    cout<<endl;

    cout<<"Cycles for Blue: "<<endl;
    vector<pair<int,int> > blue_forrest_edges=gb.cycles();
    cout<<endl;

    cout<<"Cycles for Red: "<<endl;
    vector<pair<int,int> > red_forrest_edges=gr.cycles();
    cout<<endl;
	vector<pair<int,int> > rb_forrest_edges= g.get_two_col_edges();
    
    // cout<<"Blue forrest_edges edges: "<<endl;
    // for(int i=0; i<blue_forrest_edges.size(); i++) cout<<blue_forrest_edges[i]<<" ";
    // cout<<endl;

    // cout<<"red forrest_edges edges: "<<endl;
    // for(int i=0; i<red_forrest_edges.size(); i++) cout<<red_forrest_edges[i]<<" ";
    // cout<<endl;

    // cout<<"common forrest_edges edges: "<<endl;
    // for(int i=0; i<rb_forrest_edges.size(); i++) cout<<rb_forrest_edges[i]<<" ";
    // cout<<endl;
    
    graph grb(n, color);  
    for(int i=0; i<rb_forrest_edges.size(); i++) grb.addEdge(rb_forrest_edges[i]);
    
    for(int i=0; i<blue_forrest_edges.size(); i++) grb.addEdge(blue_forrest_edges[i]);
    
    for(int i=0; i<red_forrest_edges.size(); i++) grb.addEdge(red_forrest_edges[i]);
 	grb.print();   
	cout<<endl;

    cout<<"Cycles for RB: "<<endl;
	grb.cycles_void();
    return 0; 
} 