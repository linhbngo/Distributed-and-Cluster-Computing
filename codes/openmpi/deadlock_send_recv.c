#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) 
{
  int my_rank;       /* rank of process     */
  int size;             /* number of processes */
  int source;        /* rank of sender      */
  int dest;          /* rank of receiver    */

  int tag=0;         /* tag for messages    */
  char message[100]; /* storage for message */
  MPI_Status status; /* return status for receive */

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  fprintf(stderr,"I am here!  ID = %d\n", my_rank);
  sprintf(message, "Greetings from process %d!", my_rank);

  if (my_rank == 0) {
    dest = 1;
    MPI_Recv(message, 100, MPI_CHAR, dest, tag, MPI_COMM_WORLD, &status);
    MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    printf("Process 0 printing:  %s\n", message);
  }
  else { 
    /* my rank == 1 */
    dest = 0;
    MPI_Recv(message, 100, MPI_CHAR, dest, tag, MPI_COMM_WORLD, &status);
    MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    printf("Process 1 printing:  %s\n", message);
  }
  
  MPI_Finalize();
} /* end main */