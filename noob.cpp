#include <stdio.h> 
#include <iostream> 
#include <math.h>
#include<limits.h>
#include <cfloat>
using namespace std;
struct sequences
{
	int n_seq;
	int n_seq_size;
	int **data;
};
int fact(int n)
{
	if(n==0 || n==1) return 1;
	return n*fact(n-1);
}
int ncr(int n, int r)
{
	return fact(n)/(int)(fact(n-r)*fact(r));
}
int countseq(int *data, int n)
{
	if(n<=2) return 1;
	int l=0;
	for(int i=0; i<n; i++) if(data[i]<data[0]) l++;
	int r=n-1-l;
	int *al=new int(l);
	int *ar=new int(r);

	cout<<"Input n= "<<n<<endl;
	cout<<"Data: ";
	for(int i=0; i<n; i++) cout<<data[i]<<" ";
	
	int counter1=0, counter2=0;
	cout<<endl;
	for(int i=1; i<n; i++)
	{
		if(data[i]<data[0])
		{
			al[counter1]=data[i];
			++counter1;
		}
		else if(data[i]>data[0])
		{
			ar[counter2]=data[i];
			++counter2;
		}
		cout<<"counters: "<<counter1<<" "<<counter2<<endl;
	}
	cout<<data[0]<<endl;
	cout<<"l: "<<l<<" ";
	for(int i=0; i<l; i++) cout<<al[i]<<" ";
	cout<<"\nr: "<<r<<" ";
	for(int i=0; i<r; i++) cout<<ar[i]<<" ";
	cout<<endl<<endl;	
	int iso_l=countseq(al, l);
	int iso_r=countseq(ar, r);
	int isodata= iso_l*iso_r*ncr(n-1, l);
	return isodata;
}

// sequence findallseq(int *data, int n)
// {
// 	if(n<=2)
// 	{
// 		sequence ans;
// 		ans.n_seq=1;
// 		ans.n_seq_data=2;
// 		ans.data = new int*()
// 	} 
// }
int main()
{
	int n;
	cin>>n;
	int *data=new int(n);
	for(int i=0; i<n; i++) cin>>data[i];
	
	cout<<"Input n= "<<n<<endl;
	cout<<"Data: ";
	for(int i=0; i<n; i++) cout<<data[i]<<" ";
	cout<<endl;

	int countiso=countseq(data, n);
	cout<<"Sequence count: "<<endl;
	cout<<"Total number of sequences= "<<countiso<<endl;
	return 0;
}