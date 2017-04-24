---
layout: page
title: Assignment 4 (50 points) - Due on Friday September 30th
---

**You can work as a two-member team for this assignment**

For this assignment, you are to execute and extend the heat exchange program
discussed in class. This assignment is to
be completed inside a Jupyter notebook.

The room size is set at 2048 by 2048. The number of time steps is 5,000

1. Modify the color printing code segment to demonstrate the dissipation of
heat throughout the room over time. More specifically, modify the code such
that a graphical presentation of the room's temperature is created every 500 steps.

2. Add timing call to the heat exchange program. Run the heat exchange program
with a 2048x2048 room size and 5,000 steps on 1, 2, 4, 8, 16, 32, and 64 cores
and collect the run times. Calculate the speedup for each core count and use
Python's matplotlib to display a speedup graph.

3. The original heat exchange MPI program partitions the room through a single
dimension (room_height). Modify the code such that the room can be partitioned
through both dimensions of the room. Repeat task 2 using the new heat exchange
program with the two-dimensional partitioning scheme and 1, 4, 16, 64 for the number of cores.

4. Overlay the speedup from task 2 and 3 on the same graph. Discuss the
differences in performance between the two partitioning schemes regarding
workload division and communication overhead.   

### Submission instructions:
Submit this version of the program by emailing the notebook containing the
all source codes and the resulting output to the TA. If you work on this assignment
as a team, you must also include a document that describes how the work is
divided between the members of the team (e.g., what each member knows and does
  not know about the assignment).
