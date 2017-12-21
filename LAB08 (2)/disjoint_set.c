#include "disjoint_set.h"
// #include<disjoint_set.h>
int rank[10000007];
int p[10000007];
int a[10000007];
int size=0;

void make_set(int x) {
    //creates a new set with a satellite dat
    //for all operations 
    //the key must be used rather than satellite data
    a[size] = x;
    p[size] = size;
    rank[size]=0;
    size++;
}
void link(int x,int y){
    //links the sets by linking their parents
    if(rank[x]>rank[y]) p[y] = find_set(x); 
    else p[x] = find_set(y);
    if(rank[x]==rank[y]) rank[y]++;
}
int find_set(int x){
    //recursively finds the set's main root
    //along the way stores the main root
    //in all the elements of the tree
    //for faster future access
    if(x>=size) return -1;
    if(x!=p[x]) p[x] = find_set(p[x]);
    return p[x];
}
void uni(int x,int y){
    //finds the parents and 
    //if not same link them
    int px = find_set(x);
    int py = find_set(y);
    if(px!=py) link(px,py);
}