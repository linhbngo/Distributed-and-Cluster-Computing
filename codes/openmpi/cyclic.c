#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

float f(float x);

main(int argc, char** argv) {
  int rank;     /* rank of each MPI process */
  int size;     /* total number of MPI processes */
  double a, b;  /* default left and right endpoints of the interval */
  int n;        /* total number of trapezoids */
  double h;        /* height of the trapezoids */
  double local_a, local_b; /* left and right endpoints on each MPI process */
  int local_n;  /* number of trapezoids assigned to each individual MPI process */
  double result;       /* final integration result */
  double local_result; /* partial integration result at each process */
  double start, stop, tpar, tcomm;  /* timing variables */
  int i;        /* counter */
  MPI_Status  status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  a = atof(argv[1]);               
  b = atof(argv[2]);              
  n = atoi(argv[3]);               
 
  // calculate work interval for each process
  start = MPI_Wtime(); 
  h = (b-a)/n;    /* height is the same for all processes */
  local_n = n/size;  /*  so is the number of trapezoids */

  /* Each process' interval starts at: */
  local_a = a + rank * h;
  local_b = local_a + h;
  local_result = 0;

  for (i = 0; i < n/size; i++){
    local_result = local_result + h * (f(local_a) +  f(local_b)) / 2;
    local_a += h * size;
    local_b = local_a + h;
  }
  stop = MPI_Wtime();
  tpar = stop - start;

  printf("Process %d uses %lfs to calculate partial result %lf\n", rank, tpar, local_result);
  
  // sending the results back to the master using reduce  
  start = MPI_Wtime();
  MPI_Reduce(&local_result, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  stop = MPI_Wtime();
  tcomm = stop - start;

  /* Print the result */
  if (rank == 0){
    printf("Calculating the integral of f(x) from %lf to %lf\n", a, b);
    printf("The integral is %lf\n", result);  
    printf("Communication time: %.5fs\n",tcomm);
  }
  MPI_Finalize();
}

float f(float x) {
    return ( x*x );
} 