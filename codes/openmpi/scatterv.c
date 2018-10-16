#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int rank, size;    
    int i; 
    int sendcounts[4] = {1,2,3,4}; /* each process will receive its rank plus 1 numbers from the sendbuf array */
    int displs[4] = {0,0,0,0}; /* array describing the displacements where each segment begins and is initialized to all 0s */
    int sendbuf[10] = {2,13,4,3,5,1,0,12,10,8}; /* the buffer to be sent */
    int *recvbuf; /* array at each process to receive data. To be initialized based on process rank */

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* initializes recvbuf to contain exactly rank plus 1 numbers */
    recvbuf = malloc(sizeof(int)* (rank + 1));
    
    // calculate displacements
    for (i = 1; i < 4; i++) {
        displs[i] = displs[i-1] + sendcounts[i-1];
    }

    // divide the data among processes as described by sendcounts and displs
    MPI_Scatterv(sendbuf, sendcounts, displs, MPI_INT, recvbuf, (rank + 1), MPI_INT, 0, MPI_COMM_WORLD);

    // print what each process received
    printf("%d: ", rank);
    for (i = 0; i < sendcounts[rank]; i++) {
        printf("%d ", recvbuf[i]);
    }
    printf("\n");
    
    free(recvbuf);

    MPI_Finalize();
    return 0;
}