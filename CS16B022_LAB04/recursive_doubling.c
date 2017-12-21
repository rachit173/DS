#include<stdio.h>
#include<stdlib.h>
#include "linked_list.h"
//array for creating the array for storing pointers to memory of the linked list
node *arr[100000];
int main(){
  int val;
  node *head;
  head=(node *)malloc(sizeof(node));
  head ->next = addNode(head,-1);
  node *tmp = head;
  int i=0; 
  while(scanf("%d",&val)==1){
    tmp -> next = addNode(tmp,val);
    tmp = tmp->next;
    arr[i++] = tmp;
    tmp -> next = NULL;
   }
  int N=i;
  int ai=0;
  //recursive doubling
  for(int k=1;k<N;k=k*2){
    ai=0;
    while(ai+k<N){
      arr[ai]->val=arr[ai]->val+arr[ai+k]->val;
      ai++;
    }
  }
    //printing the output
  for(i=0;i<N;i++)
    printf("%d ",arr[i]->val);
  printf("\n"); 
}
