#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main(int argv,char* argc[]){
    clock_t start,end;          //setting a variables 
    srand(time(NULL));          //seeding the random function 
    double cpu_time_used;
    int NUM_POINTS=argv-1;      //number of values of n to test for
    int NUM_COMMANDS=2;         //commands for the gnuplot function
    char *commandsForGnuplot[]={"set title \"TITLE\"","plot 'data1.temp' with lines lw 5"};  //list of commands for the gnuplot function
    double xval[NUM_POINTS];      //data points for the x axis of the plot(n)
    double yval[NUM_POINTS];      //data points for the y axis of the plot(time taken)
    for(int j=1;j<argv;j++){
        start=clock();
        int n=atoi(argc[j]);
        xval[j-1]=n;
        int q=10000;
        double a[n];
        //random initialisation of array of size n
        for(int i=0;i<n;i++){
          a[i]=rand()/10000.0;  
        }
        double fintime=0;
        //5 test cases for each value of n 
        for(int k=0;k<5;k++)
        {
          for(int i=0;i<q;i++){            //processing the queries
            double t=rand()/10000.0;
            int opt=0;
            for(int j=0;j<n;j++) if(a[j]==t) {opt=1;break;} //if the condition becomes true then we have found the query
            if(opt==0) continue; // not found
          }
          end=clock();
          //find the time for each test case
          cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC; 
          fintime+=cpu_time_used;
        }
        //average time for all the test cases
        fintime/=5.0;
        yval[j-1]=fintime;
    }
    //open the file to store the data for plotting the issue of commands
    FILE * temp = fopen("data1.temp","w");
    //open the pipeline of gnuplot for 
    FILE * gnuplotPipe = popen("gnuplot -persistent","w");
    //print data to the temporary data file
    for(int i=0;i<NUM_POINTS;i++)
    {
        fprintf(temp, "%lf %lf \n", xval[i], yval[i]); //Write the data to a temporary file
    }
    ////fclose('data1.temp');
    for (int i=0; i < NUM_COMMANDS; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
  return 0;
}
