#include<stdio.h>
#define sc(a) scanf("%d",&a)
#define swap(a,b) {int _ = a; a = b; b = _;}
int tmp;
int mid;
void qs(int a[],int start,int end){
  //printf("%d %d\n",start,end);
  if(end-start<1) return ;
  //swap first and last element
    int pivot = a[start];
    int st = start;
    int en = end;
    st ++;
    while(st<en){
      if(a[st]>pivot){
        swap(a[st],a[en])
        en--;
      }
      else st++;
    }
    if(a[start]>a[st]) swap(a[start],a[st])
    qs(a,start,st-1); 
    qs(a,st,end);
}
int main(){
  int n;
  sc(n);
  int a[n];
  for(int i=0;i<n;i++)
  {
     sc(a[i]);
  }
  qs(a,0,n-1);
  for(int i=0;i<n;i++)
    printf("%d ",a[i]);
  printf("\n");
  return 0;
}
