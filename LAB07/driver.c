#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "RBTree.h"   //header file for partial trees
struct colorNode* queue1[100005];
struct colorNode* queue2[100005];   //queue for level order traveral
void LevelOrderTraversal(struct colorNode* root){
    if(root==NULL) return ;
    int ptr = 0;
    queue1[ptr++] = root;
    while(ptr>0){
        int tmp=0;
        for(int i=0;i<ptr;i++){
            printf("%d %d,",queue1[i]->c,queue1[i]->val);
            if(queue1[i]->c==0){
                if((queue1[i]->left)->c==0||(queue1[i]->right)->c==0) printf("error ");
            }
            if(queue1[i]->left!=NULL) queue2[tmp++]=queue1[i]->left;
            if(queue1[i]->right!=NULL) queue2[tmp++]=queue1[i]->right;
        }
        printf("\n");
        ptr=tmp;
        for(int i=0;i<ptr;i++) queue1[i]=queue2[i];
    }
}

// int main(){
//     int query;
//     struct node* root=NULL;
//     srand(time(NULL));
//     FILE *f = fopen("data.temp","w");
//     //cloack variables
//     clock_t start,end;
//     for(int i=10000;i<=1000000;i=i*2){
//         int T = i;
//         start=clock();
//         while(T--)
//         {   
//             query = rand()%2;
//             //--------------------------//
//             //query 0:insert
//             //query 1:delete
//             //query 2:search
//             //query otherwise print tree

//             //--------------------------//
//             int val;
//             val = rand();
//             // printf("query: %d , val: %d\n",query,val);
//             if(query==0){

//                 // scanf("%d",&val);
//                 root = insert(root,val);
//                 // insert done          
//                 root = rebalance_insert(root,val);
//                 // balance done
//             }
//             else if(query==1){
//                 //query for deletion
//                 // scanf("%d",&val);
//                 //mark the node for deletion also 
//                 //marked variable stores whether the 
//                 //value to be deleted was found
//                 int marked = del(root,val); 
//                 root = rebalance_delete(root);
//             }
//             else if(query==2){
//                 //search query
//                 // scanf("%d",&val);
//                 //search returns if the variable is found
//                 int found = search(root,val);
//             }
//             else{
//                 LevelOrderTraversal(root);
//             }
//         }
//         end=clock();
//         fprintf(f,"%lf %lf\n",(double)i,(double)(end-start)/(i));
//     }
//     return 0;
// }
int main(){
    FILE *f = fopen("data.temp","w");
    clock_t start,end;
    for(int i=1024;i<=129000;i=i*2){
        start=clock();
        struct colorNode* leaf=new1();
        leaf->c=1;
        struct colorNode* root=NULL;
        int c;
        int val;
        int q=i;
        while(q--){
            c = rand()%2;
            val = rand()%10000;
            // printf("%d %d\n",c,val);
            if(c==0){
                root = insert(root,val);
                root->c=1;
                // LevelOrderTraversal(root);
                fun(root);
            }
            else if(c==1){
                if(search(root,val)==1){
                    // printf("found\n");
                    // printf("%d",root->val);
                    root = delfin(root,val);
                    fun(root);
                }
                else {
                    // printf("not found\n");
                }
            }
            else if(c==2){
                int tmp = search(root,val);
            }
            else {
                printf("Original tree: \n");
                LevelOrderTraversal(root);
            }
        }
        end = clock();
        fprintf(f,"%lf %lf\n",(double)i,(double)(end-start)/(i));
}
    fclose(f);
    return 0;
}