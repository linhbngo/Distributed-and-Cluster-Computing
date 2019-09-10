#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) 
{
  int my_rank;       
  int size;             
  int tag=0;
  int buf,i;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  buf = my_rank; 

  printf("Process %2d has original value %2d \n",my_rank,buf);
    
  if (my_rank == 0){
    MPI_Send(&buf,1,MPI_INT,1,tag,MPI_COMM_WORLD);
    MPI_Recv(&buf,1,MPI_INT,1,tag,MPI_COMM_WORLD,&status);
  }
  
  if (my_rank == 1){
    MPI_Recv(&buf,1,MPI_INT,0,tag,MPI_COMM_WORLD,&status);
    MPI_Send(&buf,1,MPI_INT,0,tag,MPI_COMM_WORLD);  
  }    
  printf("Process %2d now has value %2d\n",my_rank,buf);

  MPI_Finalize();
}
