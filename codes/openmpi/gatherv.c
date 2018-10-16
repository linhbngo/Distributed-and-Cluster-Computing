#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int rank, size;    
    int i; 
    int recvcounts[4] = {1,2,3,4}; /* process 0 will receive from each process that process rank */
                                   /* plus 1 numbers */
    int displs[4] = {0,0,0,0}; /* array describing the displacements where each segment begins and is initialized to all 0s */
    int *sendbuf; /* the buffer to be sent. will be initialized individually at each process */
    int *recvbuf; /* arrayto receive data. will only be initialized at process 0*/

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* initializes recvbuf to receive 10 numbers */
    if (rank == 0){
      recvbuf = malloc(sizeof(int) * (10));
    }
    
    /* initializes sendbuf to receive 10 numbers */
    sendbuf = malloc(sizeof(int) * (rank + 1));
    for (i = 0; i < (rank + 1); i++){
        sendbuf[i] = rank;
    }
    
    // calculate displacements
    for (i = 1; i < 4; i++) {
        displs[i] = displs[i-1] + recvcounts[i-1];
    }

    // divide the data among processes as described by sendcounts and displs
    MPI_Gatherv(sendbuf, rank + 1, MPI_INT, recvbuf, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    // print what process has at the end
    if (rank == 0){
      for (i = 0; i < 10; i++) {
        printf("%d ", recvbuf[i]);
      }
      printf("\n");
      free(recvbuf);
    }
    MPI_Finalize();
    return 0;
}