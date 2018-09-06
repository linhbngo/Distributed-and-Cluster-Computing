#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int size;
  int my_rank; 
  int sendbuf[2];
  int recvbuf[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
  int i;
    
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  for (i = 0; i < 2; i++){
    sendbuf[i] = my_rank;
  }
  MPI_Gather(&sendbuf, 2, MPI_INT, &recvbuf, 2, MPI_INT, 0, MPI_COMM_WORLD); 
  for (i = 0; i < 8; i++){
    printf ("Process %d has element %d at index %d in its recvbuf \n",
               my_rank, recvbuf[i], i);
  }

  /* Finalize the MPI environment. */
  MPI_Finalize();
}