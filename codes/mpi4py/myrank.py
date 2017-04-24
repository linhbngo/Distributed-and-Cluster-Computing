from mpi4py import MPI
rank = MPI.COMM_WORLD.Get_rank()
size = MPI.COMM_WORLD.Get_size()

if rank == 0:
  print ("This is process %s" % (rank))
if rank == 1:
  print ("I am not the first process, and there are %s processes" % (size))
if rank == 2:
  print ("I rank last")
