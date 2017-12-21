//Question 
//Invariant Property
//If M is free then it must belong to EXACTLY one of the holes
//IF M is allocated tehn it must belong to one of the heaps
//
//i
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 1000
#define MAX_SIZE_KEYS 10000
void memsnap(void);
int a[MAX_SIZE+1];
static int global_key_num=0;
int key_store[MAX_SIZE_KEYS]; //initialised to -1 in main
int index_store[MAX_SIZE+1];      //initialised to -1 in main
int al[MAX_SIZE+1]={0};
int fl[MAX_SIZE+1]={0};
void defragment(){            //function for collection of free spaces
  //Here we defragment the free list
  //by jumping to the index in the free list 
  //that has the free memory
  //If the index in the next jump
  //variable i for accessing the free list
  int index=0;
  //var start for keeping record of the start of 
  //free memory chunk
  int start=0;              
  int continous_sum=0;
  while(index<MAX_SIZE){
    //check if the fl[i] is free
    if(fl[index]==0){
    //if it is not free then
    //it must be occupied 
    //so the next index to
    //check is given by
    index=index+al[index];
    }
    else{
    //if it is free then
    //considering this space to be start of the free space
    start=index;
    //add all successive continous free space chunks 
    //to this chunk
    continous_sum=0;
    while(index<MAX_SIZE&&fl[index]>0){
      int chunk_memory=fl[index];
      //add the free space of the continous
      //this will be total free space of the free chunks
      continous_sum+=chunk_memory;
      //free these chunks of their free space
      fl[index]=0;
      //moving to the next chunk
      index=index + chunk_memory;
    }
    //assigning the free space available
    //to the head chunk
    fl[start]=continous_sum;
    //index is already at the end+1 of the combined chunk
    }
  }
}
int garbage_collection(){
  //-------------------------------------------------------------------
  //Here we will first update the allocated list 
  //Based on the updated allocated list
  //free memory list will be formed
  //UPDATING the allocated list
  //1. the first allocated index must be
  //    shifted to 0-index
  //2. The the end of the previously allocated chunk which has 
  //  been shifted to start at 0-index
  //  will the starting point of the next allocated chunk
  //3.Repeating the above steps will stack the 
  //  allocated chinks one after the another
  //-------------------------------------------------------------------
  int start=0;
  int index=0;
  int used_memory=0;
  while(index<MAX_SIZE){
    if(al[index]==0) { 
      index++; 
      continue;
    }
    else{
      //printf("%d %d %d\n",start,index,al[index]);
      //The key to which the memory_chunk is assigned
        used_memory+=al[index];
        int key=index_store[index];
      //shifting the memory_chunk from index to start
        al[start]=al[index];
      // freeing the memory at index
        if(index>start) al[index]=0;
      //updating key_store
        key_store[key]=start;
      //updating index_store
        index_store[start]=key;
        index_store[index]=-1;
      //moving to end of the the current allocated list
        index=index+al[start];    //al[start] is just the memory of the chunk previously at index
      //update start
        start=start+al[start];
    }
  }
  //reseting the free memory list to 0
  memset(fl,0,sizeof(fl));
  //Registering the only free memory chunk the exist at the bottom
  //of the array in the free memory list
  //printf("memory used total: %d\n",used_memory);
  if(used_memory<MAX_SIZE) fl[used_memory]=MAX_SIZE-used_memory;
  //memsnap();
  return used_memory;
}
int request(const int mem){
  int index=0;                //iterator i for the free list which is defragmented
  ///The while is used to find the free list segment 
  //with the required memory 
  //and then allocate the free memory
  //and update the free list and allocated list
  //-------------------------------------------------------------------
  //defragment to combine continous chunks of free memory
  defragment();
    while(index<MAX_SIZE){
      if(fl[index]>=mem){
        //assigning the key for the user
        const int key=global_key_num;
        global_key_num++;
        //storing the index in the key
        //The key store acts as one to one mapping between
        //the unique key of an user and the index of their memory space
        key_store[key]=index;
        //---------------------------------------------------------------------
        //Now updating the mapping of indices to key
        //unmapped index will have a key value of -1
        index_store[index]=key;
        //updating the allocated list
        al[index]=mem;
        //updating the free list
        fl[index+mem]=fl[index]-mem;
        fl[index]=0;
        //printf("%d %d %d\n",index,fl[index+mem],al[index]);
        //returning the key
        return key;
      }
      index=index+fl[index]+al[index];
    }
    //if the request() fails to allocate memory returning error code -1
    //calling garbage_collection
    int start_of_freespace=garbage_collection();
    index=start_of_freespace;
    //while(index<MAX_SIZE) index=index+al[index];
    if(fl[index]>=mem){
      //assigning the key
      const int key=global_key_num;
      global_key_num++;
      //storing the key and the index
      key_store[key]=index;
      index_store[index]=key;
      //updating the allocated list
      al[index]=mem;
      //updating the free memory list
      fl[index+mem]=fl[index]-mem;
      fl[index]=0;
      return key;
    }
    //default case
    return -1;
}
void free_memory(int key){
  //the key is provided by user
  //to free the memory we need to update
  //1. allocated list
  //2. free list
  //-------------------------------------
  //finding the index from the key_store mapping
  int index=key_store[key];
  //finding the amount to be freed from the 
  //allocated list
  int memory_freed=al[index];
  //updating the allocated memory list
  al[index]=0;
  //updating the free memory list
  fl[index]=memory_freed;
  //updating the indices mapping as
  //the previously used index is now freed
  index_store[index]=-1;
  //updating the key_store 
  //the mapping of key in key_store
  //is now -1
  //defragmentation
  defragment();
}
void memsnap(){
    printf("allocated list:\n");
  //printf("[index\tmemory]\n");
  int k=0;
  for(int i=0;i<=MAX_SIZE;i++){
    if(al[i]>0){
      printf("%d %d %d\n",k++,i,al[i]);
    }
  }
  printf("free list\n");
  //printf("[index\tmemory]\n");
  k=0;
  for(int i=0;i<=MAX_SIZE;i++){
    if(fl[i]>0){
      printf("%d %d %d\n",k++,i,i+fl[i]-1);
    }
  }

}
int main(){
  //initialising the global array index_store to -1
  memset(index_store,-1,sizeof(index_store));
  //initialising the global array key_store to-1
  //string for input
  int c;
  int T;
  scanf("%d",&T);
  fl[0]=MAX_SIZE;
  //for(int i=0;i<100000;i++) a[i]=i;
  while(T--){
    scanf("%d",&c);
      if(c==1){
      int mem;
      scanf("%d",&mem);
      request(mem);
    }
    else if(c==2){
      int key;
      scanf("%d",&key);
      free_memory(key);
    }
  }
  memsnap();
  return 0;
}
  