#include<bits/stdc++.h> 
#define INF 1e7
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
struct edge_info
{
    int i,j;
    char airline;
    int cost;
};
edge_info make_edge_info(char airline, int cost)
{
    edge_info ans;
    ans.airline=airline;
    ans.cost=cost;
    return ans;
}
class graph
{
public:
    int n; //no of nodes
    vector< vector<edge_info> > adj; //adjacency list    

public:
    graph(){};
    graph(int n)
    {
        this->n=n;
        
        //resize adjacency matrix
        this->adj.resize(n);
        // vector < edge_info > aa(n);
        for(int i=0; i<n; i++)
        {
            vector<edge_info> temp(n);
            adj[i] = temp; 
        }
        
        assert(adj.size()==n);
        assert(adj[0].size()==n);

        //Initialize adjacency matrix
        for(int i=0; i<adj.size(); i++)
        {
            for(int j=0; j<adj[i].size(); j++)
            {
                if(i==j)
                {
                    adj[i][j].airline='s';
                    adj[i][j].cost=0;
                }
                else 
                {
                    adj[i][j].airline='-';
                    adj[i][j].cost=INF;
                }
            }
        }
    }
    void addEdge(int i, int j, int cij, char aij)
    { 
        if(i==j) return;
        adj[i][j].cost = cij;
        adj[i][j].airline=aij;
    }
    void removeEdge(int i, int j, int cij, char aij)
    { 
        if(i==j) 
        {
            adj[i][j].airline='s';
            adj[i][j].cost = 0;
            return;
        }
        adj[i][j].airline='-';
        adj[i][j].cost = INF;
    } 
 
    void print()
    {
        cout<<"No of nodes: "<<n<<endl;
        for(int i=0; i<adj.size(); i++)
        {
            cout <<i<<"-> "; 
            for(int j=0; j<adj[i].size(); j++)
            {
                if(adj[i][j].airline == 'a' || adj[i][j].airline == 'n')
                {
                    cout<<j<<"("<<adj[i][j].cost<<","<<adj[i][j].airline<<") ";
                }
            }
            cout<<endl;
        }
    }
    vector<edge_info> get_ai_egdes()
    {
        vector<edge_info> ans;
        for(int i=0; i<adj.size(); i++)
        {
            for(int j=0; j<adj[i].size(); j++)
            {
                if(adj[i][j].airline == 'a')
                {
                    edge_info temp;
                    temp.i=i, temp.j=j;
                    temp.cost = adj[i][j].cost;
                    temp.airline = adj[i][j].airline;
                    ans.push_back(temp);
                }
            }
        }
        return ans;
    }
    vector<edge_info> get_non_ai_egdes()
    {
        vector<edge_info> ans;
        for(int i=0; i<adj.size(); i++)
        {
            for(int j=0; j<adj[i].size(); j++)
            {
                if(adj[i][j].airline == 'n')
                {
                    edge_info temp;
                    temp.i=i, temp.j=j;
                    temp.cost = adj[i][j].cost;
                    temp.airline = adj[i][j].airline;
                    ans.push_back(temp);
                }
            }
        }
        return ans;
    }
    vector< vector<int> > floydWarshall()  
    {  
        vector< vector<int> > dist(n);
        for(int i=0; i<n; i++) 
        {
            vector<int> temp(n);
            dist[i]=temp;
        }
        
        //Initialize the solution matrix same as input graph matrix. 
        for (int i = 0; i < adj.size(); i++)  
        {
            for (int j = 0; j < adj[i].size(); j++)  
            {
                dist[i][j] = adj[i][j].cost;
            }  
        }

        //Build the sub-optimal solutions k
        for (int k = 0; k < n; k++)  
        {    
            for (int i = 0; i < n; i++)  
            {  
                for (int j = 0; j < n; j++)  
                {  
                    if (dist[i][k] + dist[k][j] < dist[i][j])  dist[i][j] = dist[i][k] + dist[k][j];  
                }  
            }  
        }  
        return dist; 
    }

