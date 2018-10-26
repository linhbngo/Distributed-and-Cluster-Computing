#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <math.h>

int main(int argc, char** argv){
  int rank, size;
  MPI_Status status;
  int local_sum, tmp;
  int i, iter;
  int distance;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  local_sum = rank;
  tmp = 0;

  iter = log(size) / log(2);
  printf("Process %d has prefix sum %d\n", rank, local_sum);
  MPI_Barrier(MPI_COMM_WORLD);
  for (i = 0; i < iter; i++){
    distance = pow(2,i);

    if (rank == 0){
      printf("iter %d and distance %d\n", i, distance);
    }      
    if (rank < (size - distance)){
      MPI_Send(&local_sum, 1, MPI_INT, rank + distance, 0, MPI_COMM_WORLD);
      printf("%d send to %d value %d\n",rank, rank+distance, local_sum);

    }
    if (rank >= distance){
      printf("%d receive from %d \n", rank, rank - distance);
      MPI_Recv(&tmp, 1, MPI_INT, rank - distance, 0, MPI_COMM_WORLD, &status);
      printf("%d receive from %d value %d\n",rank, rank-distance, tmp);
      local_sum += tmp;
    }
    printf("Process %d has prefix sum %d\n", rank, local_sum);
    MPI_Barrier(MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}