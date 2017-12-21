struct colorNode* case1_1_left(struct colorNode* root){
    printf("case 1 1 l with root value of %d and right child %d\n",root->val,root->right->val);
    (root->left)->extrablack=0; 
    int coltemp = root->c;
    root->c=1;
    root->right->right->c=1;
    root = left_rotate(root);
    root->c = coltemp;
    return root;
}
struct colorNode* case1_2_left(struct colorNode* root){
    printf("case 1 2 l\n");
    (root->left)->extrablack=0; 
    int coltemp = root->c;
    root->c=1;
    root->right->right->c=1;
    root = left_rotate(root);
    root->c = coltemp;
    return root;
}
struct colorNode* case1_3_left(struct colorNode* root){
    printf("case 1 3 l\n");
    (root->right)->c = 0;
    ((root->right)->left)->c = 1;
    root->right = right_rotate(root->right);
    return case1_1_left(root);
}
struct colorNode* case1_4_left(struct colorNode* root){
    printf("case 1 4 l\n");
    (root->right)->c = 0;
    (root->left)->extrablack = 0;
    root->extrablack = 1;
    return root;
}