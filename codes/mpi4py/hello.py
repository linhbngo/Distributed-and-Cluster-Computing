#!/usr/bin/env python
# hello.py
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
name = MPI.Get_processor_name()
print ("Hello world from process %s running on host %s out of %s processes" % 
       (rank, name, size)) 