#!/usr/bin/env python
# sendrecv.py
#!/usr/bin/env python
# sendrecv.py
from mpi4py import MPI
import random
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
if (rank == 0):
    send_pkg = random.random()
    print (send_pkg)
    comm.send(send_pkg, dest = 1, tag = 1)
if (rank == 1):
    recv_pkg = 0
    recv_pkg = comm.recv(source = 0, tag = 1)
    print (recv_pkg)
