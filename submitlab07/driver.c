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

int main(){
    FILE *f = fopen("data.temp","w");
    clock_t start,end;
    for(int i=20;i<=4;i=i*2){
        start=clock();
        struct colorNode* leaf=new1();
        leaf->c=1;
        struct colorNode* root=NULL;
        int c;
        int val;
        int q=i;
        while(q--){
            c = rand()%2;
            val = rand()%10;
            printf("%d %d\n",c,val);
            // 0 for insert
            if(c==0){
                root = insert(root,val);
                root->c=1;
                // LevelOrderTraversal(root);
                fun(root);
            }
            //1 for insert
            else if(c==1){
                if(search(root,val)==1){
                    
                    root = delfin(root,val);
                    fun(root);
                }
                else {
                    // printf("not found\n");
                }
            }
            //2 for search
            else if(c==2){
                int tmp = search(root,val);
            }
            else {
                printf("Original tree: \n");
                LevelOrderTraversal(root);
            }
        }
        LevelOrderTraversal(root);
        end = clock();
        fprintf(f,"%lf %lf\n",(double)i,(double)(end-start)/(i));
}
    fclose(f);
    return 0;
}