    vector< vector<int> > get_shortest_distances()
    {
        vector< vector<int> > ans;
        for(int i=0; i<n; i++)
        {
            ans.push_back(dijkstra(i));
        }   
        return ans;
    }   
    int minDistance(vector<int> dist, bool closed[]) 
    { 
        // Initialize min value 
        int min = INF, min_index=-1; 
        for (int v = 0; v < n; v++) 
        {
            if (closed[v] == false && dist[v] <= min) 
                min = dist[v], min_index = v; 
        }
        return min_index; 
    } 
    vector<int> dijkstra(int src) 
    { 
        vector<int> dist(n); 
        bool closed[n]; 
        
        // Initialize all distances as INFINITE and closed[] as false 
        for (int i = 0; i < n; i++) dist[i] = INF, closed[i] = false; 
      

        dist[src] = 0; 
      
        // Find shortest path for all vertices 
        for (int count = 0; count < n - 1; count++) { 
            // Pick the minimum distance vertex from the set of vertices not in closed se
            int u = minDistance(dist, closed); 
            // Add u to closed set 
            closed[u] = true; 

            // Update distance values of vertices adjacent to u 
            for (int v = 0; v < n; v++) 
      
                // Update dist[v] only if its not in closed 
                // AND there is an edge from u to v  
                // AND new dist from src to v through u is smaller than dist[v] 
                if (!closed[v] && (adj[u][v].airline=='a' || adj[u][v].airline=='n') && dist[u] != INT_MAX && dist[u] + adj[u][v].cost < dist[v]) 
                    dist[v] = dist[u] + adj[u][v].cost; 
        } 
        return dist;
    } 
};  

vector< vector<int> > get_chart2(vector<edge_info> non_ai_edges, vector< vector<int> > chart1)
{
    vector< vector<int> > dist(chart1.size());
    for(int i=0; i<chart1.size(); i++) 
    {
        vector<int> temp(chart1.size());
        dist[i]=temp;
    }
    for(int i=0; i<chart1.size(); i++)
    {
        for(int j=0; j<chart1[i].size(); j++)
        {
            if(chart1[i][j]!=INF)
            {
                dist[i][j]=chart1[i][j];
                continue;
            }

            int min=INF;
            //minimize cost of i,j over all non_ai_edges
            for(int m=0; m<non_ai_edges.size(); m++)
            {
                int k=non_ai_edges[m].i;
                int l=non_ai_edges[m].j;

                int cost= chart1[i][k] + non_ai_edges[m].cost + chart1[l][j];
                if(cost<INF)
                {
                    if(cost<min)
                    {
                        min=cost;
                    }
                }
            }
            dist[i][j]=min;
        }
    }
    return dist;
} 

vector< vector<int> > get_chart3(vector< vector<int> > shortest_distances, vector< vector<int> > chart1)
{
    vector< vector<int> > dist(chart1.size());
    for(int i=0; i<chart1.size(); i++) 
    {
        vector<int> temp(chart1.size());
        dist[i]=temp;
    }

    for(int i=0; i<chart1.size(); i++)
    {
        for(int j=0; j<chart1[i].size(); j++)
        {
            if(chart1[i][j]!=INF)
            {
                dist[i][j]=chart1[i][j];
                continue;
            }
            //else
            dist[i][j]=shortest_distances[i][j];
        }
    }
    return dist;
} 

void print_chart(vector< vector<int> > input)
{
    cout<<"   ";
    for(int i=0; i<input.size(); i++)
    {
        cout<<"\t"<<i;
    }
    cout<<endl;
    for(int i=0; i<input.size(); i++)
    {
        cout<<i<<"->";
        for(int j=0; j<input[i].size(); j++)
        {
            if(input[i][j]==INF) cout<<"\t-";
            else cout<<"\t"<<input[i][j];
        }
        cout<<endl;
    }
}
int main() 
{ 
    int n;
    cin>>n;

    //input graph
    graph g(n);
    while(1)
    {
        int i;
        cin>>i;
        if(i==-1) break;
        else
        {
            int j, cij;
            char aij;
            cin>>j>>cij>>aij;
            g.addEdge(i,j,cij, aij);
        }
    }

    //Original graph
    cout<<"Original Graph: "<<endl;
    g.print();
    
    //Get AI Sub Graph
    graph g_ai(n);
    vector<edge_info> ai_edges= g.get_ai_egdes();
    for(int i=0; i<ai_edges.size(); i++)
    {
        g_ai.addEdge(ai_edges[i].i, ai_edges[i].j, ai_edges[i].cost, ai_edges[i].airline);
    }
    cout<<"\nAI sub-graph: "<<endl;
    g_ai.print();

    //Chart 1
    //chart1[i][j] -> cheapest price going from i to j using ONLY AI
    vector< vector<int> > chart1= g_ai.floydWarshall();
    cout<<"\nCheapest AI Prices: "<<endl;
    print_chart(chart1);

    //Chart 2
    vector<edge_info> non_ai_edges= g.get_non_ai_egdes();
    vector< vector<int> > chart2= get_chart2(non_ai_edges, chart1);
    cout<<"\nCheapest prices with at most one non-AI leg: "<<endl;
    print_chart(chart2);

    //Chart 3
    vector< vector<int> > shortest_distances=g.get_shortest_distances();
    vector< vector<int> > chart3= get_chart3(shortest_distances, chart1);
    cout<<"\nCheapest prices with any number of non-AI leg: "<<endl;
    print_chart(chart3);
    return 0; 
} 