#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 64

int main(int argc, char* argv[]){

  int rawNum[N];
  int sortNum[N];
  int* local_bucket;
  int rank,size;
  int* proc_count;
  int* disp;
  MPI_Status status;
  int i,j,counter;
  int local_min,local_max;
  int tmp;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
    
  if (rank == 0){
    /* Initialize a random array with N integers whose values range between 0 and N */
    for (i = 0; i < N; i++){
      rawNum[i] = rand() % N;
    }
  }

  /* Broadcast contents of rawNum from 0 to all other processes */
  MPI_Bcast(rawNum, N, MPI_INT, 0, MPI_COMM_WORLD);

  /* Each process only works with numbers within their assigned interval */
  counter = 0;
  local_min = rank * (N/size);
  local_max = (rank + 1) * (N/size);  
  for (i = 0; i < N; i++){
    if ((rawNum[i] >= local_min) && (rawNum[i] < local_max)){
      counter += 1;
    }
  }    
    
  printf("For rank %d, max is %d, min is %d, and there are %d elements in rawNum that falls within max and min \n",
         rank,local_max,local_min,counter);


  /* Each process creates its own bucket containing values that fall within its interval */  
  local_bucket = malloc(counter * sizeof(int));
  counter = 0;
  for (i = 0; i < N; i++){
    if ((rawNum[i] >= local_min) && (rawNum[i] < local_max)){
      local_bucket[counter] = rawNum[i];
      counter += 1;
    }
  }

  /* Insertion sort */
  for (i = 0; i < counter; i++){
    for (j = i+1; j < counter; j++){
      if (local_bucket[i] > local_bucket[j]){
        tmp = local_bucket[i];
        local_bucket[i] = local_bucket[j];
        local_bucket[j] = tmp;
      }
    }
  }


  for (i = 0; i < counter; i++){
    printf("%d %d \n",rank,local_bucket[i]);
  }

  /* set up root process */
  if (rank == 0){
    proc_count = malloc(size * sizeof(int));
    disp = malloc(size * sizeof(int));
  }

  /* populate proc_count */
  MPI_Gather(&counter,1,MPI_INT,proc_count,1,MPI_INT,0,MPI_COMM_WORLD);

  if (rank == 0){
    disp[0] = 0;
    for (i = 0; i < size-1; i++){
      disp[i+1] = disp[i] + proc_count[i];
    }
  }

  // receive final result
  MPI_Gatherv(local_bucket,counter,MPI_INT,sortNum,proc_count,disp,MPI_INT,0,MPI_COMM_WORLD);

  if (rank == 0){
    printf("Before sort: \n");
    for (i = 0; i < N; i++) printf("%d ",rawNum[i]);
    printf("\nAfter sort: \n");
    for (i = 0; i < N; i++) printf("%d ",sortNum[i]);
  }

  MPI_Finalize();
  return 0;
}