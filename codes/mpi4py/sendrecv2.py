#!/usr/bin/env python
# sendrecv2.py
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
if rank == 0:
    data = {'class': 'cpsc3620', 'semester': 'Spring 2017', 
            'enrollments': 40}
    comm.send(data, dest=1, tag=11)
elif rank == 1:
    data = comm.recv(source=0, tag=11)
    print(data)
