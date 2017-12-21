#include "partial_tree.h"

int left_h;
int right_h;
int left_c;
int right_c;
//The tree node is commented below it is defined in the header file
// struct node{
//     int val;
//     int num;
//     int del;
//     int height;
//     struct node *left;
//     struct node *right;
// }node;
//

struct node* newnode(){
    //Helper function for creating a new node and setting new values
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->num = 1;
    temp->del = 0;
    temp->height = 1;
    temp->left = temp->right = NULL;
    return temp; 
}
//Global variable to keep track of the number of nodes
//marked for deletion 
int deleted_nodes=0;
//
struct node* insert(struct node* root,int val){
    //insert function just inserts a node 
    //as in a usual binary search treee
    if(root==NULL){
        // printf("here\n");
        root = newnode();
        // printf("here\n");
        root->val = val;
        // printf("here\n");
        return root;
    }
    if(root->val == val) return root;
    //Go to the left subtree if the value is less than root
    if(val<root->val) {
        //The updated left subtree is linked with the root 
        root->left = insert(root->left,val);
        //Updating the number of children in the subtree 
        left_c = (root->left==NULL)?0:(root->left)->num;
        right_c = (root->right==NULL)?0:(root->right)->num;
        root->num = left_c + right_c + 1;
        //Updating the height of the subtree
        left_h = (root->left==NULL)?0:(root->left)->height;
        right_h = (root->right==NULL)?0:(root->right)->height;
        root->height = (max(left_h,right_h))+1;
        return root;
    }
    //Go to the right subtree of the value is greater than the root
    if(val>root->val) {
        //The updated right subtree with the inserted node is linked with the root
        root->right = insert(root->right,val);
        //Updating the subtree size due to possible insertion
        left_c = root->left==NULL?0:(root->left)->num;
        right_c = root->right==NULL?0:(root->right)->num;
        root->num = left_c + right_c + 1;
        //Updating the height of the subtree 
        left_h = root->left==NULL?0:(root->left)->height;
        right_h = root->right==NULL?0:(root->right)->height;
        root->height = (max(left_h,right_h))+1;
        return root;
    }
}
int del(struct node* root,int val){
    //Function to mark nodes for deletion like in a binaryn search tree
    //Not found or tree not present then return 0 
    if(root==NULL) return 0;
    if(root->val==val) {
        if(root->del==1){
            return 0;
        }
        deleted_nodes++;
        root->del=1;
        return 1;
    }
    //If the value is lesser than the value at the root then 
    //go to the left subtree
    if(val<root->val)
        return del(root->left,val);
    //If the value is greater than the value at the root then 
    if(val>root->val)
        return del(root->right,val);
}
int search(struct node* root,int val){
    //same as delete function just don't mark nodes for deletion
    if(root==NULL) return 0;
    if(root->val==val) {
        if(root->del==1){
            return 0;
        }
        
        return 1;
    }
    if(val<root->val)
        return search(root->left,val);
    if(val>root->val)
        return search(root->right,val);
}
struct node* reconstruct(struct node* root,int a[],int b[],int start,int end){
    if(end-start<0){
        return NULL;
    }
    //calaculate the mid portion of the segment where root value 
    //has to be stored 
    int mid = start + (end-start+1)/2;
    root = newnode();
    root->val = a[mid];
    root->del = b[mid];
    //Dividing the segment using mid and recursively building 
    root->left = reconstruct(root->left,a,b,start,mid-1);
    root->right = reconstruct(root->right,a,b,mid+1,end);
    //Setting the subtree heights
    left_h = root->left==NULL?0:(root->left)->height;
    right_h = root->right==NULL?0:(root->right)->height;
    root->height = max(left_h,right_h)+1;
    //Setting the subtree size
    left_c = root->left==NULL?0:(root->left)->num;
    right_c = root->right==NULL?0:(root->right)->num;
    // printf("%d ,,",left_c+right_c+1);
    root->num = left_c + right_c + 1;
    return root;
}
void inorder(struct node* root,int a[],int b[],int start){
    //Function for inorder traversal to store tha tree in an array in a 
    //sorted manner
    left_c = (root->left==NULL)?0:(root->left)->num;
    //Store the node value in the array
    a[start+left_c] = root->val;
    b[(start+left_c)] = root->del;
    int tmp = start+left_c+1;
    if(root->left!=NULL) inorder(root->left,a,b,start);
    if(root->right!=NULL) inorder(root->right,a,b,tmp);
}
struct node* rebalance_insert(struct node* root,int  val){
    // Check if the subtree is too long and needs to be reconstructed
    if(root->height>2*log2(root->num*1.0)+1) {
        int n = root->num;
        //Array to store the subtree
        int *a = (int *)malloc(sizeof(int)*(root->num));
        int *b = (int *)malloc(sizeof(int)*(root->num));
        //Create a sorted array of elements 
        inorder(root,a,b,0);
        //using divide and conquer create an almost balanced binary tree 
        //from the sorted array
        root = NULL;
        root = reconstruct(root,a,b,0,n-1);
        inorder(root,a,b,0);
        // Set the height of the root at ehich the subtree has
        //been recinstructed
        left_h = root->left==NULL?0:(root->left)->height;
        right_h = root->right==NULL?0:(root->right)->height;
        root->height = max(left_h,right_h)+1;
        free(a);
        free(b);
        return root;
        }
    if(root->val == val) return root;
    if(val<root->val){
        root->left = rebalance_insert(root->left,val);
        left_h = root->left==NULL?0:(root->left)->height;
        right_h = root->right==NULL?0:(root->right)->height;
        root->height = max(left_h,right_h)+1;
        return root;
    }
    if(root->val<val){
        root->right = rebalance_insert(root->right,val);
        left_h = root->left==NULL?0:(root->left)->height;
        right_h = root->right==NULL?0:(root->right)->height;
        root->height = max(left_h,right_h)+1;
        return root;
    }
}

struct node* rebalance_delete(struct node* root){
    //Cheeck if more than half of the nodes are due ti be deleted
    if(root==NULL||2*deleted_nodes<=(root->num)) return root;
    int *a = (int *)malloc(sizeof(int)*(root->num));
    int *b = (int *)malloc(sizeof(int)*(root->num));
    //Form sorted array with nodes marked for deletion
    inorder(root,a,b,0);
    int n=root->num;
    int n1=root->num-deleted_nodes;
    int a1[n1];
    int b1[n1];
    int j=0;
    //Form sorted array removing the elements marked for deletion
    for(int i=0;i<n;i++){
        if(b[i]==0){
            a1[j]=a[i];
            b1[j]=b[i];
            j++;
        }
    }
    // reconstruct almost balaced BSTusing sorted array
    root = reconstruct(root,a1,b1,0,n1-1);
    deleted_nodes=0;
    return root;
}
