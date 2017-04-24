#!/usr/bin/env python
# bucket2.py
import numpy as np
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank(); size = comm.Get_size(); N = 16
unsorted = None
local_unsorted = np.zeros(int(N / size), dtype="int")
final_sorted = np.zeros(N, dtype="int")
if rank == 0:
    unsorted = np.random.randint(low=0,high=N,size=N)
    print ("Original unsorted data at process", rank, ": ", unsorted)
comm.Scatter(unsorted, local_unsorted, root = 0)
print ("Scattered data at process ", rank, ": ", local_unsorted)

local_buckets = np.full(shape=(int(N/size), size), fill_value=-1, dtype="int")
sendcount = np.zeros(size, dtype="int")
local_unsorted_bucketed = np.zeros(int(N / size), dtype="int")
count = 0
for i in range(0, size):    
    for j in range (0, local_unsorted.size):
        local_min = i * N/size
        local_max = (i + 1) * N / size  
        if ((local_unsorted[j] >= local_min) and (local_unsorted[j] < local_max)):
            local_buckets[i][sendcount[i]] = local_unsorted[j]
            sendcount[i] += 1
    if (sendcount[i] > 0):
        local_unsorted_bucketed[count:count + sendcount[i]] = local_buckets[i, 0:sendcount[i]]
        print ("Local_unsorted_bucketed at process ", rank, ": ", local_unsorted_bucketed)
        count += sendcount[i]

print ("Sendcount at process ", rank, ": ", sendcount)
print ("Bucket matrix at process ", rank, ": \n", local_buckets)

dispcount = np.zeros(size, dtype="int")
dispcount[0] = 0
for i in range(1,size):
    dispcount[i] = dispcount[i-1] + sendcount[i-1]    

recvcount = np.zeros(size, dtype="int")
comm.Alltoall(sendcount, recvcount)
print("Rank ", rank, " recvcount: ", recvcount)
disprecv = np.zeros(size, dtype="int")
disprecv[0] = 0
for i in range(1,size):
    disprecv[i] = disprecv[i-1] + recvcount[i-1]   
print("Rank ", rank, " disprecv: ", disprecv)
single_unsorted_bucket = np.zeros(np.sum(recvcount), dtype="int")
comm.Alltoallv([local_unsorted_bucketed,tuple(sendcount),tuple(dispcount),MPI.DOUBLE],
               [single_unsorted_bucket, tuple(recvcount), tuple(disprecv), MPI.DOUBLE])
print ("Rank ", rank, " single_unsorted_bucket: ", single_unsorted_bucket)
local_sorted = np.sort(single_unsorted_bucket)
arr_sendcount = np.zeros(size, dtype="int")
sendcount = np.array([local_sorted.size], dtype="int")
comm.Gather(sendcount, arr_sendcount, root=0)
comm.Bcast(arr_sendcount, root = 0)
dispcount = np.zeros(size, dtype="int")
dispcount[0] = 0
for i in range(1,size):
    dispcount[i] = dispcount[i-1] + arr_sendcount[i-1]
comm.Gatherv(local_sorted, [final_sorted, tuple(arr_sendcount), tuple(dispcount), MPI.DOUBLE])
if (rank == 0):
    print (final_sorted)