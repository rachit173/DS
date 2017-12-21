#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main(int argv,char* argc[]){
  int n=atoi(argc[1]);
  int q=atoi(argc[2]);// the argument 2 will be the number ofn elements
  int a[n];                 // initialising the array for storing the randomly generated n numbers
  srand(time(NULL));        //seeding the rand function 
  for(int i=0;i<n;i++) a[i]=rand();   //assigning the random numbers to the array using a for loop
  for(int i=0;i<q;i++){            //processing the queries
    int t=rand();
    int opt=0;
    for(int j=0;j<n;j++) if(a[j]==t) {opt=1;break;} //if the condition becomes true then we have found the query
    if(opt==0) continue; // not found
  } 
  
return 0;
}
