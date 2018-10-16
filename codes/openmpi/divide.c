#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char * argv[] ) {
  int rank;     /* rank of each MPI process */
  int size;     /* total number of MPI processes */
  int i;        /* counter */
  int distance; /* distance between sender and receiver */
    
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
    
  /* Am I sender or receiver? */
  /* Who am I sending/receiving to/from */
  distance = 1;
  i = 0;
  while (distance <= size / 2){      
    if (rank < distance) {
      printf ("At iteration %d, sender %d sends to %d\n", i, rank, rank + distance);
    }
    if ((rank >= distance) && (rank < distance * 2)){
      printf ("At iteration %d, receiver %d receives from %d\n", i, rank, rank - distance);
    }
    distance = distance * 2;
    i += 1;
  }
    
  MPI_Finalize();
  return 0;  
}