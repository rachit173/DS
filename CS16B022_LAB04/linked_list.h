#include<stdio.h>
#include<stdlib.h>
//node for the linked list
typedef struct node{
    int val;
    struct node *next;
  }node;
node *addNode(node *hd,int val);