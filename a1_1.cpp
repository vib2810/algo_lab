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
    double hirec=1, lorec=0;
    for(int i=0; i<n; i++)
    {
        double hirec_old=hirec;
        hirec=2*hirec+lorec;
        lorec=hirec_old+lorec;
    }
    hilo temp;
    temp.hirec=hirec;
    temp.lorec=lorec;
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

    cout << "Method 1 n=" << n << " hirec: "<< hirec(n) << " lorec: " <<lorec(n)<<endl;

    hilo ans2=hilorec(n);
    cout << "Method 2 n=" << n << " hirec: "<< ans2.hirec << " lorec: " <<ans2.lorec<<endl;   

    hilo ans3=hiloformula(n);
    cout << "Method 3 n=" << n << " hirec: "<< ans3.hirec << " lorec: " <<ans3.lorec<<endl;   

    return 0; 
} 
  
