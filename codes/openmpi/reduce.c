#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int size;
  int my_rank; 
  int rank_sum;
  int i;
    
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  
  rank_sum = my_rank;

  MPI_Reduce(&my_rank, &rank_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 
  printf ("The total sum of all ranks at process %d is %d \n", my_rank, rank_sum);

  /* Finalize the MPI environment. */
  MPI_Finalize();
}