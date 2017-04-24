#!/usr/bin/env python
# bcastUpper.py
import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
rand_num = numpy.zeros(1)
print (rand_num[0])
if rank == 0:
    rand_num[0] = numpy.random.uniform(0)
    print(rand_num[0])
comm.Bcast(rand_num, root = 0)
print ("Process", rank, "has the number", rand_num[0])
