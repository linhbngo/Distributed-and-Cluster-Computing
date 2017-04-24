import mpi4py
mpi4py.rc.recv_mprobe = False 
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
sum = 0
tmp = rank

if (rank == 0):
  sum = comm.reduce(tmp,op=MPI.SUM, root=0)
else:
  comm.reduce(tmp,op=MPI.SUM, root=0)

print ("Process %s has final sum is %s" % (rank, sum))


sum = comm.bcast(sum, root = 0)
print ("Broadcast sum on process %s is %s" % (rank, sum))
