#include <stdio.h> 
#include <iostream> 
#include <math.h>
#include<string>
#include<limits>
#include<stack>
#include <cfloat>
using namespace std;
int fac2(int input)
{
	int count=0;
	if(input%2!=0) return -1;
	if(input<=0) return -1;
	while(1)
	{
		input=input/2;
		count++;
		if(input==1 || input%2!=0) break;
	}
	return count;
}
void greedy1(int input)
{
	//even number divide
	//odd number subtract
	int temp=input;
	int count=0;
	cout<<"Method 1"<<endl;
	cout<<"Start    : "<<input<<endl;;
	while(1)
	{
		if(input==1) break;
		if(input%2==0) 
		{
			input=input/2;
			cout<<"Divide   : "<<input<<endl;
		}
		else 
		{
			input--;
			cout<<"Decrement: "<<input<<endl;
		}
		count++;
	}
	cout<<"Number of operations= " <<count<<"\n"<<endl;
}
void greedy2(int input)
{

	int temp=input;
	int count=0;
	cout<<"Method 2"<<endl;
	cout<<"Start    : "<<input<<endl;;
	while(1)
	{
		if(input==1) break;
		if(input%2==0)
		{
			input=input/2;
			cout<<"Divide   : "<<input<<endl;	
			count++;
			continue;
		} 
		int inc2=fac2(input+1), dec2=fac2(input-1);
		if(input==3)
		{
			input--;
			cout<<"Decrement: "<<input<<endl;
			count++;
			continue;
		}
		if(inc2<dec2) 
		{
			input--;
			cout<<"Decrement: "<<input<<endl;
			count++;
			continue;
		}
		else 
		{
			input++;
			cout<<"Increment: "<<input<<endl;
			count++;
			continue;
		}
	}
	cout<<"Number of operations= " <<count<<"\n"<<endl;
}
void greedy3(int input, int k, int *a)
{
	int temp=input;
	int count=0;
	cout<<"Method 3"<<endl;
	cout<<"Start    : "<<input<<endl;;
	while(1)
	{
		if(input==1) break;
		if(input%2==0) 
		{
			input=input/2;
			cout<<"Divide   : "<<input<<endl;
			count++;
			continue;
		}
		if(input==3)
		{
			input--;
			cout<<"Decrement: "<<input<<endl;
			count++;
			continue;
		}
		int max2=-1; //store in max2 the action with max 2 factors
		for(int i=0; i<k; i++)
		{
			if(input+a[i]<=0) continue;
			int tempfac2=fac2(input+a[i]);
			if(tempfac2>max2) max2=a[i]; 
			if(tempfac2==fac2(max2)) //tie between current and previous best 
			{
				if(input+a[i] < max2) max2=input+a[i]; 
			}

		}
		input=input+max2;
		cout<<"Add "<<max2<<"   : "<<input<<endl;
		count++;
		// int aa;
		// scanf("%d", &aa);
	}
	cout<<"Number of operations= " <<count<<"\n"<<endl;
}
int pow2(int input)
{
	int count=0;
	if(input==1) return 0;
	if(input%2!=0) return -1;
	while(1)
	{
		count++;
		input=input/2;
		if(input==1) return count;
		if(input%2!=0) return -1;
	} 
}
int *data;
struct ret
{
	int optimal;
	int depth;
};
int get_optimal(int input, int k, int *a, int max)
{
	cout<<"input: "<<input<<endl;
	int aa;
	cin>>aa;
	for(int i=0; i<max; i++) cout<<data[i]<<" ";
	cout<<endl;		
	if(input>max) return 9999;
	if(pow2(input)>0)
	{
		int ans=pow2(input);
		data[input]=ans;
		cout<<"returning default: "<<ans<<endl;
		return ans;
	}
	if(input%2==0) //even
	{
		cout<<"even"<<endl;
		//get min
		int min=99999999;
		for(int i=0; i<k; i++)
		{
			int optimal;
			if(data[input+a[i]]>0) optimal=data[input+a[i]];
			else
			{
				optimal=get_optimal(input+a[i], k, a, max);
				data[input+a[i]]=optimal;
			} 
			if(optimal<min) min=optimal;
		}
		int optimal_div=get_optimal(input/2, k, a, max);
		if(optimal_div<min) min=optimal_div;
		cout<<"returning"<<endl;
		return 1+min;
	}
	else 
	{
		cout<<"odd"<<endl;
		int min=99999999;
		for(int i=0; i<k; i++)
		{
			int optimal;
			if(data[input+a[i]]>0) optimal=data[input+a[i]];
			else
			{
				optimal=get_optimal(input+a[i], k, a, max);
				data[input+a[i]]=optimal;
			} 
			if(optimal<min) min=optimal;
		}
		cout<<"returning"<<endl;
		return 1+min;
	}
}
int optimal(int input, int k, int *a) 
{
	int itr=log(input)/log(2);
	int max=-99999;
	for(int i=0; i<k; i++) if(a[i]>max) max=a[i];
	max=max+input;
	cout<<"Max=" <<max<<endl;;
	data=new int[max]; 
	for(int i=0; i<max; i++) data[i]=-1;
	return get_optimal(input, k, a, max);
}
int main() 
{ 
	int input;
	cout<<"Enter Number: ";
	cin>>input;
	// greedy1(input);
	// greedy2(input);
	
	cout<<"Enter k:";
	int k;
	cin>>k;
	int a[k];
	for(int i=0; i<k; i++) cin>>a[i];
	// greedy3(input, k, a);
	cout<<"Optimal Soln: "<<optimal(input, k, a)<<endl;
}