#!/usr/bin/env python
# trapezoidDynamic.py
from mpi4py import MPI
import numpy
comm = MPI.COMM_WORLD
rank = comm.Get_rank(); size = comm.Get_size()
def f(x):
    return x*x
partial_result = numpy.zeros(1)
local_result = numpy.zeros(1)
sum = numpy.zeros(1)
h = numpy.zeros(1)
a = numpy.zeros(1)
status = MPI.Status()

if (rank == 0):
    N = 1000; a[0]= 0; b = 1; h[0]= (b - a)/N;
    comm.Bcast(h, root = 0)
    count = 0;
    for i in range(1, size):
        comm.Send(a,dest = i,tag = 1)
        count = count + 1
else:
    comm.Bcast(h, root = 0)
    comm.Recv(a,source = 0, tag = 1,status = status)

if (rank != 0):
    while True:
        local_result[0] = h[0] * (f(a[0]) +  f(a[0] + h[0])) / 2
        partial_result[0] += local_result[0];
        comm.Send(local_result,dest = 0,tag = 1)      
        comm.Recv(a, source = 0, tag = MPI.ANY_TAG, status = status)
        if status.Get_tag() != 1:
            break
            
if (rank == 0):
    while (count < N):
        comm.Recv(partial_result, source = MPI.ANY_SOURCE, tag = MPI.ANY_TAG, status = status)
        sum[0] = sum[0] + partial_result[0]
        local_a = numpy.array([a + count * h])
        comm.Send(local_a, dest = status.Get_source(), tag = 1)
        count = count + 1      
    for i in range (1,size):
        comm.Recv(partial_result, source = MPI.ANY_SOURCE, tag = MPI.ANY_TAG, status = status)
        sum = sum + partial_result
    for i in range (1,size):
        comm.Send(a,dest = i,tag = 0)
    print ("The integral is %s" % (sum))
else:
    print ("The partial_integral is %s" % (partial_result))
