#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 32

int main(int argc, char* argv[]){

  int rank,size;
  MPI_Status status;

  int rawNum[N];
  int sortNum[N];
  int* local_array;

  int i,j;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  // initialize the unsorted array at process 0
  if (rank == 0){
    for (i = 0; i < N; i++){
      rawNum[i] = rand() % N;
    }
  }

  // prepare the local container, then distribution equal portions of the
  // unsorted array to all the processes from process 0
  local_array = malloc((N/size) * sizeof(int));
  MPI_Scatter(rawNum,(N/size),MPI_INT,local_array,(N/size),MPI_INT,0,MPI_COMM_WORLD);

  // initialize the local bucket matrix
  int local_bucket[size][N/size];
  for (i = 0; i < size; i++){
    for (j = 0; j < N/size; j++){
      local_bucket[i][j] = RAND_MAX;
    }
  }

  int counter = 0;
  int local_min,local_max;
 // populate the bucket matrix
  for (i = 0; i < size; i++){
    counter = 0;
    for (j = 0; j < N/size; j++){
      local_min = i * N/size;
      local_max = (i + 1) * N / size;
      if ((local_array[j] >= local_min)&&(local_array[j] < local_max)){
        local_bucket[i][counter] = local_array[j];
        counter += 1;
      }
    }
  }

  // sort the bucket matrix. 
  int tmp = 0;
  for (i = 0; i < size; i++){
    for (j = 0; j < N/size; j++){
      for (counter = j; counter < N/size; counter++){
        if (local_bucket[i][j] > local_bucket[i][counter]){
          tmp = local_bucket[i][j];
          local_bucket[i][j] = local_bucket[i][counter];
          local_bucket[i][counter] = tmp;
        }
      }
    }
  }

  // placing the number from the buckets back into the main array
  counter = 0;
  int array_counter[size];
  for (i = 0; i < size; i++){
    for (j = 0; j < N/size; j++){
      if (local_bucket[i][j] != RAND_MAX){
        local_array[counter] = local_bucket[i][j];
        counter += 1;
      }
      else {
        array_counter[i] = j;
        printf("Rank %d counter %d \n",rank,array_counter[i]);
        break;
      }
    }
  }
 /*
  for (i = 0; i < N/size; i++){
    printf("rank %d sorted num %d \n",rank,local_array[i]);
  }
  */

  if (rank == 0)  printf("-----------------\n");
  MPI_Barrier(MPI_COMM_WORLD);

  // preparation for bucket gathering
  int recvbuf[size];
  int rdisp[size];
  int sdisp[size];

  sdisp[0] = 0;
  for (i = 0; i < size - 1; i++){
    sdisp[i+1] = sdisp[i] + array_counter[i];
    printf("%d send displace %d \n",rank,sdisp[i+1]);
  }

  MPI_Alltoall(array_counter,1,MPI_INT,recvbuf,1,MPI_INT,MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);

  int sum = 0;
  for (i = 0; i < size; i++){
    sum += recvbuf[i];
    printf("rank %d recvbuf %d \n",rank,recvbuf[i]);
  }

  printf("rank %d total recv buf %d \n", rank,sum);

  MPI_Barrier(MPI_COMM_WORLD);

  rdisp[0] = 0;
  for (i = 0; i < size - 1; i++){
    rdisp[i+1] = rdisp[i] + recvbuf[i];
    printf("%d recv displace %d \n",rank,rdisp[i+1]);
  }

  int local_array_alltoall[sum];
  // initialize local_array_alltoall for testing purpose
  for (i = 0; i < sum; i++) local_array_alltoall[i] = -1;
  MPI_Alltoallv(local_array,array_counter,sdisp,MPI_INT,local_array_alltoall,recvbuf,rdisp,MPI_INT,MPI_COMM_WORLD);

  for (i = 0; i < sum; i++){
    printf("rank %d semi-sorted num %d \n",rank,local_array_alltoall[i]);
  }


  // local sort on big bucket one more time
  for (i = 0; i < sum; i++){
    for (j = i; j < sum; j++){
      if (local_array_alltoall[i] > local_array_alltoall[j]){
        tmp = local_array_alltoall[i];
        local_array_alltoall[i] = local_array_alltoall[j];
        local_array_alltoall[j] = tmp;
      }
    }
  }

  // preparation for the final gathering
  int proc_count[size];
  int disp[size];


  MPI_Gather(&sum,1,MPI_INT,proc_count,1,MPI_INT,0,MPI_COMM_WORLD);

  if (rank == 0){
    disp[0] = 0;
    for (i = 0; i < size-1; i++){
      disp[i+1] = disp[i] + proc_count[i];
    }
  }

  MPI_Gatherv(local_array_alltoall,sum,MPI_INT,sortNum,proc_count,disp,MPI_INT,0,MPI_COMM_WORLD);

  if (rank == 0){
    printf("Before sort: \n");
    for (i = 0; i < N; i++) printf("%d ",rawNum[i]);
    printf("\nAfter sort: \n");
    for (i = 0; i < N; i++) printf("%d ",sortNum[i]);
  }
MPI_Finalize();
  return 0;
}