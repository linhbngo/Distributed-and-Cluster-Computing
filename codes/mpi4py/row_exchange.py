#!/usr/bin/env python
# row_exchange.py
import numpy as np
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank(); size = comm.Get_size(); N = 24
status = MPI.Status()

local_array = np.full(shape=(int(N / size) + 2, N), fill_value=rank, dtype="int")
full_array = np.zeros(shape=(N + size * 2, N), dtype="int")

comm.Gather(local_array, full_array, root=0)
if rank == 0:
    print (full_array)
if (rank < size - 1):
    print (rank)
    comm.Send(local_array[int(N/size),], dest = rank + 1, tag = 0)
    comm.Recv(local_array[int(N/size) + 1,], source = rank + 1, tag = 0, status = status)
if (rank > 0):
    print (rank)
    comm.Recv(local_array[0,], source = rank - 1, tag = 0, status = status)
    comm.Send(local_array[1,], dest = rank - 1, tag = 0)

comm.Barrier()
comm.Gather(local_array, full_array, root=0)
if rank == 0:
    print (full_array)