#!/usr/bin/env python
# bucket1.py
import numpy as np
from mpi4py import MPI
comm = MPI.COMM_WORLD

rank = comm.Get_rank(); size = comm.Get_size(); N = 16

unsorted = np.zeros(N, dtype="int")
final_sorted = np.zeros(N, dtype="int")

if rank == 0:
    unsorted = np.random.randint(low=0,high=N,size=N)
    
comm.Bcast(unsorted)
local_min = rank * N / size
local_max = (rank + 1) * N / size

#generic form:
# local_min = rank * (b - a) / size
# local_max = (rank + 1) * (b - a) / size

print("At rank ", rank, ": ", local_min, local_max)

local_bucket = unsorted[np.logical_and(unsorted >= local_min, 
                                       unsorted < local_max)]
local_sorted = np.sort(local_bucket)

arr_sendcount = np.zeros(size, dtype="int")
sendcount = np.array([local_sorted.size], dtype="int")

comm.Gather(sendcount, arr_sendcount, root=0)
comm.Bcast(arr_sendcount, root = 0)

dispcount = np.zeros(size, dtype="int")
dispcount[0] = 0
for i in range(1,size):
    dispcount[i] = dispcount[i-1] + arr_sendcount[i-1]
    
comm.Gatherv(local_sorted, [final_sorted, 
                            tuple(arr_sendcount), 
                            tuple(dispcount), 
                            MPI.DOUBLE])

if (rank == 0):
    print ("At root: ", unsorted)
    print ("At root: ", final_sorted)
print("Rank", rank, ": ", local_bucket)
print("Rank", rank, ": ", local_sorted)