
#include "mpi.h"
#include <stdio.h>
#define array_size 4

static char filename[] = "output.dat";

main(int argc, char **argv)
{
  int rank, size;
  MPI_File outfile;
  MPI_Status status;
  MPI_Datatype arraytype;
  int nbytes, myarray[array_size], mode, i;
  double start, stop, resolution;

  /* initialize MPI */
  MPI_Init( &argc, &argv );
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
    
  MPI_Type_vector(array_size, 1, size * array_size, MPI_INT, &arraytype);
  MPI_Type_commit(&arraytype);

  /* initialize array */
  for (i=0; i < array_size; i++) {
    myarray[i] = rank;
  }

  /* open file */
  mode = MPI_MODE_CREATE | MPI_MODE_WRONLY;
  MPI_File_open(MPI_COMM_WORLD, filename, mode, MPI_INFO_NULL, &outfile);

  /* set file view */
  MPI_File_set_view(outfile, rank * sizeof(MPI_INT), MPI_INT, arraytype, "native", MPI_INFO_NULL);

  /*  write buffer to file*/
  MPI_File_write(outfile, &myarray[0], array_size, MPI_INT, &status);    

  /* print out number of bytes written */
  MPI_Get_elements(&status, MPI_CHAR, &nbytes);
  printf("TASK %d wrote %d bytes\n", rank, nbytes);

  /* close file */
  MPI_File_close( &outfile );
    
  /* finalize MPI */
  MPI_Finalize();
    
  return 0;
}