#include "RBTree1.h"
struct colorNode* new1(){
    struct colorNode* ret = (struct colorNode*)malloc(sizeof(struct colorNode));
    ret->c = 0;
    ret->p=NULL;
    ret->extrablack=0;
    ret->left=NULL;
    ret->right=NULL;
    return ret;
}
int check_leaf(struct colorNode* root){
    if(root->left==NULL&&root->right==NULL) return 1;
    return 0;
}
void fun(struct colorNode* root){
    if(root==NULL) return ;
    int ptr = 0;
    queue1[ptr++] = root;
    while(ptr>0){
        int tmp=0;
        for(int i=0;i<ptr;i++){
            if(queue1[i]->c==0){
                if((queue1[i]->left)->c==0||(queue1[i]->right)->c==0) printf("error ");
            }
            if(queue1[i]->left!=NULL) queue2[tmp++]=queue1[i]->left;
            if(queue1[i]->right!=NULL) queue2[tmp++]=queue1[i]->right;
        }
        // printf("\n");
        ptr=tmp;
        for(int i=0;i<ptr;i++) queue1[i]=queue2[i];
    }
}
struct colorNode* left_rotate(struct colorNode* root){
    struct colorNode* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
    return right_child;
}
struct colorNode* right_rotate(struct colorNode* root){
    struct colorNode* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
    return left_child;
}
struct colorNode* insert(struct colorNode* root,struct colorNode* p,int val){
    if(root==NULL||check_leaf(root)){
        // printf("here");
        root = new1();
        root->val = val;
        root->left = new1();
        root->right = new1();
        root->left->p = root;
        root->right->p = root;
        (root->left)->c=1;
        (root->right)->c=1;
        root->p = p;
        return root;
    }
    if(val==root->val) return root;
    if(val>root->val){
        root->right = insert(root->right,root,val);
        if(root->c){
            struct colorNode* px=root->right;
            struct colorNode* lc=root->left;
            if(px==NULL||lc==NULL) return root;
            //checck if the child is red
            if(!(px->c)){
                struct colorNode *x1=px->left;
                struct colorNode *x2=px->right;
                if((x1->c)==0){
                    if((lc->c)==0){
                        //recolor the nodes
                        lc->c=1;
                        px->c=1;
                        root->c=0;
                        return root;
                    }
                    else{
                        root->right = right_rotate(px);
                        struct colorNode* ret = left_rotate(root);
                        ret->c = 1;
                        (ret->left)->c = 0;
                        return ret;
                    }
                }
                else if((x2->c)==0){
                    if((lc->c)==0){
                        //recolor the nodes
                        lc->c=1;
                        px->c=1;
                        root->c=0;
                        return root;
                    }
                    else{
                        struct colorNode* ret = left_rotate(root);
                        ret->c = 1;
                        (ret->left)->c = 0;
                        return ret;
                    }
                }
            }
        }
        return root;
    }
    else{
        root->left = insert(root->left,root,val);
        //root is black
        if((root->c)){
            struct colorNode* px=root->left;
            struct colorNode* rc=root->right;
            if(px==NULL||rc==NULL) return root;
            //checck if the child is red
            if(!(px->c)){
                struct colorNode *x1=px->left;
                struct colorNode *x2=px->right;
                if(x1->c==0){
                    if(rc->c==0){
                        //recolor the nodes
                        rc->c=1;
                        px->c=1;
                        root->c=0;
                        return root;
                    }else{
                        struct colorNode* ret = right_rotate(root);
                        ret->c = 1;
                        (ret->right)->c = 0;
                        return ret;
                    }
                }
                else if(x2->c==0){
                    if(rc->c==0){
                        //recolor the nodes
                        rc->c=1;
                        px->c=1;
                        root->c=0;
                        return root;
                    }else{
                        root->left = left_rotate(px);
                        struct colorNode* ret = right_rotate(root);
                        ret->c = 1;
                        (ret->right)->c = 0;
                        return ret;
                    }
                }
            }
        }
        return root;
    }
    return root;
}
int leftmostInRightSubtree(struct colorNode* root){
    if(check_leaf(root->left)){
        return root->val;
    }
    return leftmostInRightSubtree(root->left);
}
struct colorNode* case1_1_left(struct colorNode* root){
    // printf("case 1 1 l with root value of %d and right child %d\n",root->val,root->right->val);
    (root->left)->extrablack=0; 
    int coltemp = root->c;
    root->c=1;
    root->right->right->c=1;
    root = left_rotate(root);
    root->c = coltemp;
    return root;
}
struct colorNode* case1_2_left(struct colorNode* root){
    // printf("case 1 2 l\n");
    (root->left)->extrablack=0; 
    int coltemp = root->c;
    root->c=1;
    root->right->right->c=1;
    root = left_rotate(root);
    root->c = coltemp;
    return root;
}
struct colorNode* case1_3_left(struct colorNode* root){
    // printf("case 1 3 l\n");
    (root->right)->c = 0;
    ((root->right)->left)->c = 1;
    root->right = right_rotate(root->right);
    return case1_1_left(root);
}
struct colorNode* case1_4_left(struct colorNode* root){
    // printf("case 1 4 l\n");
    (root->right)->c = 0;
    (root->left)->extrablack = 0;
    root->extrablack = 1;
    return root;
}
struct colorNode* case1_1_right(struct colorNode* root){
    // printf("case 1 1 r\n");
    (root->right)->extrablack=0; 
    int coltemp = root->c;
    root->c=1;
    ((root->left)->left)->c=1;
    root = right_rotate(root);
    root->c = coltemp;
    return root;
}
struct colorNode* case1_2_right(struct colorNode* root){
    // printf("case 1 2 r\n");
    (root->right)->extrablack=0; 
    int coltemp = root->c;
    root->c=1;
    ((root->left)->left)->c=1;
    root = right_rotate(root);
    root->c = coltemp;
    return root;
}
struct colorNode* case1_3_right(struct colorNode* root){
    // printf("case 1 3 r\n");
    (root->left)->c = 0;
    ((root->left)->right)->c = 1;
    root->left = left_rotate(root->left);
    return case1_1_right(root);
}
struct colorNode* case1_4_right(struct colorNode* root){
    // printf("case 1 4 r\n");
    root->left->c = 0;
    (root->right)->extrablack = 0;
    root->extrablack = 1;
    return root;
}
void deb(){
    printf("err");
}
struct colorNode* case1_left(struct colorNode* root){
    if((root->right)->left->c==1&&(root->right)->right->c==0){
        root = case1_1_left(root);
        return root;
    }
    if((root->right)->left->c==0&&(root->right)->right->c==0){
        root = case1_2_left(root);
        return root;
    }
    if((root->right)->left->c==0&&(root->right)->right->c==1){
        root = case1_3_left(root);
        return root;
    }
    if((root->right)->left->c==1&&(root->right)->right->c==1){
        root = case1_4_left(root);
        return root;
    }
    return root;    //may have errors
}
struct colorNode* case1_right(struct colorNode* root){
    if((root->left)->right->c==1&&(root->left)->left->c==0)
    {
        root = case1_1_right(root);
        return root;
    }
    if((root->left)->right->c==0&&(root->left)->left->c==0)
    {
        root = case1_2_right(root);
        return root;
    }
    if((root->left)->right->c==0&&(root->left)->left->c==1)
    {
        root = case1_3_right(root);
        return root;
    }
    if((root->left)->right->c==1&&(root->left)->left->c==1)
    {
        root = case1_4_right(root);
        return root;
    }
    return root; //may have errors
}
struct colorNode* del(struct colorNode* root,struct colorNode* x,int val){
    // printf("here");
    if(root==NULL||check_leaf(root)==1) return NULL;
    // printf("%d %d : ",root->c,root->val);
    if(root->val==val){
        // both the children are leaf
        if(check_leaf(root->left)&&check_leaf(root->right)){
            // (root->right)->extrablack=root->c;                  //delete the left leaf and give the right leaf the extra black
            // free(root->left);
            
        }
        //only the left child is leaf
        else if(check_leaf(root->left)&&!check_leaf(root->right)){
            // (root->right)->extrablack=root->c;                  //transfer the right subtree to parent node 
            // free(root->left);
            truex = root->right;
            return root->right;
        }
        //only the right child is leaf
        else if(!check_leaf(root->left)&&check_leaf(root->right)){
            // (root->left)->extrablack=root->c;                   //transfer the left subtree to parent node
            // free(root->right);
            truex = root->left;
            return root->left;
        }
        //when the node to be deleted has to two children 
        else{
            // printf("two children");
            int v1 = leftmostInRightSubtree(root->right);           //find the inorder successor    
            root->val=v1;                                           //assign the value to this node 
            root->right = del(root->right,x,v1);
            return root;                      
        }
    }
    if(val>root->val){
        return del(root->right,x,val);
    }
    else{
        // printf("left del hq %d\n",root->val);
        return del(root->left,x,val);
    }
    return NULL;   
}
void leftRotate(struct colorNode* p){
    if((p->p)->left==p) (p->p)->left = left_rotate(p);
    else (p->p)->right = left_rotate(p);
}
void rightRotate(struct colorNode* p){
    if((p->p)->left==p) (p->p)->left = right_rotate(p);
    else (p->p)->right = right_rotate(p);
}
void del_fix_up(struct colorNode* root,struct colorNode* x){
    x = truex;
    printf("enter to the hell\n");
    while(x!=root&&x->c==1){
        //if the double black node is the left child of parent
        printf("%d %d\n",x->val,x->p->val);
        if(x==(x->p->left)){
            printf("left member\n");
            struct colorNode* w = x->p->right; //w is the sibling of x
            //if the sibling w is of red color
            if(w->c==0){
                printf("1.2\n");
                w->c=1;
                x->p->c=0;
                leftRotate(x->p);
                w = x->p->right;   //make the sibling to the right child of p[x]
            }
            if(w->left->c==1&&w->right->c==1){
                printf("case 1.1.4 the good life\n");
                w->c=0;
                x = x->p;
            }
            else{ 
                printf("1.1.1,2,3\n");
                if(w->right->c==1){
                    printf("case 1.1.3 the bad life\n");
                    w->left->c=1;
                    w->c=0;
                    rightRotate(w);
                    w = x->p->right;
                }
                w->c=x->p->c;
                x->p->c=1;
                w->right->c=1;
                leftRotate(x->p);
                x = root;
            } 
        }
        //if the double black node is right child of parent
        else{
            printf("right member\n");
            struct colorNode* w = x->p->left; //w is the sibling of x
            //if the sibling w is of red color
            if(w->c==0){
                w->c=1;
                x->p->c=0;
                rightRotate(x->p);
                w = x->p->right;   //make the sibling to the right child of p[x]
            }
            if(w->right->c==1&&w->right->c==1){
                printf("case 1.1.4 the good life\n");
                w->c=0;
                x = x->p;
            }
            else{ 
                printf("1.1.1,2,3\n");
                if(w->right->c==1){
                    printf("case 1.1.3 the bad life\n");
                    w->right->c=1;
                    w->c=0;
                    rightRotate(w);
                    w = x->p->right;
                }
                w->c=x->p->c;
                x->p->c=1;
                w->right->c=1;
                rightRotate(x->p);
                x = root;
            } 
        }
    }
    x->c=1;
}
int search(struct colorNode* root,int val){
    if(root==NULL||check_leaf(root)) return 0;
    if(root->val==val) return 1;
    if(root->val>val) return search(root->left,val);
    else return search(root->right,val);
}