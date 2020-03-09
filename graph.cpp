#include<bits/stdc++.h> 
using namespace std; 
  
class graph
{
protected:
    int n; //no of nodes
    vector< vector<double> > adj;
public:
    void addEdge(int u, int v);
    void print()
    { 
        cout<<"No of Nodes: "<<this->n<<endl;
        for (int i=0; i<n; i++) 
        { 
            cout << i<<":"; 
            for (int j=0; j<adj[i].size(); j++) cout << "-> " << adj[i][j]; 
            cout<<endl;
        } 
    } 
    void dfs(int node)
    {
        stack<int> s_dfs;
        bool visited[n];
        for(int i = 0; i < this->n; ++i) visited[i]=false;
        s_dfs.push(node);
        while(s_dfs.empty()==0)
        {
            int next=s_dfs.top();
            s_dfs.pop();
            if(visited[next]==false)
            {
                visited[next]=true;
                cout<<next<<" ";
            }
            for(int i=0; i<adj[next].size(); i++) 
            {
                int child=adj[next][i];
                if(visited[child]==false) s_dfs.push(child);
            }
        }
        cout<<endl;
    }
    void bfs(int node)
    {
        queue<int> q_bfs;
        bool *visited=new bool(this->n);
        for(int i = 0; i < this->n; ++i) visited[i]=false;
        q_bfs.push(node);
        while(q_bfs.empty()==0)
        {
            int next=q_bfs.front();
            q_bfs.pop();
            if(visited[next]==false)
            {
                visited[next]=true;
                cout<<next<<" ";
            }
            for(int i=0; i<adj[next].size(); i++) 
            {
                int child=adj[next][i];
                if(visited[child]==false)  q_bfs.push(child);
            }
        }
        cout<<endl;
    }
};
class graph_undir: public graph
{
public:
    graph_undir(int n)
    {
        this->n=n;
        this->adj.resize(n); 
    }
    void addEdge(int u, int v)
    { 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    } 
};
class graph_dir: public graph
{
public:
    graph_dir(int n)
    {
        this->n=n;
        this->adj.resize(n); 
    }
    void addEdge(int u, int v)
    { 
        adj[u].push_back(v); 
    } 
};

int main() 
{ 
    graph_dir g(4); // Total 5 vertices in graph 
    g.addEdge(0, 1); 
    g.addEdge(0, 2); 
    g.addEdge(1, 2); 
    g.addEdge(2, 0); 
    g.addEdge(2, 3); 
    g.addEdge(3, 3); 
    g.dfs(0);
    g.bfs(2);
    g.print(); 
    return 0; 
} 