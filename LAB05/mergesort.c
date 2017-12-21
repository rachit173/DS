#include<stdio.h>
#define sc(a) scanf("%d",&a)
int tmp;
void ms(int a[],int b[],int start,int end){
  if(end-start<2) return ;
  int mid = start+(end-start)/2;
  ms(a,b,start,mid);
  ms(a,b,mid,end);
  int c1 = start;
  int c2 = mid;
  int i=start;
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
  int n;
  sc(n);
  int a[n];
  int b[n];
  for(int i=0;i<n;i++)
  {
     sc(a[i]);
  }
  ms(a,b,0,n);
  for(int i=0;i<n;i++)
    printf("%d ",a[i]);
   printf("\n");
  return 0;
}
