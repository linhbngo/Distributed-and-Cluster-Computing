#!/usr/bin/env python
# merge.py
import numpy as np
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank(); size = comm.Get_size(); status = MPI.Status();
N = 16
unsorted = np.zeros(N, dtype="int")
final_sorted = np.zeros(N, dtype="int")
local_array = np.zeros(int(N / size), dtype="int")
local_tmp = np.zeros(int(N / size), dtype="int")
local_remain = np.zeros(2 * int(N / size), dtype="int")

if rank == 0:
    unsorted = np.random.randint(low=0,high=N,size=N)
    print (unsorted)
comm.Scatter(unsorted, local_array, root = 0)

local_array.sort()

step = size / 2
print ("Rank: ", rank)
while (step >= 1):
    if (rank >= step and rank < step * 2):
        comm.Send(local_array, rank - step, tag = 0)
    elif (rank < step):
        local_tmp = np.zeros(local_array.size, dtype="int")
        local_remain = np.zeros(2 * local_array.size, dtype="int")
        comm.Recv(local_tmp, rank + step, tag = 0)
        i = 0 #local_array counter
        j = 0 # local_tmp counter
        for k in range (0, 2 * local_array.size):
            if (i >= local_array.size):
                local_remain[k] = local_tmp[j]
                j += 1
            elif (j >= local_array.size):
                local_remain[k] = local_array[i]
                i += 1
            elif (local_array[i] > local_tmp[j]):
                local_remain[k] = local_tmp[j]
                j += 1
            else:
                local_remain[k] = local_array[i]
                i += 1        
        print ("Step: ", step)
        print ("local array: ", local_array)
        print ("local tmp: ", local_tmp)
        print ("local remain: ", local_remain)
        local_array = local_remain
    step = step / 2
    
if (rank  == 0):
    print (local_array)