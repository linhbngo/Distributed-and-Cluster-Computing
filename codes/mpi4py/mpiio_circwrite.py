#!/usr/bin/env python
from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = comm.Get_rank();size = comm.Get_size();

amode = MPI.MODE_WRONLY|MPI.MODE_CREATE
fh = MPI.File.Open(comm, "./datafile.noncontig", amode)
item_count = 10
buffer = np.empty(item_count, dtype='i')
buffer[:] = rank
print (buffer)
filetype = MPI.INT.Create_vector(item_count, 1, size)
filetype.Commit()

displacement = MPI.INT.Get_size()*rank
fh.Set_view(displacement, filetype=filetype)

fh.Write_all(buffer)
filetype.Free()
fh.Close()

if (rank == 0):
    print (np.fromfile("./datafile.noncontig", dtype="i"))