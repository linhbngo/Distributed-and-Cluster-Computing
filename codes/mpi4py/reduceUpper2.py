#!/usr/bin/env python
# reducerUpper2.py
import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
LENGTH = 3
x = None
x_local = numpy.linspace(rank*LENGTH,(rank+1)*LENGTH, LENGTH)
print (x_local)
total = numpy.zeros(LENGTH)
comm.Reduce(x_local,total, op=MPI.SUM, root = 0)
print (total)
