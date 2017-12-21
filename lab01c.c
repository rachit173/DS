#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main(int argv,char* argc[]){
    clock_t start,end;
    double cpu_time_used;
    srand(time(NULL));
    int NUM_POINTS=argv-1;
    int NUM_COMMANDS=2;
    char *commandsForGnuplot[]={"set title \"Search\"","plot 'data.temp' with lines"};
    double xval[NUM_POINTS];
    double yval[NUM_POINTS];
    for(int j=1;j<argv;j++){      //the number of values of n
        start=clock();
        int n=atoi(argc[j]);      
        int q=10000;              //10000 queries for each value of n
                                  //and the time taken averaged over 5
                                  //trials
        int a[n];
        for(int i=0;i<n;i++){     //random initialisation of the array
          a[i]=rand();  
        }
        double fintime=0;   
        for(int k=0;k<5;k++){
            for(int i=0;i<q;i++){            //processing the queries
              int t=rand();
              int opt=0;
              for(int j=0;j<n;j++)  
                if(a[j]==t) 
                   {
                    opt=1;
                    break;
                    } //if the condition becomes true then we have found the query
              if(opt==0) continue; // not found
            }
          end=clock();
          cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC; 
          fintime+=cpu_time_used;
        }
        fintime/=5.0; 
        //storing the data points
        xval[j-1]=n;      
        yval[j-1]=fintime;
    }
    FILE * temp = fopen("data.temp","w");       //'data.temp' is the file in which the data points for 
                                                //processing by gnuplot are stored
    FILE * gnuplotPipe = popen("gnuplot -persistent","w");
    for(int i=0;i<NUM_POINTS;i++){
        fprintf(temp, "%lf %lf \n", xval[i], yval[i]); //Write the data to a temporary file
    }

    for (int i=0; i < NUM_COMMANDS; i++)
    {
      fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
  return 0;
}
