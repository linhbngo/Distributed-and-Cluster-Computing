#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int my_rank; 
    
  /* Initialize the MPI environment */
  MPI_Init(&argc, &argv);

  /* Get the rank of the process */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank % 2 == 0) {
    printf ("Process %d is even \n", my_rank);
  } else {
    printf ("Process %d is odd \n", my_rank);
  }
  MPI_Finalize();
}