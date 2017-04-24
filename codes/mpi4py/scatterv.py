#!/usr/bin/env python
# scatterv.py
# Run with 3 processes
import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD; rank = comm.Get_rank()
if rank == 0:
    x = numpy.linspace(0,100,11)
    print (x)
else:
    x = None
if rank == 2:
    xlocal = numpy.zeros(9)
else:
    xlocal = numpy.zeros(1)
comm.Scatterv([x,(1,1,9),(0,1,2),MPI.DOUBLE],xlocal)
print ("process " + str(rank) + " has " +str(xlocal))
if (rank == 0):
    print(x)