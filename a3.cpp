#include <stdio.h> 
#include <iostream> 
#include <math.h>
#include<string>
#include<limits>
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

};
struct segment
{
    int line_no;
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
segment **method1(int n, line* lines)
{
    line* smallest_line;
    double smallest=DBL_MAX;
    for(int i=0; i<n; i++)
    {   
        // lines[i].print();
        if(smallest>lines[i].m) 
        {
            smallest_line=&lines[i];
            smallest=lines[i].m;
        }
    }
    // cout<<"smallest line_no: "<<smallest_line->line_no<<endl;;
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
    
    segment *ans_ret[n];
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
segment **method2(int n, line* lines)
{
    mergeSort(lines, 0, n-1);
    
    cout<<"Sorted Lines: "<<endl;
    for(int i=0; i<n; i++)
    {   
        // lines[i].line_nos
        lines[i].print();
    }
    point minf(-DBL_MAX, DBL_MAX);
    point minfy(DBL_MAX, -DBL_MAX);
    point inf(DBL_MAX, DBL_MAX);

    segment *ans_ret[n];
    for(int i=0; i<n; i++) ans_ret[i]=NULL;
    ans_ret[0]=new_segment(lines[0].line_no, minf, minfy);
    int a=(minfy.y==-DBL_MAX );
    cout<< a<<endl;
    print_segment_arr(ans_ret, n);
    cout<<"Starting Loop"<<endl;
    for(int i=1; i<n; i++) //get the next line index(sorted) to add
    {
        int count=0;
        for(int i=0; i<n; i++) if(ans_ret[i]!=NULL) count++;
        cout<<"No in stack: "<<count<<endl;
        
        //case first line intersect
        point intersect_l0=lines[0].find_intercept(lines[i]);
        if( ( intersect_l0.x<ans_ret[0]->p2.x && intersect_l0.x>=ans_ret[0]->p1.x )&&( intersect_l0.y>ans_ret[0]->p2.y && intersect_l0.y<ans_ret[0]->p1.y ))
        {
            for(int i=2; i<n; i++) ans_ret[i]=NULL;
            ans_ret[0]->p2.x=intersect_l0.x;
            ans_ret[0]->p2.y=intersect_l0.y;
            ans_ret[1]=new_segment(lines[i].line_no, intersect_l0, intersect_l0);
            if(lines[i].m>0) 
            {
                ans_ret[1]->p2.x=inf.x;
                ans_ret[1]->p2.y=inf.y;
            }
            else
            {
                ans_ret[1]->p2.x=minfy.x;
                ans_ret[1]->p2.y=minfy.y;
            }
        }
        //case last line intersect
        point intersect_ll=lines[count-1].find_intercept(lines[i]);
        if( ( intersect_ll.x<ans_ret[count-1]->p2.x && intersect_l0.x>=ans_ret[count-1]->p1.x )&&( intersect_l0.y>ans_ret[count-1]->p2.y && intersect_l0.y<ans_ret[count-1]->p1.y ))
        {
            if(ans_ret[count-1]->p2.x==DBL_MAX && ans_ret[count-1]->p2.y ==DBL_MAX) //check if last parent is +inf
            {
                //need to update just the last segment
                ans_ret[count-1].line_no=lines[i].line_no;
                ans_ret[count-1].p1.x=intersect_ll.x;
                ans_ret[count-1].p1.y=intersect_ll.y;
            }
        }

        //case in the middle of first and last point intersect
        //update stack according to the intersection of the point with line

        print_segment_arr(ans_ret, n);
        cout<<"------------------------"<<endl;

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
    segment **m1=method1(n, lines);
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

    cout<<"\nMethod 2:"<<endl;
    segment **m2=method2(n, lines);

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