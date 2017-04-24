#!/usr/bin/env python
# trapezoidRoundRobin.py
import numpy; from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank(); size = comm.Get_size()
N = 3000; a = 0; b = 1; h = (b - a)/N
def f(x):
    return x*x
local_N = N / size; local_a = a + rank * h
partial_result = numpy.zeros(1)
sum = numpy.zeros(1)
for i in range(0,int(local_N)):
    partial_result = partial_result + (f(local_a) + f(local_a + h)) * h / 2
    local_a = local_a + size * h
comm.Reduce(partial_result,sum, op=MPI.SUM, root=0)
print ("Process ", rank, " has ", partial_result[0])
if rank == 0:
    print ("The integral is %s" % (sum[0]))
