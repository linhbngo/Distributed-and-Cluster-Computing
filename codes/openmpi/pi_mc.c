#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

// Generate a random double representing an x coordinate in a given process's
// region of the square.
static inline double randomXInRegion(int rank, int squareWidth, double modifier) {
  return (double)rand() / ((double)RAND_MAX * squareWidth) + modifier;
}

// Generate a random double representing an y coordinate in a given process's
// region of the square.
static inline double randomYInRegion(int rank, int squareWidth, double modifier) {
  return (double)rand() / ((double)RAND_MAX * squareWidth) + modifier;
}

// Test to see if a given point lies within an imaginary unit circle.
static inline char pointInCircle(double x, double y) {
  return (x * x + y * y <= 1);
}

int main(int argc, char* argv[]) {

  long long int nPointsInCircle  = 0,
                i                = 0,
                nPointsTotal     = 0,
                nPointsPerRegion = 0,
                pointsReceived   = 0;
  double        piEstimate, runtime, x, y;
  int           rank, size, squareWidth;
  MPI_Status    status;

  // Argument parsing
  if (argc != 2) {
    printf("Usage: %s <number of points>\n", argv[0]);
    return 1;
  }
  nPointsTotal = strtoll(argv[1], NULL, 0);

  // Initialize MPI and related variables
  MPI_Init(&argc, &argv);
  runtime = MPI_Wtime();
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Seed RNG and make calculations for constants
  nPointsPerRegion = nPointsTotal / size;
  srand( (unsigned)time(NULL) + rank ); // seed differently per node
  squareWidth = (int)sqrt(size);

  // Place and record points in the circle
  double xmod = ((double)(rank % squareWidth) / squareWidth);
  double ymod = ((double)((int)(rank / squareWidth)) / squareWidth);
  for (i = 0; i < nPointsPerRegion; i++) {
    x = randomXInRegion(rank, squareWidth, xmod);
    y = randomYInRegion(rank, squareWidth, ymod);
    nPointsInCircle += pointInCircle(x, y);
  }

  if (rank == 0) {

    // The master process accepts points in the circle from slave processes
    for (i = 1; i < size; i++) {
      pointsReceived = 0;
      MPI_Recv(&pointsReceived, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      nPointsInCircle += pointsReceived;
    }

    // Calculate pi, runtime, and print results
    piEstimate = (double)(nPointsInCircle * 4) / nPointsTotal;
    runtime    = MPI_Wtime() - runtime;
    printf("%f, %f\n", piEstimate, runtime);

  } else {

    // Slave processes only send their contents to the master process.
    MPI_Send(&nPointsInCircle, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

  }

  MPI_Finalize();
  return 0;
}