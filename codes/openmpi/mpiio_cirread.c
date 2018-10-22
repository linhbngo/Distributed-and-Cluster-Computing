
#include "mpi.h"
#include <stdio.h>
#define array_size 4

static char filename[] = "output.dat"; 

main(int argc, char **argv)
{
  int rank, size;
  MPI_File infile;
  MPI_Status status;
  MPI_Datatype arraytype;

  int nbytes, myarray[array_size], mode, i;
  double start, stop;

  /* initialize MPI */
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  MPI_Type_vector(array_size, 1, size*array_size, MPI_INT, &arraytype);
  MPI_Type_commit(&arraytype);
    
  /* open file */
  mode = MPI_MODE_RDONLY;

  MPI_File_open( MPI_COMM_WORLD, filename, mode, MPI_INFO_NULL, &infile );

  /* set file view */
  MPI_File_set_view( infile, rank*sizeof(MPI_INT), MPI_INT, arraytype, "native", MPI_INFO_NULL );

  /*  read file */
  MPI_File_read( infile, &myarray[0], array_size, MPI_INT, &status );


  /* close file */
  MPI_File_close( &infile );

  /* print out results */
  for (i=0; i < array_size; i++) 
    printf("%2d%c", myarray[i], i%4==3 ? '\n' : ' ');

  /* finalize MPI */
  MPI_Finalize();
}