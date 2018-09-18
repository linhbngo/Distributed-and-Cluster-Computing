#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) 
{
  int my_rank;       
  int size;             
  int tag=0;
  int buf,i;
  int des1,des2;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  /*  set up data */
  buf = my_rank; 

  //printf("Process %2d has original value %2d \n",my_rank,buf);
    
  /* set up source and destination */
  des1 = (my_rank + 1) % size;
  des2 = (my_rank + size - 1) % size;
  //printf("Process %2d has des1 %2d and des2 %2d\n",my_rank,des1,des2);
    
  /* shift the data n/2 steps */
  for (i = 0; i < size/2; i++){
    MPI_Send(&buf,1,MPI_INT,des1,tag,MPI_COMM_WORLD);
    MPI_Recv(&buf,1,MPI_INT,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD,&status);
    MPI_Barrier(MPI_COMM_WORLD);
  }

  MPI_Send(&buf,1,MPI_INT,des2,tag,MPI_COMM_WORLD);
  MPI_Recv(&buf,1,MPI_INT,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD,&status);
  
  MPI_Barrier(MPI_COMM_WORLD);
  printf("Process %2d now has value %2d\n",my_rank,buf);

  /* Shut down MPI */
  MPI_Finalize();

} /* end main */