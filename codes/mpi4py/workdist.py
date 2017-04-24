#!/usr/bin/env python
# workdist..py
from mpi4py import MPI
import random
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
name = MPI.Get_processor_name()
A = [2,13,4,3,5,1,0,12,10,8,7,9,11,6,15,14]
#print ("Elements %s and %s are assigned to process %s" 
#       % (A[rank%15], A[1+rank%15], rank))
#if (rank < 4):
#    print ("Process %s has elements %s" % (rank, A[(4*rank):(4*rank+4)]))


partial_work = int(len(A) / size)

if (rank < size):
  print ("Process %s has elements %s" % (rank, A[(partial_work*rank):(partial_work*rank+partial_work)]))
