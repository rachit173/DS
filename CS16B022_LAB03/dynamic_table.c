#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int size;       //size of the global array
int top_element=0;  //index of the next element to if inserted
int *arr;           //array pointer
int *tmparr;        //array pointer for temporarily copying values
void insert(int num)
{
  if(top_element<size)      //if the array is not full isert the element at the top
  {      
    arr[top_element++]=num;       //inserting the top element
  }
  else
  {
    tmparr=(int *)malloc(2*size*sizeof(int));   //allocate memory for array of double size
    for(int i=0;i<size;i++) tmparr[i]=arr[i];   //copy previous element to new memory space
    //if(size>4);
    free(arr);                                  //free memory of previous array
    size=size*2;                                //update the size of the primary array
    arr=tmparr;                                 
    arr[top_element++]=num;                     //insert the new element
  }
}
void delete(){
  if(top_element==0) {insert(1);return;}        //if there are no elements to be deleted
                                                //insert an element
  top_element--;                                //delete an element from the top otherewise
  if(top_element<=4) return ;                   //if the size of the main array <4
                                                //no need to halve the size
  if(top_element>size/4) return ;               //check if the number of elements
                                                //in the array are more than size/4
  else{                                         //if not
    tmparr=(int *)malloc(sizeof(int)*(size/2));             //allocate memory space half the size of current array
    for(int i=0;i<top_element;i++) tmparr[i]=arr[i];        //copy the elements to the new memoryspace
    free(arr);                                              //free the original memory space
    arr=tmparr;                                             //now the main array pointer is the new array
    size=size/2;                                            //update the size variable to current size of array
  }
}
int main(int argc,char *argv[]){
  int q;  
  int c;
  int num;
  srand(time(NULL));                        //seed the rand() function
  FILE *f=fopen("data.temp","w");           //file pointer open
  clock_t start,end;                        
  for(int i=1;i<argc;i++){
    start=clock();
    q=atoi(argv[i]);
   // printf();
    free(arr);
    arr=(int *)malloc(4*sizeof(int));
    size=4;
    top_element=0;
    int query=q;
    while(q--){                               //generating random queries
      c = rand()%100;
      c = (c/60)^1;    
      if(c==1){
        num=rand();                           //random number for insertion
        insert(num);                           //call the insert function        
  //      printf("%d\n",size);
      }
      else delete();                            //call the delete function
      //else assert(false);
    }
    end=clock();
    fprintf(f,"%lf %lf\n",(double)query,(double)(end-start)/(CLOCKS_PER_SEC)); //print the time taken for number of queries for n number of queries
  }
  fclose(f);
return 0;
}
