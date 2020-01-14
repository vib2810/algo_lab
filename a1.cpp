#include <stdio.h> 
#include <iostream> 
#include <math.h>
using namespace std; 
double lorec(int n);
double hirec(int n);

struct hilo
{
    double hirec;
    double lorec;
};
double lorec(int n)
{
    if(n==0) return 0;
    return hirec(n-1)+lorec(n-1);
}  
double hirec(int n)
{
    if(n==0) return 1;
    return 2*hirec(n-1)+lorec(n-1);
}  
hilo hilorec(int n)
{
    if(n==0)
    {
        hilo temp;
        temp.hirec=1;
        temp.lorec=0;
        return temp;   
    }
    hilo temp_m1=hilorec(n-1);
    hilo temp;
    temp.hirec=2*temp_m1.hirec+temp_m1.lorec;
    temp.lorec= temp_m1.hirec+temp_m1.lorec;
    return temp;
}
hilo hiloformula(int n)
{
    double hirec= (0.1*(5+sqrt(5)))*pow(0.5*(3-sqrt(5)),n+1) + (0.1*(5-sqrt(5)))*pow(0.5*(3+sqrt(5)),n+1);
    double lorec= (0.1*(-5-3*sqrt(5)))*pow(0.5*(3-sqrt(5)),n+1) + (0.1*(-5+3*sqrt(5)))*pow(0.5*(3+sqrt(5)),n+1);
    hilo temp;
    temp.hirec=hirec;
    temp.lorec=lorec;
    return temp;
}
int main() 
{ 
    int n;
    cout<<"Enter n: ";
    cin>>n;

    cout << "Method 0 n=" << n << " hirec: "<< hirec(n) << " lorec: " <<lorec(n)<<endl;

    hilo ans2=hilorec(n);
    cout << "Method 1 n=" << n << " hirec: "<< ans2.hirec << " lorec: " <<ans2.lorec<<endl;   

    hilo ans3=hiloformula(n);
    cout << "Method 2 n=" << n << " hirec: "<< ans3.hirec << " lorec: " <<ans3.lorec<<endl;   

    return 0; 
} 
  
