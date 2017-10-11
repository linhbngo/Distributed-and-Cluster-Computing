#!/usr/bin/env python
# prefixsum.py
import numpy as np; import math; from mpi4py import MPI;
comm = MPI.COMM_WORLD; rank = comm.Get_rank(); size = comm.Get_size(); N = 16
local_nums = np.zeros(int(N/size), dtype="int")
recv_sum = np.zeros(1, dtype="int")
local_sums = np.zeros(int(N/size), dtype="int")
for i in range(0,int(N/size)):
    local_nums[i] = rank * int(N/size) + i
    local_sums[i] += np.sum(local_nums[0:(i+1)])

print("Process ", rank, " has initial local numbers: ", local_nums);
print("Process ", rank, " has initial local prefix sums: ", local_sums)
comm.Barrier()
for i in range(0, int(math.log2(size))):
    distance = int(math.pow(2,i))
    if (rank < (size - distance)):
        comm.Send(local_sums[int(N/size) - 1], dest = rank + distance, tag = 0)
    if (rank >= distance):
        status = MPI.Status()
        comm.Recv(recv_sum, source = rank - distance, tag = 0, status = status);
        for j in range(0,int(N/size)):
            local_sums[j] += recv_sum[0]
comm.Barrier()
print("Process ", rank, " has final prefix sums: ", local_sums)  