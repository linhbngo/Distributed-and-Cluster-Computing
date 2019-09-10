#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) 
{
  int my_rank;       
  int size;             
  int tag=0;
  int buf,i;
  int des, src;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  buf = my_rank; 

  printf("Process %2d has original value %2d \n",my_rank,buf);
    
  des = (my_rank + 1) % size;
  src = (my_rank + size - 1) % size;
  printf("Process %2d has des %2d and src %2d\n",my_rank,des,src);
    
  /* shift the data n/2 steps */
  for (i = 0; i < size/2; i++){
    MPI_Send(&buf,1,MPI_INT,des,tag,MPI_COMM_WORLD);
    MPI_Recv(&buf,1,MPI_INT,src,tag,MPI_COMM_WORLD,&status);
  }
  
  printf("Process %2d now has value %2d\n",my_rank,buf);

  /* Shut down MPI */
  MPI_Finalize();
}
