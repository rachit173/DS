#include "linkedlist.h"
node * addNode(node *hd,int val){
    //allocating address to heap memory 
    //to the next pointer of the current head
    hd ->next= (node *)malloc(sizeof(node));        
    hd = hd -> next;
    hd -> val = val;
    //return the address
    return hd;
}