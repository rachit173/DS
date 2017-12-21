#include "disjoint_set.h"

int main(){
    int q;
    scanf("%d",&q);
    int t;
    int x,y;
    for(int i=0;i<q;i++){
        scanf("%d",&t);
        if(t==0){
            //make set
            // here x is the satelite data
            scanf("%d",&x);
            make_set(x);
        }
        else if(t==1){
            //find set
            //give the key not the satellite data for find set
            scanf("%d",&x);
            printf("%d",find_set(x));
        }
        else {
            //union of two sets
            scanf("%d %d",&x,&y);
            uni(x,y);
        }
    }
}