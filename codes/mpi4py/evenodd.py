#!/usr/bin/env python
# evenodd.py
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
name = MPI.Get_processor_name()
if (rank % 2 == 0):
    print ("Process %s is even" % (rank))
else:
    print ("Process %s is odd" % (rank))
