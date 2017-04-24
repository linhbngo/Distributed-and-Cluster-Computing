#!/usr/bin/env python
# conquer.py
from mpi4py import MPI
import math
comm = MPI.COMM_WORLD
rank = comm.Get_rank(); size = comm.Get_size()
for i in range(int(math.log2(size)) - 1, -1, -1):
    distance = int(math.pow(2, i))
    if ( rank < int(math.pow(2, i)) ):
        print ("Iteration ", i, ": receiver ", rank, 
               " receives from ", rank + distance)
    if (rank >= int(math.pow(2, i)) and rank < int(math.pow(2,i+1))):
        print ("Iteration ", i, ": sender ", rank, 
               "sends to ", rank - distance)
    #am I sender or receiver?
    # who am I sending/receiving to/from?    