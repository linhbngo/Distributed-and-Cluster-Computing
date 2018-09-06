#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int size;
  int my_rank; 
  int A[16] = {2,13,4,3,5,1,0,12,10,8,7,9,11,6,15,14};
  int i;
    
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  for (i = 0; i < 16; i++){
    if (i % size == my_rank){
      printf ("Process %d has elements %d at index %d \n",
               my_rank, A[i], i);
    }
  }

  /* Finalize the MPI environment. */
  MPI_Finalize();
}