#!/usr/bin/env python
# reduce.py
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank() 

sum = comm.reduce(rank, op=MPI.SUM, root=0)

if rank == 0:
    print ("The reduction is %s" % (sum))