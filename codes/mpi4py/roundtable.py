import mpi4py
mpi4py.rc.recv_mprobe = False 
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
sum = 0
tmp = rank
for i in range(0,size):  
  if (rank == (size - 1)):
    des = 0
  else:
    des = rank + 1  
  comm.send(tmp, dest=des)
  if (rank == 0):
    src = size - 1
  else:
    src = rank - 1
  tmp = comm.recv(source=src)
  print ("process %s receives %s from process %s" % (rank, tmp, des))
  sum += tmp
print ("Process %s has final sum is %s" % (rank, sum))
