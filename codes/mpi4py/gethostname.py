#/usr/bin/env python
# gethostname.py
from mpi4py import MPI
import socket

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
print ("hello world from process %s running on host %s" % (rank, socket.gethostname()))
