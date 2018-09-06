#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) 
{
  int my_rank;       
  int size;
  int value;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
  
  value = my_rank;
  printf("process %d: Before MPI_Bcast, value is %d\n", my_rank, value); 

  MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
  printf("process %d: After MPI_Bcast, value is %d\n", my_rank, value);

  MPI_Finalize();
  return 0;
}