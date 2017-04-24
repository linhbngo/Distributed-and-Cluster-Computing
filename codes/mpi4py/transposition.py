#!/usr/bin/env python
# transposition.py
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
for step in range(0, size):
    print ("Step: ", step)
    if (step % 2 == 0):
        if (rank % 2 == 0):
            des = rank + 1
        else:
            des = rank - 1
    else:
        if (rank % 2 == 0):
            des = rank - 1
        else:
            des = rank + 1
            
    if (des >= 0 and des < size):
        print ("My rank is ", rank, " and my des is ", des)
        comm.Send(local_array, dest = des, tag = 0)
        comm.Recv(local_tmp, source = des)    
        print ("Rank ", rank, " ", step, ": Initial local_array: ", local_array)
        print ("Rank ", rank, " ", step, ": Received local_tmp:", local_tmp)
        local_remain = np.concatenate((local_array, local_tmp), axis=0)
        local_remain.sort()
        
        if (rank < des):
            local_array = local_remain[0:int(N/size)]
        else:
            local_array = local_remain[int(N/size):2 * int(N/size)]
        print ("Rank ", rank, " ", step, ": Retained portions: ", local_array)
comm.Gather(local_array, final_sorted)

if (rank  == 0):
    print (final_sorted)