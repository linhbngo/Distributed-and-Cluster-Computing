#!/usr/bin/env python
# bcast.py
from mpi4py import MPI
comm = MPI.COMM_WORLD; rank = comm.Get_rank();
if rank == 0:
    data = 2
elif (rank != 1):
    data = -1
else:
    data = -2
print ("%s: %s" % (rank, data))
if (rank != 1):
    data = comm.bcast(data, root=0)
    print ("%s: %s" % (rank, data))
else:
    data1 = comm.bcast(data, root=0)
    print ("%s: %s" % (rank, data))
if (rank == 1):
    print("%s: %s" % (rank, data1))