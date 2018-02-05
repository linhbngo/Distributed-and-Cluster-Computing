#!/usr/bin/env python
# workdist.py
from mpi4py import MPI
import random
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
name = MPI.Get_processor_name()
A = [2,13,4,3,5,1,0,12,10,8,7,9,11,6,15,14]
#print ("Elements %s and %s are assigned to process %s" 
#       % (A[rank%15], A[1+rank%15], rank))
if (rank < 4):
    for i in range(0,16):
        if (i % size == rank):
            print ("Process %s has elements %s at index %s" % \
               (rank, A[i], i))