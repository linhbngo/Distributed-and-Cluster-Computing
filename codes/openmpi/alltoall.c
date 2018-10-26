#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc,char *argv[]){
  int rank, size;
  int *sray,*rray;
  int *sdisp,*scounts,*rdisp,*rcounts;
  int ssize,rsize,i,k,j;
  float z;

  MPI_Init(&argc,&argv);
  MPI_Comm_size( MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
  scounts=(int*)malloc(sizeof(int)*size);
  rcounts=(int*)malloc(sizeof(int)*size);
  sdisp=(int*)malloc(sizeof(int)*size);
  rdisp=(int*)malloc(sizeof(int)*size);

  z = (float) rand() / RAND_MAX;
    
  for(i=0; i < size; i++){
    scounts[i]= rank * i + i;
  }
  
  printf("myid = %d scounts = ",rank);
  for(i=0;i<size;i++)
    printf("%d ",scounts[i]);
  printf("\n");

  /* send the data */
  MPI_Alltoall(scounts,1,MPI_INT,rcounts,1,MPI_INT,MPI_COMM_WORLD);
  printf("myid = %d rcounts = ",rank);
  for(i=0;i<size;i++)
    printf("%d ",rcounts[i]);
  printf("\n");
  MPI_Finalize();
}