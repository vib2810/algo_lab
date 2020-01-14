#include <stdio.h> 
#include <iostream> 
#include <math.h>
using namespace std; 
void decToBinary(int no, int n, int* binaryNum) 
{ 
    for(int i=0; i<n; i++)
    {
        binaryNum[n-i-1]=no%2;
        no=no/2;
    }
} 
int count1(int data[], int n)
{
    int count=0;
    for(int i=0; i<n; i++) 
    {
        if (data[i]==1) count++;
    }
    return count;
}
int ret_int(int data[], int n, int match)
{
    for(int i=0; i<n; i++) 
    {
        if (data[i]==match) 
        {
            return i;
        }
    }
}
bool check_desc(int data[], int n)
{
    int flag=1;
    int prev, itr=0;
    for(int i=0; i<n; i++)
    {
        if(data[i]!=0)
        {
            if(itr==0)
            {
                prev=data[i];
                itr++;
                continue;  
            } 
            if((prev<data[i])) 
            {
                flag=0;
                break;
            }
            prev=data[i];
        }
    }
    if(flag==0) return false;
    else return true;
}
bool m0(int data[], int n)
{
    int flag=1;
    int itr_count= n*(n-1)*(n-2)/6;
    int num=pow(2, n+1);
    int comb_num=0;
    
    //get all combinations of 3 nos between 1 to n
    for(int i=0; i<num; i++)
    {
        int binaryNum[n];
        decToBinary(i,n,binaryNum);
        int count=count1(binaryNum,n);
        if(count==3)
        {
            // for(int i=0; i<n; i++)
            // {
            //     cout<<binaryNum[i];
            // }
            int nos[3]; 
            int int_count=0;
            for(int i=0; i<n; i++)
            {
                if(binaryNum[i]==1) 
                {
                    nos[int_count]=i+1;
                    int_count++;
                }
            }
            // for(int i=0; i<3; i++) cout<<nos[i]<<" ";
            // cout<<"\n";
            comb_num++;
            int j=ret_int(data, n, nos[0]);
            int k=ret_int(data, n, nos[1]);
            int i=ret_int(data, n, nos[2]);
            // cout<< "i: "<<i<<"j: "<<j<<"k: "<<k<<endl;
            if((i<j && j<k)) 
            {
                flag=0;
                break;
            } 
        }
    }
    // cout<<"comb_num: "<<comb_num<<endl;
    if(flag==0) return false;
    else return true;

}
bool m1(int data[], int n)
{
    int flag=1;
    int itr_count= n*(n-1)*(n-2)/6;
    int num=pow(2, n+1);
    int comb_num=0;
    
    //get all combinations of 3 nos between 1 to n
    for(int i=0; i<num; i++)
    {
        int binaryNum[n];
        decToBinary(i,n,binaryNum);
        int count=count1(binaryNum,n);
        if(count==3)
        {
            int nos[3]; 
            int int_count=0;
            for(int i=0; i<n; i++)
            {
                if(binaryNum[i]==1) 
                {
                    nos[int_count]=i;
                    int_count++;
                }
            }
            comb_num++;
            int i=nos[0];
            int j=nos[1];
            int k=nos[2];
            int c=data[i], a=data[j], b=data[k];
            if((a<b && b<c)) 
            {
                flag=0;
                break;
            } 
        }
    }
    // cout<<"comb_num: "<<comb_num<<endl;
    if(flag==0) return false;
    else return true;

}
bool m2(int data[], int n)
{
    int flag=1;
    for(int i=0; i<n;i++)
    {
        int c=data[i];
        int temp[n];
        for (int k = 0; k < n; ++k) temp[k]=0;

        for(int j=i+1; j<n; j++)
        {
            if(data[j]<c) temp[j]=data[j];
        }

        int prev, itr=0;
        for(int k=0; k<n; k++)
        {
            if(temp[k]!=0)
            {
                if(itr==0)
                {
                    prev=data[k];
                    itr++;
                    continue;  
                } 
                if((prev<data[k])) 
                {
                    flag=0;
                    break;
                }
                prev=data[k];
            }
        }

    }
    if(flag==0) return false;
    else return true;
}
bool m4(int data[], int n)
{
    int flag=1;

    if(flag==0) return false;
    else return true;
}
int main() 
{ 
    int n=25;
    cout<<"Enter n:";
    cin>>n;
    int data[n];
    cout<<"Enter the array: ";
    for(int i=0; i<n; i++)
    {
        cin>>data[i];
    }
    for(int i=0; i<n; i++) 
    {
        cout<<data[i]<<" ";
    }
    cout<<"\n";
    bool ans0=m0(data, n);
    if(ans0==false) cout<<"Method 0: Not Algolicious"<<endl;
    else cout<<"Method 0: Algolicious"<<endl;

    bool ans1=m1(data, n);
    if(ans1==false) cout<<"Method 1: Not Algolicious"<<endl;
    else cout<<"Method 1: Algolicious"<<endl;

    bool ans2=m2(data, n);
    if(ans2==false) cout<<"Method 2: Not Algolicious"<<endl;
    else cout<<"Method 2: Algolicious"<<endl;

    return 0; 
} 
  
