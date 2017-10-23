#!/usr/bin/env python
from mpi4py import MPI
import numpy as np
    
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
amode = MPI.MODE_WRONLY|MPI.MODE_CREATE
comm = MPI.COMM_WORLD
fh = MPI.File.Open(comm, "/home/lngo/datafile.contig", amode)

local_count = (int)(1600000000 / size)

buffer = np.empty(local_count, dtype=np.int)
buffer[:] = rank

offset = comm.Get_rank()*buffer.nbytes
fh.Write_at_all(offset, buffer)  
fh.Close()