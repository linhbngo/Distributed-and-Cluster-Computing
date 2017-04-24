#!/usr/bin/env python
from mpi4py import MPI
import numpy as np
    
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
amode = MPI.MODE_WRONLY|MPI.MODE_CREATE
comm = MPI.COMM_WORLD
fh = MPI.File.Open(comm, "./datafile.contig", amode)
   
buffer = np.empty(10, dtype=np.int)
buffer[:] = rank
print(buffer)

offset = comm.Get_rank()*buffer.nbytes
fh.Write_at_all(offset, buffer)  
fh.Close()

if (rank == 0):
    print (np.fromfile("./datafile.contig", dtype="int"))