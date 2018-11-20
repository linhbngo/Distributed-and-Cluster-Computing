#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define array_size 512000000

static char filename[] = "output.dat";

main(int argc, char **argv)
{
  int rank, size, offset, local_size;
  MPI_File outfile;
  MPI_Status status;
  int nbytes, mode, i;
  int *myarray;

  /* initialize MPI */
  MPI_Init( &argc, &argv );
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  /* initialize array */
  local_size = array_size / size;
  myarray = malloc(local_size * sizeof(int));

  for (i=0; i < local_size; i++) {
    myarray[i] = rank;
  }

  /* open file */
  mode = MPI_MODE_CREATE | MPI_MODE_WRONLY;
  MPI_File_open(MPI_COMM_WORLD, filename, mode, MPI_INFO_NULL, &outfile);

  offset = rank * (array_size / size) * sizeof(int);

  /*  write buffer to file*/
  MPI_File_write_at(outfile, offset, myarray, local_size, MPI_INT, &status);

  /* print out number of bytes written */
  MPI_Get_elements(&status, MPI_CHAR, &nbytes);
  printf("TASK %d wrote %d bytes\n", rank, nbytes);

  /* close file */
  MPI_File_close( &outfile );

  MPI_Barrier(MPI_COMM_WORLD);



  /* finalize MPI */
  MPI_Finalize();

  return 0;
}
