#include "RBTree.h"
struct colorNode* new1(){
    struct colorNode* ret = (struct colorNode*)malloc(sizeof(struct colorNode));
    ret->c = 0; //variable to store the color
    ret->leaf=0;   //(optional) i  have not used in the version submitted last
    ret->extrablack=0;  //storing extrablack in the node
    ret->left=NULL;
    ret->right=NULL;
    return ret;
}
int check_leaf(struct colorNode* root){
    //the function checks if the node is leaf by checking if both its children NULL
    if(root->left==NULL&&root->right==NULL) return 1;
    return 0;
}
void fun(struct colorNode* root){
    //This is testing function for checking if no red node has children which are not black
    //The code is same as Level Order Traversal 
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
    //Left rotates the at the root at returns the new root 
    // to be attached to the parent
    struct colorNode* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
    return right_child;
}
struct colorNode* right_rotate(struct colorNode* root){
    //Right rotates the at the root at returns the new root 
    // to be attached to the parent
    struct colorNode* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
    return left_child;
}
struct colorNode* insert(struct colorNode* root,int val){
    //Insert Function for all the cases
    if(root==NULL||check_leaf(root)){
        //Terminal case when we reach at the end of a tree path 
        //have to insert the new node
        root = new1();
        root->val = val;
        root->left = new1();
        root->right = new1();
        (root->left)->c=1;
        (root->right)->c=1;
        (root->left)->leaf=1;
        (root->right)->leaf=1;
        return root;
    }
    if(val==root->val) return root;     //If the value to be inserted is found in the tree 
                                        //then just the return the tree as it is
    if(val>root->val){
        //This is the case if node has been inserted in the right subtree  
        root->right = insert(root->right,val);
        if(root->c){
            //check if the node inserted 
            struct colorNode* px=root->right;
            struct colorNode* lc=root->left;
            if(px==NULL||lc==NULL) return root;
            //check if the parent of the child is red
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
        root->left = insert(root->left,val);
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
    // case 1 1 left
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
   // printf("err");
}
struct colorNode* case1_left(struct colorNode* root){
    //This will decide the case which needs to operate if the left child has a extra black 
    //and the sibling is black
    if(root->left->extrablack==0) return root;
    if(root->left->c==0){
        root->left->c=1;
        root->left->extrablack = 0;
        return root;
    }
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
    //This will decide the case which needs to operate if the left child has a extra black 
    //and the sibling is black
    if(root->right->extrablack==0) return root;
    if(root->right->c==0){
        root->right->c=1;
        root->right->extrablack = 0;
        return root;
    }
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
struct colorNode* del(struct colorNode* root,int val){
    // printf("here");
    if(root==NULL||check_leaf(root)==1) return root;
    // printf("%d %d : ",root->c,root->val);
    if(root->val==val){
        // both the children are leaf
        if(check_leaf(root->left)&&check_leaf(root->right)){
            (root->right)->extrablack=root->c;                  //delete the left leaf and give the right leaf the extra black
            // free(root->left);
            return root->right;
        }
        //only the left child is leaf
        else if(check_leaf(root->left)&&!check_leaf(root->right)){
            (root->right)->extrablack=root->c;                  //transfer the right subtree to parent node 
            // free(root->left);
            return root->right;
        }
        //only the right child is leaf
        else if(!check_leaf(root->left)&&check_leaf(root->right)){
            (root->left)->extrablack=root->c;                   //transfer the left subtree to parent node
            // free(root->right);
            return root->left;
        }
        //when the node to be deleted has to two children 
        else{
            // printf("two children");
            int v1 = leftmostInRightSubtree(root->right);           //find the inorder successor    
            root->val=v1;                                           //assign the value to this node 
            root->right = del(root->right,v1);                      
            if(root->right->extrablack==0) return root;             
            // when the extrablack carrying node is red                 
            if((root->right)->c==0)
            {
                // printf("recoloring");
                if((root->right)->extrablack>0)
                {
                    (root->right)->c=1;
                    (root->right)->extrablack=0;
                }
                return root;
            }
            //case 2 when the sibling is red
            if(root->left->c==0)
            {
                // printf("sibling is red");
                root = right_rotate(root);
                (root->right)->c=0;
                root->c=1;
                root->right = case1_right(root->right);
                root = case1_right(root);
                return root;
            }
            //when the sibling is black
            root  = case1_right(root);
            return root;
        }
    }
    if(val>root->val){
        //The deletion takes place in right subtree
        root->right = del(root->right,val);
        //If there is no extrablack in the right child
        //the tree already satisfies RB properties
        if(root->right->extrablack==0) return root;
        //If the right child is red with extrablack then we need
        //to color it to black and we are done
        if((root->right)->c==0)
        {
            // printf("recoloring");
            if((root->right)->extrablack>0){
                (root->right)->c=1;
                (root->right)->extrablack=0;
            }
            return root;
        }
        //if the right child is black and the sibling is red 
        if(root->left->c==0)
        {
            // printf("sibling is red");
            root = right_rotate(root);
            (root->right)->c=0;
            root->c=1;
            root->right = case1_right(root->right);
            root = case1_right(root);
            return root;
        }
        //If the right child is black and the sibling is black 
        root = case1_right(root);
        return root;
    }
    else{
        // The deletion takes place in the left subtree
        root->left = del(root->left,val);
        // If the left chld has no extrablack then the RBTree property is 
        //already satisfied 
        if(root->left->extrablack==0) return root;
        //If the left child is red with extrablack then 
        //we just recolor it 
        if((root->left)->c==0){
            // recoloring 
            if((root->left)->extrablack>0){
                (root->left)->c=1;
                (root->left)->extrablack=0;
            }
            return root;
        }
        //If the left child is black with the sibling red
        if(root->right->c==0){
            // printf("sibling is red");
            root = left_rotate(root);
            (root->left)->c=0;
            root->c=1;
            root->left = case1_left(root->left);
            root = case1_left(root);
            return root;
        }
        //If the left chld is black with the sibling black 
        root = case1_left(root);
        return root;
    }
    return root;   
}
struct colorNode* delfin(struct colorNode* root,int val){
    //The function just calls the
    //del function and sets the root color 
    //to black after the call
    root = del(root,val);
    root->c=1;
    root->extrablack=0;
    return root;
}
int search(struct colorNode* root,int val){
    //The search function which returns 1 is found and 0 if not
    if(root==NULL||check_leaf(root)) return 0;
    if(root->val==val) return 1;
    if(root->val>val) return search(root->left,val);
    else return search(root->right,val);
}