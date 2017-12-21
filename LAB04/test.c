#include<stdio.h>
int main(){
    int a[100000];
    int i=0;
     while(scanf("%d",&a[i++])==1){}
     int n=i-1;
    //int ans[n]=0;
    for(i=n-1;i>0;i--){
        a[i-1]=a[i-1]+a[i];
        //printf("%d ",ans);
    }
    for(int i=0;i<n;i++) printf("%d ",a[i]);
    printf("\n"); 
}