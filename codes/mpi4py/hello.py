#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int size;
  int my_rank; 
  char proc_name[MPI_MAX_PROCESSOR_NAME];
  int proc_name_len;
    
  /* Initialize the MPI environment */
  MPI_Init(&argc, &argv);
  
  /* Get the number of processes */
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  /* Get the rank of the process */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  /* Get the name of the processor */
  MPI_Get_processor_name(proc_name, &proc_name_len);

  /* Print off a hello world message */
  printf("Hello world from processor %s, rank %d out of %d processors\n",
           proc_name, my_rank, size);

  /* Finalize the MPI environment. */
  MPI_Finalize();
}