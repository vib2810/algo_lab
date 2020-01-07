#include <stdio.h> 
#include <iostream> 
using namespace std; 
  
class Node { 
public: 
    int data; 
    Node* right;
    Node* down; 
}; 

void printl(Node *head)
{
    int count=0;
    Node *itr=head;
    while(itr!=NULL)
    {
        count++;
        if(itr->data<10) cout<<" ";
        if(itr->data==0) cout<<" "<<" "; 
        else cout<<itr->data<<" ";
        itr=itr->right;
        if(count==7) 
        {
            cout<<"   ";
            count=0;
        }
    }
    cout<<"\n";
}
void printm(Node *head)
{
    int count=0;
    int count2=1;
    Node* itr1=head;
    cout<<"      January                  February                 March  "<<endl;
    while(itr1!=NULL)
    {
        count++;
        printl(itr1);
        itr1=itr1->down;
        if(count==5) 
        {
            count2++; 
            cout<<"\n" <<endl;
            if(count2==2) cout<<"       April                     May                    June  "<<endl;
            if(count2==3) cout<<"       July                     August                September  "<<endl;
            if(count2==4) cout<<"      October                  November                December  "<<endl;
            count=0;
        }
    }
}
void setval(Node* head, int a, int b, int data)
{
    Node* itr1=head;
    for (int i = 0; i < a; ++i) itr1=itr1->right;
    for (int i = 0; i < b; ++i) itr1=itr1->down;
    itr1->data=data;
}
Node* initcal()
{
    Node* inits[20];
    for(int i=0;i<20;i++)
    {
        inits[i]=new Node();
        inits[i]->data=0;
        Node* itr= inits[i];
        for(int j=0;j<20;j++)
        {
            Node* temp=new Node();
            temp->data=0;
            itr->right=temp;
            itr=itr->right;
        }
    }
    for (int i = 0; i < 19; ++i)
    {
        Node *t1=inits[i];
        Node *t2=inits[i+1];
        for(int j=0;j<21;j++)
        {
            t1->down=t2;
            t1=t1->right;
            t2=t2->right;
        }
    }
    return inits[0];
}
void storemonth(Node *head, int month, int day, int num)
{
    int x= (month%3)*7; //0 or 1 or 2
    int y= (month/3)*5; //0,1,2,3
    int count=1;
    int temp_x=x;
    temp_x+=day;
    int temp_y=y;
    while(1)
    {   
        setval(head, temp_x ,temp_y ,count);
        ++count;
        ++temp_x;
        if(temp_x-x >6) 
        {
            ++temp_y;
            temp_x=temp_x-7;
        }
        if(temp_y-y>4) temp_y=temp_y-5;
        if(count>num) break;
    }
}
void neatprint(Node *head, int off)
{
    int days[]={31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for(int i=0; i<12;i++)
    {   
        int off_now;
        if(i==0) off_now=off;
        else off_now= 7-(35-days[i-1]-off_now);
        if(off_now>=7) off_now=off_now-7;
        storemonth(head, i, off_now, days[i]);
    }
    printm(head);
}
int main() 
{ 
    Node* head = initcal();
    neatprint(head, 3);
    return 0; 
} 
  
