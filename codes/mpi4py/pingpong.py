import mpi4py
mpi4py.rc.recv_mprobe = False 

from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

if (rank == 0):
  counter = 0
  for i in range(0, 100):
    comm.send(counter, dest=1)
    counter = comm.recv(source = 1)
  print ("Final count is %s " % (counter))

if (rank == 1):
  for i in range(0, 100):
    X = comm.recv(source=0)
    X = X + 1
    comm.send(X, dest=0)
