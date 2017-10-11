#!/usr/bin/env python
# scatterUpper.py
import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank();size = comm.Get_size();LENGTH = 3
if rank == 0:
    x = numpy.linspace(1,size*LENGTH,size*LENGTH)
    print ("Original data: ", x)
else:
    x = None
x_local = numpy.zeros(LENGTH)
comm.Scatter(x, x_local, root=0)
#you should notice that only the root process has a value for x that
#is not "None"
print ("process", rank, "x:", x)
print ("process", rank, "x_local:", x_local)