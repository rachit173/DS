Name : 		Rachit Tibrewal
Roll Number: 	cs16b022
1.File lab01a.c contains the first program
	to run it use 
	./a.out n q
	where n is the number of elements in the array
	and q is the nu,mber of queries
2.File lab01b.c contains the second program
	to run it use
	./a.out n q
	where n is the number of elements in the array
	and q is the nu,mber of queries
3.File lab01c1.c contains the third program which 
	is to plot a graph between time taken to process 10000
	queries on an integer array of size n as n increases
	to run it
	./a.out n1 n2 .....nk
	where ni's are the value of sizes of array you want a plot for
	example : ./a.out 512 1024 2048 4196 8382 16764
4.File lab01c2.c contains the third program which 
	is to plot a graph between time taken to process 10000
	queries on an floating value array of size n as n increases
	to run it
	./a.out n1 n2 .....nk
	where ni's are the value of sizes of array you want a plot for
	example : ./a.out 512 1024 2048 4196 8382 16764
5.To plot a simultaneous graph for floating point array and integer value array
	1.First do step 3 and 4 as it creates files data.temp and data1.temp which contain
	data points for two plots.
	2.Open gnuplot int terminal by typing gnuplot
	3.It opens gnuplot in bash.
	4.Now type
	gnuplot>plot 'data.temp' with lines,'data1.temp' with lines
