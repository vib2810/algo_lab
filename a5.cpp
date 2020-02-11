#include <stdio.h> 
#include <iostream> 
#include <math.h>
#include<float.h>

using namespace std;
//m is no of machines you are buying 
double calc_e(double m, double s, double t, double p) //calculates profit
{
	return (1-pow(p,m))*s + pow(p,m)*t;
}
struct optimal
{
	int n;
	double val_opt;
	int *mi_opt=NULL;
	double *profit=NULL;
	int *c=NULL;
	bool *r=NULL;
};
void print_opt(optimal data)
{
	// cout<<"Optimal value: "<<data.val_opt<<endl;
	// cout<<"Optimal m_i: ";
	float profit_sum=0, cost_sum=0;
	if(data.mi_opt!=NULL)
	{
		for(int i=0; i<data.n; i++)
		{
			cost_sum+=data.mi_opt[i]*data.c[i];
			profit_sum+=data.profit[i];
			cout<<"Machine "<<i<<": "<<data.mi_opt[i]<<" copies, cost= "<<data.mi_opt[i]*data.c[i]<<" Profit: "<<data.profit[i];
			if(data.r!=NULL)
			{
				if(data.r[i]==true) cout<<" [Need maintanance]"<<endl;
				else cout<<" [No maintanance]"<<endl ;
				continue;
			}
			cout<<endl;	
		}
	}
	cout<<"Total buying cost ="<<cost_sum<<endl;
	cout<<"Expected total profit ="<< data.val_opt<<endl;
}
optimal optimalbuy1(int n, int tot, int* c, double* s, double* t, double* p)
{
	double **dp=new double*[n];
	for(int i=0; i<n; i++) dp[i]=new double[tot+1];
	int **m_opt=new int*[n];
	for(int i=0; i<n; i++) m_opt[i]=new int[tot+1];
	//initialize 
	dp[0][0]=0;
	for(int j=0; j<tot+1; j++)
	{
		if(j<c[0]) dp[0][j]=FLT_MIN;
		else
		{
			dp[0][j]= calc_e(j/c[0], s[0], t[0], p[0]);
			m_opt[0][j]= j/c[0];
		}
	}
	for (int i=1; i<n; ++i)
	{
		for(int j=0; j<tot+1; j++)
		{
			// cout<<"Outer i: "<<i<<"j: "<<j<<endl;
			if(j<c[i]) dp[i][j]=FLT_MIN;
			else
			{
				int mi=j/c[i];
				int mi_opt=1;
				double val_max=-1;
				for(int k=1; k<mi; k++) //k tries values for mi
				{
					// cout<<"index check: "<<(j-k*c[i])<<" "<<(double)(dp[i-1][j-k*c[i]])<<endl;
					double value=dp[i-1][j-k*c[i]]+calc_e(k, s[i], t[i], p[i]);
					if(value>val_max) 
					{
						val_max=value;
						mi_opt=k;
					}
				}
				dp[i][j]=val_max;
				m_opt[i][j]= mi_opt;
				// cout<<val_max<<endl;
			}
		}
	}
	optimal ans;
	ans.n=n;
	ans.val_opt=dp[n-1][tot];
	ans.mi_opt=new int[n];
	ans.profit=new double[n];
	ans.c=c;
	int temp=tot;
	for(int i=n-1; i>-1; i--)
	{
		ans.mi_opt[i]=m_opt[i][tot];
		tot=tot-c[i]*ans.mi_opt[i];
	}
	for(int i=0; i<n; i++) 
	{
		ans.profit[i]=calc_e(ans.mi_opt[i], s[i], t[i], p[i]);
	}
	return ans;
}
optimal optimalbuy2(int n, int tot, int* c, double* s, double* r, double* t, double* p, double* q)
{
	double **dp=new double*[n];
	for(int i=0; i<n; i++) dp[i]=new double[tot+1];
	int **m_opt=new int*[n];
	for(int i=0; i<n; i++) m_opt[i]=new int[tot+1];
	bool **r_opt=new bool*[n];
	for(int i=0; i<n; i++) r_opt[i]=new bool[tot+1];
	//initialize 
	dp[0][0]=0;
	for(int j=0; j<tot+1; j++)
	{
		if(j<c[0]) dp[0][j]=FLT_MIN;
		else
		{
			m_opt[0][j]= j/c[0];
			//2 cases with and without maintanance
			double profit1=calc_e(j/c[0], s[0], t[0], p[0]);
			double profit2=calc_e(j/c[0], s[0], t[0], q[0])-m_opt[0][j]*r[0];
			if(profit1>profit2)
			{
				dp[0][j]=profit1; 
				r_opt[0][j]=false;
			}
			else
			{
				dp[0][j]=profit2; 
				r_opt[0][j]=true;
			}
		}
	}
	for (int i=1; i<n; ++i)
	{
		for(int j=0; j<tot+1; j++)
		{
			if(j<c[i]) dp[i][j]=FLT_MIN;
			else
			{
				int mi=j/c[i];
				int mi_opt=1, mi_opt_m=1;
				double val_max=-1, val_max_m=-1;
				
				for(int k=1; k<mi; k++) //k tries values for mi
				{
					//dp[i-1][j-k*c[i]] is profit 
					//k*c[i] cost of buying k machines of type i
					//with no maintanance
					double value=dp[i-1][j-k*c[i]]+calc_e(k, s[i], t[i], p[i]);
					if(value>val_max) 
					{
						val_max=value;
						mi_opt=k;
					}
					//with maintanance
					double value_m=dp[i-1][j-k*c[i]]+(calc_e(k, s[i], t[i], q[i])-k*r[i]);
					if(value_m>val_max_m) 
					{
						val_max_m=value_m;
						mi_opt_m=k;
					}
				}
				
				if(val_max>val_max_m)
				{
					dp[i][j]=val_max;
					m_opt[i][j]= mi_opt;
					r_opt[i][j]=false;
				}
				else
				{
					dp[i][j]=val_max_m;
					m_opt[i][j]= mi_opt_m;
					r_opt[i][j]=true;
				}
			}
		}
	}
	optimal ans;
	ans.n=n;
	ans.val_opt=dp[n-1][tot];
	ans.mi_opt=new int[n];
	ans.profit=new double[n];
	ans.r=new bool[n];
	ans.c=c;

	int temp=tot;
	for(int i=n-1; i>-1; i--)
	{
		ans.mi_opt[i]=m_opt[i][tot];
		ans.r[i]=r_opt[i][tot];
		tot=tot-c[i]*ans.mi_opt[i];
	}
	for(int i=0; i<n; i++) 
	{
		if(ans.r[i]==false) ans.profit[i]=calc_e(ans.mi_opt[i], s[i], t[i], p[i]);
		if(ans.r[i]==true) ans.profit[i]=calc_e(ans.mi_opt[i], s[i], t[i], q[i])-ans.mi_opt[i]*r[i];
	}
	return ans;
}
int main() 
{ 
	int n, tot; 
	cout<<"n: ";
	cin>>n;
	int *c= new int[n]; 
	double *s=new double[n];
	double *r=new double[n];
	double *p=new double[n];
	double *q=new double[n];
	double *t=new double[n];
	
	cout<<"\nCapital: ";
	cin>>tot;
	cout<<"\nc_i: ";
	for(int i=0; i<n; i++) { cin>>c[i]; }
	for(int i=0; i<n; i++) cout<<c[i]<<" ";
	
	cout<<"\ns_i: ";
	for(int i=0; i<n; i++) { cin>>s[i]; }
	for(int i=0; i<n; i++) cout<<s[i]<<" ";
	
	cout<<"\nt_i: ";
	for(int i=0; i<n; i++) { cin>>t[i]; }
	for(int i=0; i<n; i++) cout<<t[i]<<" ";
	
	cout<<"\nr_i: ";
	for(int i=0; i<n; i++) { cin>>r[i]; }
	for(int i=0; i<n; i++) cout<<r[i]<<" ";
	
	cout<<"\np_i: ";
	for(int i=0; i<n; i++) { cin>>p[i]; }
	for(int i=0; i<n; i++) cout<<p[i]<<" ";
	
	cout<<"\nq_i: ";
	for(int i=0; i<n; i++) { cin>>q[i]; }
	for(int i=0; i<n; i++) cout<<q[i]<<" ";

	cout<<"\n----------------Optimal 1----------------"<<endl;
	optimal ans1=optimalbuy1(n, tot, c, s, t, p);
	print_opt(ans1);

	cout<<"\n----------------Optimal 2----------------"<<endl;
	optimal ans2=optimalbuy2(n, tot, c, s, r, t, p, q);
	print_opt(ans2);
}