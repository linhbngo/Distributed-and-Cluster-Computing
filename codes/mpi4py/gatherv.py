#!/usr/bin/env python
# gatherv.py
# Run with 3 processes
import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD; rank = comm.Get_rank()
if rank == 0:
    x = numpy.linspace(0,80,9)
    print (x)
else:
    x = None
if rank == 1:
    xlocal = numpy.zeros(7)
else:
    xlocal = numpy.zeros(1)
comm.Scatterv([x,(1,7,1),(0,1,8),MPI.DOUBLE],xlocal); 
if rank == 0:
    xGathered = numpy.zeros(9)
else:
    xGathered = None
comm.Gatherv(xlocal,[xGathered,(1,7,1),(0,1,1),MPI.DOUBLE])
print (" process ", rank, " has ", xlocal); 
if (rank == 0):
    print ("process " + str(rank) + " has " +str(xGathered))