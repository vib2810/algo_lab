#include <stdio.h> 
#include <iostream> 
#include <math.h>
#include<string>
#include<limits>
#include<stack>
#include <cfloat>

using namespace std; 

//a structure array of strings, along with no of strings that are there. findallexpr will return this structure
class point
{
public:
    double x,y;
    void print()
    {
        cout<< "[" << this->x << ", " << this->y <<"]";
    }
    point(){}
    point(double x, double y){this->x=x, this->y=y;}

};
class line
{
public:
    friend point;
    bool visible=false;
    int line_no;
    double m;
    double c;
    void print()
    {
        cout<< "Line No: " << this->line_no << " Line: y="<< this->m << "*x+" << this->c << endl;
    }
    line(){}
    line(int line_no, double m, double c)
    {
        this->line_no=line_no;
        this->m=m, this->c=c;
    }
    point find_intercept(line l2)
    {
        point *temp=new point();
        temp->x= -(l2.c-this->c)/(l2.m-this->m);
        temp->y= this->m*temp->x+this->c; 
        return *temp;
    }
    // point find_intercept(segment l2)
    // {
    //     double m=(l2.p2.y-l2.p1.y)/(l2.p2.x-l2.p1.x);
    //     double c=l2.p2.y-m*l2.p2.x;
    //     point *temp=new point();
    //     temp->x= -(c-this->c)/(m-this->m);
    //     temp->y= this->m*temp->x+this->c; 
    //     return *temp;
    // }
};
struct segment
{
    int line_no;
    line line_data;
    point p1;
    point p2;
};
point* new_point(double x, double y)
{
    point *ans=new point(x,y);
    return ans;
}
segment* new_segment(int line_no, point x, point y)
{
    segment *ans=new segment;
    ans->p1.x=x.x;
    ans->p1.y=x.y;
    ans->p2.x=y.x;
    ans->p2.y=y.y;
    ans->line_no=line_no;
    return ans;
}
segment* new_segment(line line_data, point x, point y)
{
    segment *ans=new segment;
    ans->p1.x=x.x;
    ans->p1.y=x.y;
    ans->p2.x=y.x;
    ans->p2.y=y.y;
    ans->line_data.m=line_data.m;
    ans->line_data.c=line_data.c;
    ans->line_data.line_no=line_data.line_no;
    ans->line_no=line_data.line_no;

    return ans;
}

void print_segment_arr(segment **m1, int n)
{
    for(int i=0; i<n; i++)
    {
        if(m1[i]!=NULL) 
        {
            cout<<"Line: "<<m1[i]->line_no<<" ";
            m1[i]->p1.print();
            cout<<" To ";
            m1[i]->p2.print();
            cout<<"\n";
        }
    }
}
void PrintStack(stack<segment *> s) 
{ 
    if (s.empty()) return; 
    segment* x = s.top(); 
    s.pop(); 
    PrintStack(s);
    cout<<"Line: "<<x->line_no<<" ";
    x->p1.print();
    cout<<" To ";
    x->p2.print();
    cout<<"\n"; 
    s.push(x); 
} 
segment **method1(int n, line* lines)
{
    line* smallest_line;
    double smallest=DBL_MAX;
    for(int i=0; i<n; i++)
    {   
        if(smallest>lines[i].m) 
        {
            smallest_line=&lines[i];
            smallest=lines[i].m;
        }
    }
    point intercept[n][n];
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i==j) continue;
            intercept[i][j]=lines[i].find_intercept(lines[j]);
        }
    }
    point current_point(-DBL_MAX, DBL_MAX);
    
    point *ans[n];
    int line_nos[n];
    for(int i=0; i<n; i++) ans[i]=NULL;
    ans[0]=new_point(current_point.x, current_point.y); //first point at -inf
    int count=0;
    
    segment **ans_ret=new segment*[n];
    for(int i=0; i<n; i++) ans_ret[i]=NULL;

    int current_line=smallest_line->line_no;
    line_nos[0]=current_line;
    while(1)
    {
        point temp;
        temp.x=DBL_MAX;
        bool flag=false;
        int next_line_no;
        for(int i=0; i<n; i++) //iterate for line nos
        {
            if(i==current_line)  continue; //this is the same line as current line
            if(lines[i].visible==true) continue; //if line already present in visible region
            if(intercept[i][current_line].x >current_point.x) //intercept ahead of the current point x
            {
                flag=true; //atleast 1 such point exists
                if(temp.x>intercept[i][current_line].x) //new intersection has a lower x intercept
                {
                    next_line_no=i;
                    temp.x=intercept[i][current_line].x;
                    temp.y=intercept[i][current_line].y;
                }
            }
        }
        if(flag==false) break;
        count++;
        ans[count]=new_point(temp.x, temp.y);
        line_nos[count]=next_line_no;
        current_point.x=temp.x;
        current_point.y=temp.y;
        current_line=next_line_no;
    }
    for(int i=0; i<count; i++)
    {
        ans_ret[i]=new_segment(line_nos[i], *ans[i], *ans[i+1]);
    }
    point inf(DBL_MAX, DBL_MAX);
    ans_ret[count]=new_segment(line_nos[count], *ans[count], inf);
    return ans_ret;
}
void merge(line *arr, int l, int m, int r);
void mergeSort(line *lines, int l, int r); 

