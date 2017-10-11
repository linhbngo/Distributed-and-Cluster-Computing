#!/usr/bin/env python
# sendrecvUpper.py
import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank(); print(rank)
a = numpy.zeros((4), dtype=numpy.int)
status = MPI.Status()
print (a)
if rank == 0:
    a = numpy.array([1,2,4])
    print (a)
    comm.Send(a, dest=1, tag = 1000)
if rank == 1:
    comm.Recv(a, source = 0, tag = MPI.ANY_TAG, status = status)
    print (status.Get_source())
    print (status.Get_tag())
    print (a)