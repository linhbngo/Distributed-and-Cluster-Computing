import numpy as np
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank(); size = comm.Get_size(); status = MPI.Status();
N = 16
HAS = 1
HASNOT = 0
unsorted = np.zeros(N, dtype="int")
final_sorted = np.zeros(N, dtype="int")
local_array = None
local_tmp = None
local_tmp_size = np.zeros(1,dtype="int")

if rank == 0:
    unsorted = np.random.randint(low=0,high=N,size=N)
    print (unsorted)
    local_array = unsorted

distance = 1
print ("Rank: ", rank)
while (distance <= size / 2):
    if (rank < distance):
        if (local_array is not None):
            if local_array.size == 1 or np.unique(local_array).size == 1:
                comm.Send(local_array[0], dest = rank + distance, tag = HASNOT)
            else:
                local_tmp = local_array[local_array > np.median(local_array)]
                comm.Send(np.full(shape = 1, fill_value = local_tmp.size, dtype="int"), dest = rank + distance, tag = HAS)
                comm.Send(local_tmp, dest = rank + distance, tag = HAS)
                local_array = local_array[local_array <= np.median(local_array)]
        else:
            comm.Send(np.zeros(1,dtype="int"), rank + distance, tag = HASNOT)
    elif (rank < 2 * distance):
        comm.Recv(local_tmp_size, source = rank - distance, tag = MPI.ANY_TAG, status = status)
        if status.Get_tag() == HASNOT:
            continue
        else:
            local_array = np.zeros(local_tmp_size[0], dtype="int")
            comm.Recv(local_array, source = rank - distance, tag = MPI.ANY_TAG, status = status)
    distance *= 2

local_array.sort()
print (local_array)