#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SEND 1
#define STOP 0

float f(float x);

main(int argc, char** argv) {
  int rank;     /* rank of each MPI process */
  int size;     /* total number of MPI processes */
  double a, b;  /* default left and right endpoints of the interval */
  int n;        /* total number of trapezoids */
  double h;        /* height of the trapezoids */
  double param[3]; /* array containing end points and height for each individual trapezoid
                      for communication purpose */
  double local_result = 0.0;  /* area of each individual trapezoid */
  double partial_result = 0.0; /* amount of area calculated by each process */
  double result = 0.0;     /* Total integral            */
  int source;    /* Process sending the partial integral  */
  int dest = 0;  /* All messages go to 0      */
  int tag = 0;
  double start, stop, tpar, tcomm;
  int i,count, partial_count;
  MPI_Status  status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
    start = MPI_Wtime();

  /* initial job distribution is handled only by process 0 */
  if (rank == 0){
    a = atof(argv[1]);               
    b = atof(argv[2]);               
    n = atoi(argv[3]);              
    h = (b-a)/n;    
    count = 0;
    /* send out the first round of work assignment, incrementing count as needed */
    for (i = 1; i < size; i++){
      param[0] = a + count * h;
      param[1] = param[0] + h;
      param[2] = h;
      MPI_Send(param,3,MPI_DOUBLE,i,SEND,MPI_COMM_WORLD);
      count = count + 1;
    }
  }
  else {
    MPI_Recv(param,3,MPI_DOUBLE,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
  }
    
  tpar = 0.0;
  tcomm = 0.0;
  partial_count = 0; 
  /* Each process that is not process 0 works on its portion, send the partial result back to 0, 
   * and wait for new workload unless the TAG of the message is 0 
   */
  if (rank != 0){
    do {
      start = MPI_Wtime();
      local_result = param[2] * (f(param[1]) +  f(param[0])) / 2;
      partial_result += local_result;
      stop = MPI_Wtime(); 
      tpar += stop - start;
      partial_count += 1;
      start = MPI_Wtime();
      MPI_Send(&local_result,1,MPI_DOUBLE,0,SEND,MPI_COMM_WORLD);      
      MPI_Recv(param,3,MPI_DOUBLE,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
      stop = MPI_Wtime();
      tcomm += stop - start;
    } while(status.MPI_TAG != 0);
    printf("Process %d uses %lfs to calculate partial result %lf of %d portions and %lfs for communication \n", rank, tpar, partial_result, partial_count, tcomm);
  }
  

  /* Process 0 receives results and sends out work while there is still work left to be sent
   * (count < n) */
  if (rank == 0) {
    do {
      MPI_Recv(&local_result,1,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
      result = result + local_result;    
      param[0] = a + count * h;
      param[1] = param[0] + h;
      param[2] = h;
      MPI_Send(param,3,MPI_DOUBLE,status.MPI_SOURCE,SEND,MPI_COMM_WORLD); 
      count = count + 1; 
    }   
    while (count < n);  

    /* Make sure that we receive everything */
    for (i = 0; i < (size - 1); i++){
      MPI_Recv(&local_result,1,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
      result = result + local_result;  
    } 
  }

  /* All the work has been sent, */
  if (rank == 0){
    for (i = 1; i < size; i++){
      MPI_Send(param,3,MPI_DOUBLE,i,STOP,MPI_COMM_WORLD);
    }
  }

    /* Print the result */
    if (rank == 0) {
        printf("With n = %d trapezoids, our estimate\n",
            n);
        printf("of the integral from %f to %f = %f\n",
            a, b, result);
    }

    /* Shut down MPI */
    MPI_Finalize();
} /*  main  */

float f(float x) {
    return ( x*x );
} 