#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "partial_tree.h"   //header file for partial trees
struct node* queue1[100005];
struct node* queue2[100005];   //queue for level order traveral
int level[10000005];
void LevelOrderTraversal(struct node* root){
    if(root==NULL) return ;
    int ptr = 0;
    queue1[ptr++] = root;
    while(ptr>0){
        int tmp=0;
        for(int i=0;i<ptr;i++){
            printf("%d ",queue1[i]->val);
            if(queue1[i]->left!=NULL) queue2[tmp++]=queue1[i]->left;
            if(queue1[i]->right!=NULL) queue2[tmp++]=queue1[i]->right;
        }
        printf("\n");
        ptr=tmp;
        for(int i=0;i<ptr;i++) queue1[i]=queue2[i];
    }
}
int main(){
    int query;
    struct node* root=NULL;
    srand(time(NULL));
    FILE *f = fopen("data.temp","w");
    //cloack variables
    clock_t start,end;
    for(int i=64;i<=64;i=i*2){
        int T = i;
        start=clock();
        while(T--)
        {   
            query = rand()%2;
            //--------------------------//
            //query 0:insert
            //query 1:delete
            //query 2:search
            //query otherwise print tree

            //--------------------------//
            int val;
            val = rand()%10;
            // printf("query: %d , val: %d\n",query,val);
            if(query==0){

                // scanf("%d",&val);
                root = insert(root,val);
                // insert done          
                root = rebalance_insert(root,val);
                // balance done
            }
            else if(query==1){
                //query for deletion
                // scanf("%d",&val);
                //mark the node for deletion also 
                //marked variable stores whether the 
                //value to be deleted was found
                int marked = del(root,val); 
                root = rebalance_delete(root);
            }
            else if(query==2){
                //search query
                // scanf("%d",&val);
                //search returns if the variable is found
                int found = search(root,val);
            }
            else{
                LevelOrderTraversal(root);
            }
        }
        LevelOrderTraversal(root);
        end=clock();
        fprintf(f,"%lf %lf\n",(double)i,(double)(end-start)/(i));
    }
    return 0;
}