// point is_intersect(segment seg, line l, line *lines)
// {
//     point intersect=l.find_intercept(lines[seg.line_no]);
//     if( ( intersect.x<seg.p2.x && intersect.x>=seg.p1.x )&&( intersect.y>seg.p2.y && intersect.y<seg.p1.y )) return true;
//     return false;
// }
stack<segment *> method2(int n, line* lines)
{
    mergeSort(lines, 0, n-1);
    
    cout<<"Sorted Lines: "<<endl;
    for(int i=0; i<n; i++)
    {   
        lines[i].print();
    }
    point minfx(-DBL_MAX, DBL_MAX);
    point minfy(DBL_MAX, -DBL_MAX);
    point inf(DBL_MAX, DBL_MAX);
    stack<segment *> ans_ret;
    ans_ret.push(new_segment(lines[0], minfx, minfy));
    cout<<"Starting Loop"<<endl;
    for(int i=1; i<n; i++) //get the next line index(sorted) to add
    {
        while(1)
        {
            int a; 
            cin>>a;
            segment *top=ans_ret.top();
            point intersect=lines[i].find_intercept(top->line_data); //point of intersection between line and segment
            if(intersect.x < top->p1.x) 
            {
                ans_ret.pop();
                continue;
            }
            else
            {
                segment *temp;
                if(lines[i].m > 0)
                {
                    temp=new_segment(lines[i], intersect, inf);
                }
                else temp=new_segment(lines[i], intersect, minfy);
                top->p2.x=intersect.x;
                top->p2.y=intersect.y;
                ans_ret.pop();
                ans_ret.push(top);
                ans_ret.push(temp);
                break;
            }
        }
    }
    return ans_ret;
}
int main() 
{ 
    int n;
    cin>>n;
    line lines[n];
    for(int i=0; i<n; i++)
    {
        double m,c;
        cin>>m;
        cin>>c;
        lines[i]=line(i,m,c);
    }

    for(int i=0; i<n; i++)
    {   
        lines[i].print();
    }
    cout<<"\nMethod 1:"<<endl;
    segment **m1;
    m1=method1(n, lines);
    print_segment_arr(m1, n);

    cout<<"\nMethod 2:"<<endl;
    stack<segment*> m2=method2(n, lines);
    PrintStack(m2);
    return 0; 
} 
void merge(line* arr, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    line L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
    {
        L[i].line_no=arr[l + i].line_no;
        L[i].m=arr[l + i].m;
        L[i].c=arr[l + i].c;
    }
    for (j = 0; j < n2; j++) 
    {
        R[j].line_no=arr[m+1+j].line_no;
        R[j].m=arr[m+1+j].m;
        R[j].c=arr[m+1+j].c;
        // R[j] = arr[m + 1+ j]; 
    }
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i].m <= R[j].m) 
        { 
            arr[k].line_no=L[i].line_no;
            arr[k].m=L[i].m;
            arr[k].c=L[i].c;
            // arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k].line_no=R[j].line_no;
            arr[k].m=R[j].m;
            arr[k].c=R[j].c;
            // arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k].line_no=L[i].line_no;
        arr[k].m=L[i].m;
        arr[k].c=L[i].c;
        // arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k].line_no=R[j].line_no;
        arr[k].m=R[j].m;
        arr[k].c=R[j].c;
        // arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(line *lines, int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(lines, l, m); 
        mergeSort(lines, m+1, r); 
  
        merge(lines, l, m, r); 
    } 
} 