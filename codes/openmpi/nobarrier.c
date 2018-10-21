#include <stdio.h>
#include <unistd.h>
#include <mpi.h>
int main(int argc, char *argv[]){
  int rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0){
    sleep(5);
  }
  printf("Process %d is awake! \n", rank);
  MPI_Finalize();
  return 0;
}