#!/usr/bin/env python
# gatherUpper.py
import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
LENGTH = 3
x = None
x_local = numpy.linspace(rank*LENGTH,(rank+1)*LENGTH, LENGTH)
print(x_local)
if rank == 0:
    x = numpy.zeros(size*LENGTH)
    print (x)
comm.Gather(x_local, x, root=0)

#you should notice that only the root process has a value for x that
#is not "None"
print ("process", rank, "x:", x)
print ("process", rank, "x_local:", x_local)
