#include<stdlib.h>
#include<stdio.h>
#include<time.h>
struct colorNode{
    int val;
    int c;      //c carry 0 is red and 1 is black.
    int leaf;
    int extrablack;
    struct colorNode* left;
    struct colorNode* right;
}colorNode;
struct colorNode* new1();
int check_leaf(struct colorNode* );
struct colorNode* queue1[100005];
struct colorNode* queue2[100005];   //queue for level order traveral
void LevelOrderTraversal(struct colorNode* );
void fun(struct colorNode* );
struct colorNode* left_rotate(struct colorNode* );
struct colorNode* right_rotate(struct colorNode* );
struct colorNode* insert(struct colorNode* ,int );
int leftmostInRightSubtree(struct colorNode* );
struct colorNode* case1_1_left(struct colorNode* );
struct colorNode* case1_2_left(struct colorNode* );
struct colorNode* case1_3_left(struct colorNode* );
struct colorNode* case1_4_left(struct colorNode* );
struct colorNode* case1_1_right(struct colorNode* );
struct colorNode* case1_2_right(struct colorNode* );
struct colorNode* case1_3_right(struct colorNode* );
struct colorNode* case1_4_right(struct colorNode* );
struct colorNode* case1_left(struct colorNode* );
struct colorNode* case1_right(struct colorNode*);
struct colorNode* del(struct colorNode* ,int );
struct colorNode* delfin(struct colorNode* ,int );
int search(struct colorNode* ,int );