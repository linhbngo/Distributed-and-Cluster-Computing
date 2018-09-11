#include <stdio.h>
#include <sys/utsname.h>
#include <mpi.h>
int main(int argc, char *argv[]){
  MPI_Init(&argc, &argv);
  struct utsname uts;
  uname (&uts);
  printf("My process is on node %s.\n", uts.nodename);
  MPI_Finalize();
  return 0;
}