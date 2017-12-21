            struct colorNode* w = x->p->left; //w is the sibling of x
            //if the sibling w is of red color
            if(w->c==0){
                w->c=1;
                x->p->c=0;
                rightRotate(x->p);
                w = x->p->right;   //make the sibling to the right child of p[x]
            }
            if(w->right->c==1&&w->right->c==1){
                w->c=0;
                x = x->p;
            }
            else{ 
                if(w->right->c==1){
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