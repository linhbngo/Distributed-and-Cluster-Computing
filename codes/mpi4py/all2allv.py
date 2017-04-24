#!/usr/bin/env python
# all2allv.py
import numpy
import random
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank(); size = comm.Get_size(); N = 8
local_array = numpy.random.randint(low = 0, high = N, size = N)
print("Rank ", rank, "local_array: ", local_array)
#stackoverflow
def constrained_sum_sample_pos(n, total):
    dividers = sorted(random.sample(range(1, total), n - 1))
    return [a - b for a, b in zip(dividers + [total], [0] + dividers)]
sendcount = numpy.array(constrained_sum_sample_pos(size, N), dtype="int")
dispcount = numpy.zeros(size, dtype="int")
dispcount[0] = 0
for i in range(1,size):
    dispcount[i] = dispcount[i-1] + sendcount[i-1]    
print ("Rank ", rank, " sendcount: ", sendcount)
print ("Rank ", rank, " dispcount: ", dispcount)
recvcount = numpy.zeros(size, dtype="int")
comm.Alltoall(sendcount, recvcount)
print("Rank ", rank, " recvcount: ", recvcount)
disprecv = numpy.zeros(size, dtype="int")
disprecv[0] = 0
for i in range(1,size):
    disprecv[i] = disprecv[i-1] + recvcount[i-1]   
print("Rank ", rank, " disprecv: ", disprecv)
new_array = numpy.zeros(numpy.sum(recvcount), dtype="int")
comm.Alltoallv([local_array,tuple(sendcount),tuple(dispcount),MPI.DOUBLE],
               [new_array, tuple(recvcount), tuple(disprecv), MPI.DOUBLE])
print ("Rank ", rank, "new_array: ", new_array)
#print (local_array)