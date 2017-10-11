#!/usr/bin/env python
# scatter.py
from mpi4py import MPI
comm = MPI.COMM_WORLD
size = comm.Get_size();rank = comm.Get_rank(); print(rank)

if rank == 0:
    data = [(i+1)**2 for i in range(size)]
    print (data)
else:
    data = None
partial_data = comm.scatter(data, root=0)
print (data)
print (rank, partial_data)