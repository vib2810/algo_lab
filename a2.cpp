#include <stdio.h> 
#include <iostream> 
#include <math.h>
#include<string>
using namespace std; 

//a structure array of strings, along with no of strings that are there. findallexpr will return this structure
struct stringstr
{
    int no_of_1;
    string data;
};
struct strarr
{
    int no_of_strings;
    stringstr* data;
};

//a function to add a string to a strarr structure
void add_str(stringstr data, strarr &prev)
{
    stringstr *next=new stringstr[prev.no_of_strings+1];
    int flag=0;
    for(int i=0; i<prev.no_of_strings; i++)
    {
        next[i].no_of_1=prev.data[i].no_of_1;
        next[i].data=prev.data[i].data;
        if(prev.data[i].data==data.data) flag=1;  
    }
    if(flag==0)
    {
        next[prev.no_of_strings].data=data.data;
        next[prev.no_of_strings].no_of_1=data.no_of_1;

        prev.no_of_strings=prev.no_of_strings+1;
        prev.data=next;
        return;
    } 
    if(flag==1)
    {
        return;
    }  
}
void printstrarr(strarr data)
{
    for(int i=0; i<data.no_of_strings; i++) 
    {
        cout<<"1s:"<< data.data[i].no_of_1<<" Size: "<< data.data[i].data.size() <<" "<< data.data[i].data<<endl;
    }
    cout<<"No of Strings: "<<data.no_of_strings<<endl;
    return;
}
int checkbrac(string a)
{
    if((a[0]=='(') && a[a.size()-1]==')') return 1;
    return -1;
}
strarr findallexpr(int n)
{
    if(n==1)
    { 
        stringstr *str_temp=new stringstr[1];
        str_temp[0].data="1";        
        str_temp[0].no_of_1=1;

        strarr temp;
        temp.no_of_strings=1;
        temp.data=str_temp;
        return temp;
    }
    
    strarr strans; 
    strans.no_of_strings=0;
    //addition
    for(int i=1; i<n; i++)
    {
        int j=n-i;
        if(j<i) break;
        //iterate for all sub_strings of i and j
        else 
        {   
            // cout<<i<<" "<<j<<endl;
            strarr id=findallexpr(i);
            strarr jd=findallexpr(j);
            for(int i=0; i<id.no_of_strings; i++)
            {
                for(int j=0; j< jd.no_of_strings; j++)
                {
                    stringstr s1=id.data[i];
                    stringstr s2=jd.data[j];
                    stringstr concat;
                    concat.data=s1.data+"+"+s2.data;
                    concat.no_of_1=s1.no_of_1+s2.no_of_1;
                    add_str(concat, strans);  
                }
            }
        } 
    }
    //multiplication
    for(int i=2; i<n; i++)
    {
        int j=n/i;
        if(j<i) break;
        if(j*i==n)
        {
            // cout<<i<<" "<<j<<endl;
            strarr id=findallexpr(i);
            strarr jd=findallexpr(j);
            for(int i=0; i<id.no_of_strings; i++)
            {
                for(int j=0; j< jd.no_of_strings; j++)
                {
                    stringstr s1=id.data[i];
                    stringstr s2=jd.data[j];
                    stringstr concat;
                    concat.no_of_1=s1.no_of_1+s2.no_of_1;
                    if(checkbrac(s1.data)==-1 && checkbrac(s2.data)==-1)
                    {
                        concat.data="("+s1.data+")x("+s2.data+")";
                    }
                    if(checkbrac(s1.data)==-1 && checkbrac(s2.data)==1)
                    {
                        concat.data="("+s1.data+")x"+s2.data;
                    }
                    if(checkbrac(s1.data)==1 && checkbrac(s2.data)==-1)
                    {
                        concat.data=s1.data+"x("+s2.data+")";
                    }
                    if(checkbrac(s1.data)==1 && checkbrac(s2.data)==1)
                    {
                        concat.data=s1.data+"x"+s2.data;
                    }
                    add_str(concat, strans);
                }
            }
        } 
    }
    return strans;
}
strarr swap(int i, int j, strarr input)
{
    // cout<<i<<"swapping"<<j<<endl;
    stringstr temp;
    //store j
    temp.data=input.data[j].data;
    temp.no_of_1=input.data[j].no_of_1;
    //j=i
    input.data[j].data= input.data[i].data;
    input.data[j].no_of_1= input.data[i].no_of_1;
    //i=temp
    input.data[i].data= temp.data;
    input.data[i].no_of_1= temp.no_of_1;
    return input;
}
strarr sortstrarr(strarr input)
{
    for(int i=0; i<input.no_of_strings; i++)
    {
        for(int j=i; j<input.no_of_strings; j++)
        {
            int ni=input.data[i].no_of_1, nj=input.data[j].no_of_1;
            if(ni < nj) input=swap(i, j, input);
            if(ni==nj)
            {
                int li=input.data[i].data.size(), lj=input.data[j].data.size();
                if(li<lj) input=swap(i, j, input);
            }
        }
    }
    return input;
}
int main() 
{ 
    int n;
    cout<<"Enter n: ";
    cin>>n;

    strarr ans=findallexpr(n); 
    cout<<"Before Sorting: "<<endl;
    printstrarr(ans);

    ans=sortstrarr(ans);
    cout<<"\nAfter Sorting: "<<endl;
    printstrarr(ans);

    return 0; 
} 