#!/usr/bin/env python
# gather.py
from mpi4py import MPI

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

data = (rank+1)**2
print ("%s: %s" % (rank, data))
all_data = comm.gather(data, root=0)
if rank == 0:
    print ("%s: %s" % (rank, data))
    print (all_data)
else:
    print ("%s: %s" % (rank, data))