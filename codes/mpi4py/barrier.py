#!/usr/bin/env python
# barrier.py
import time
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()

if rank == 0:
    time.sleep(5)
comm.Barrier()
print ("process " + str(rank) + " is here")