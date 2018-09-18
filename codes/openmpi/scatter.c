#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int size;
  int my_rank; 
  int sendbuf[16] = {2,13,4,3,5,1,0,12,10,8,7,9,11,6,15,14};
  int recvbuf[5];
  int i;
    
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  MPI_Scatter(&sendbuf, 5, MPI_INT, &recvbuf, 5, MPI_INT, 0, MPI_COMM_WORLD); 
  for (i = 0; i < 5; i++){
    printf ("Process %d has element %d at index %d in its recvbuf \n",
               my_rank, recvbuf[i], i);
  }

  /* Finalize the MPI environment. */
  MPI_Finalize();
}