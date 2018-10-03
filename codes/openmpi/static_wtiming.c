/*
 * MPI implementation of the trapezoid approach to integral calculation following a static
 * workload distribution and standard send()/recv() calls. 
 * We assume that the number of trapezoids is divisible by the number of MPI process. 
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

double Trap(double a, double b, int n);
double f(double x);

int main(int argc, char * argv[] ) {
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
  int p;        /* counter */
  MPI_Status status;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  a = atof(argv[1]);
  b = atof(argv[2]);
  n = atoi(argv[3]);

  // calculate work interval for each process
  start = MPI_Wtime();
  h = (b - a) / n;
  local_n = n / size;
  local_a = a + rank * local_n * h;
  local_b = local_a + local_n * h;
  local_result = Trap(local_a,local_b,local_n);
  stop = MPI_Wtime();
  tpar = stop - start;

  printf("Process %d uses %lfs to calculate partial result %lf\n", rank, tpar, local_result);

  // sending the results back to the master
  start = MPI_Wtime();
  if (rank == 0){
    result = local_result;
    for (p = 1; p < size; p++){
      MPI_Recv(&local_result,1,MPI_DOUBLE,p,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
      result += local_result;
    }
  } 
  else{
    MPI_Send(&local_result,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);  
  }
  stop  = MPI_Wtime();
  tcomm = stop - start;

  // displaying output at the master node
  if (rank == 0){
    printf("Calculating the integral of f(x) from %lf to %lf\n", a, b);
    printf("The integral is %lf\n", result);  
    printf("Communication time: %.5fs\n",tcomm);
  }
  MPI_Finalize();
}

double Trap(double a, double b, int n) {
  double len, area;
  double x;
  int i;
  len = (b - a) / n;
  area = 0.5 * (f(a) + f(b));
  x = a + len;
  for (i=1; i<n; i++) {
    area = area + f(x);
    x = x + len;
  }
  area = area * len;
  return area;
}

double f(double x) {
  return ( x*x );
}