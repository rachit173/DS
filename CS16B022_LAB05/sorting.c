#include<stdio.h>
#define sc(a) scanf("%d",&a)
#define swap(a,b) {int _ = a; a = b; b = _;}
int tmp;
int mid;
void qs(int a[],int start,int end){
  //printf("%d %d\n",start,end);
  if(end-start<1) return ;
  //swap first and last element
    int pivot = a[start];   //take the first element of the array as pivot
    int st = start;
    int en = end;
    st ++;
    //Bringing elements smaller than the pivot to the beginning of the array
    while(st<en){
      if(a[st]>pivot){
        swap(a[st],a[en])
        en--;
      }
      else st++;
    }
    if(a[start]>a[st]) swap(a[start],a[st])
    //now the array to be sorted is divided in 
    //two parts where left part has all
    //elements less than equal to pivot
    qs(a,start,st-1); 
    //all elements greater than equal to pivot
    qs(a,st,end);
}
void ms(int a[],int b[],int start,int end){
    //base case when the number of elements 
    //to be sorted is less than 2
    if(end-start<2) return ;
    int mid = start+(end-start)/2;
    //recursive sort the right and left half
    ms(a,b,start,mid);
    ms(a,b,mid,end);
    int c1 = start;
    int c2 = mid;
    int i=start;
    //mergeing the two sorted arrays  i.e. the left and right half
    while(c1<mid && c2<end){
      if(a[c1]<a[c2]){
          b[i++]=a[c1++];
      }
      else b[i++]=a[c2++];
    }
    while(c1<mid) b[i++] = a[c1++];
    while(c2<end) b[i++] = a[c2++];
    for(int i=start;i<end;i++) {
      a[i] = b[i];
    }
  }
int main(){
  //type of sort merge or quicksort
  int type;
  sc(type);
  //Number of elements to be sorted 
  int n;
  sc(n);
  int a[n];
  int b[n];
  for(int i=0;i<n;i++)
  {
     sc(a[i]);
  }
  if(type==0) ms(a,b,0,n);
  else  qs(a,0,n-1);
  for(int i=0;i<n;i++)
    printf("%d ",a[i]);
  printf("\n");
  return 0;
}
