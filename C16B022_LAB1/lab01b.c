#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main(int argc,char* argv[]){
  int n=atoi(argv[1]);
  int q=atoi(argv[2]);
  int a[n];
  for(int i=0;i<n;i++){
    a[i]=rand();  
  }
    for(int i=0;i<q;i++){            //processing the queries
    int h=rand()%2;
    if(h==0){
      int t=rand();
    int opt=0;
    for(int j=0;j<n;j++) 
    	if(a[j]==t) 
    	  {
    	    opt=1;
    	    break;
    	  } //if the condition becomes true then we have found the query
    if(opt==0) continue; // not found
    }
    else{
      int t=rand()%n;
      t=a[t];
      int opt=0;
    	for(int j=0;j<n;j++) 
    		if(a[j]==t) {
    	  	opt=1;break;
    	  	}
    	if(opt==0) continue;
    }
    } 
  return 0;
}
