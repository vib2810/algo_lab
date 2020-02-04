#include <stdio.h> 
#include <iostream> 
#include <math.h>
#include<string>
#include<limits.h>
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
int greedy3p(int input, int k, int *a)
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
		int max2=a[0]; //store in max2 the action with max 2 factors(subset of k)
		for(int i=0; i<k; i++)
		{
			if(input+a[i]<=0) continue;
			int tempfac2=fac2(input+a[i]);
			if(tempfac2>fac2(input+max2)) max2=a[i]; 
			// if(input==613) cout<<input<<" "<<a[i]<<" "<<tempfac2<<endl;
			if(tempfac2==fac2(input+max2)) //tie between current and previous best 
			{
				// if(input==613)
				// {
				// 	cout<<"tie between "<< max2<< " "<< a[i]<<endl;
				// }
				if(input+a[i] < input+max2) max2=a[i]; 
				// if(input+a[i] < max2) max2=input+a[i]; 
			}

		}
		input=input+max2;
		cout<<"Add "<<max2<<"   : "<<input<<endl;
		count++;
		// int aa;
		// scanf("%d", &aa);
	}
	cout<<"Number of operations= " <<count<<"\n"<<endl;
	return count;
}
int greedy3(int input, int k, int *a)
{
	int temp=input;
	int count=0;
	while(1)
	{
		if(input==1) break;
		if(input%2==0) 
		{
			input=input/2;
			count++;
			continue;
		}
		if(input==3)
		{
			input--;
			count++;
			continue;
		}
		int max2=a[0]; //store in max2 the action with max 2 factors(subset of k)
		for(int i=0; i<k; i++)
		{
			if(input+a[i]<=0) continue;
			int tempfac2=fac2(input+a[i]);
			if(tempfac2>fac2(input+max2)) max2=a[i]; 
			if(tempfac2==fac2(input+max2)) //tie between current and previous best 
			{
				if(input+a[i] < input+max2) max2=a[i]; 
			}

		}
		input=input+max2;
		count++;
	}
	return count;
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

int optimal(int input, int k, int *a) 
{
	int itr=log(input)/log(2);
	int max=-99999;
	for(int i=0; i<k; i++) if(a[i]>max) max=a[i];
	max=max+input;
	cout<<"Max=" <<max<<endl;;
	int *data=new int[max];
	for(int i=1; i<max; i++)
	{
		data[i]=greedy3(i, k, a);
	} 
	for(int i=0; i<itr; i++)
	{
		cout<<i<<endl;
		for(int j=1; j<max; j++) //iteration over max
		{
			int temp=INT_MAX;
			for(int l=0; l<k; l++)
			{
				if(j+a[l]>=max) continue;
				if(j+a[l]<1) continue;
				if(data[j+a[l]]<temp) temp=data[j+a[l]];
			}
			if(j%2==0)
			{
				if(temp>data[j/2]) temp=data[j/2];
			}
			temp=1+temp;
			if(data[j]>temp) data[j]=temp;
		}
	}
	return data[input];
}

int main() 
{ 
	int input;
	cout<<"Enter Number: ";
	cin>>input;
	greedy1(input);
	greedy2(input);
	
	cout<<"Enter k:";
	int k;
	cin>>k;
	int a[k];
	for(int i=0; i<k; i++) cin>>a[i];
	greedy3p(input, k, a);
	cout<<"Optimal Soln: "<<optimal(input, k, a)<<endl;
}