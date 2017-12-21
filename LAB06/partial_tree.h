#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define max(a,b) (a>b?a:b)
typedef struct node{
    int val;
    int num;
    int del;
    int height;
    struct node *left;
    struct node *right;
}node;
struct node* insert(struct node* ,int);
struct node* rebalance_insert(struct node* ,int);
int del(struct node*,int );
struct node* rebalace_delete(struct node* );
int search(struct node*,int );
void inorder(struct node*,int [],int [],int);
struct node* reconstruct(struct node* ,int [],int [],int ,int);