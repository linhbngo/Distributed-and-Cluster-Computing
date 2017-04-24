1. Give an example of demand for computation speed

2. In a  sentence, define speedup

3. In a sentence, define efficiency

4. Describe two limiting factors in achieving maximum parallelism

5. Describe linear speedup?  What types of applications will exhibit linear speedup?

6. What is superlinear speedup?  What can cause superlinear speedup?

7. In a sentence, define Amdahl’s Law.  Give the equation for Amdahl’s Law.

8. Suppose that I get a speedup of 8 when I run my application on 10 processors.  According to Amdahl's Law, what portion is serial?  What is the speedup on 20 processors?  What is the efficiency?  What is the best speedup that I could hope for?

9. Suppose that 4% of my application is serial.  What is my predicted speedup according to Amdahl’s Law on 5 processors?

10. For each of the following type of parallel computers, briefly describe its architecture, provide its schematic, and name a programming model
- SIMD
- Shared memory
- Distributed memory – message passing
- Distributed shared memory

11. Briefly describe the three benchmarking procedures: LINPACK, HPCC, SHOC

12. Briefly describe the three supercomputing rankings: TOP500, GREEN500, GRAPH500

13. Give the command to load the gcc compiler version 5.3.0 and the openmpi library version 10.3.1 into your environment

14. What is a message tag?

15. What is an MPI communicator?  What is the purpose of the communicator?

16. In MPI, what is a process rank? What routine do you use to determine a process rank?

17. True or false:  In MPI you set the number of processes when you write the source code.

18. Explain the basic functionality of the collective calls Bcast, Scatter, Gather, Barrier, Reduce, and how they are the same or different from each other.

19. With a short sentence, describe the role of MPI.COMM_WORLD

20. What is “Pleasantly Parallel?” List two characteristics of pleasantly parallel

21. Describe three workload assignment approaches for pleasantly parallel using a few sentences for each approach

22. How do the worker processes know when to terminate in the dynamic workload assignment model?

23. With a short sentence each, describe the two basic partitioning approaches in parallel programming.

24. A scientist wants to calculate the sum of 8,192 integers. The scientist has a 16-cores CPU that takes 0.1ns to transfer one integer from one core to another. Construct a tree that describes the divide-and-conquer process to calculate the sum. Calculate the communication time the “divide” period and the communication time for the “conquer” period.

25. Given 8 processes ranked 0 through 7, sort the following array of integers in ascending order using the odd-even transposition sorting process. You should clearly indicate which integers belong to which process at every single stage of the sorting process. [13, 7, 14, 11, 10, 4, 15, 12, 3, 6, 16, 1, 2, 8, 9, 5]

26. Be prepared to answer programming questions of the following type:       

- Using only MPI_Send and MPI_Recv, implement MPI_Reduce.
- Using only MPI_Send and MPI_Recv, implement MPI_Scatter.
- Using only MPI_Send and MPI_Recv, implement MPI_Gather.
- Using only MPI_Send and MPI_Recv, implement MPI_Alltoall.

27. Suppose the following is run with 3 processes, with rank 0, 1, and 2, respectively. What are the values of x, y, and z in each process after the code has been executed?

~~~
comm = MPI.COMM_WORLD
if rank == 0:
  x=0; y=1; z=2;
  comm.Bcast(x, root = 0)
  comm.Send(y, des = 2, tag = 43)
  comm.Bcast(z, root = 1)
if rank == 1:  
  x=3, y=4, z=5;
  comm.Bcast(x, root = 0)
  comm.Bcast(y, root = 1)
if rank == 2:
  x=6; y=7; z=8;
  comm.Bcast(z, root = 0)
  comm.Recv(x, source = 0, tag = 43, status=status)
  comm.Bcast(y, root = 1)
~~~

28. Explain if the following MPI code segment is correct or not, and why:
Process 0 executes:

~~~
comm.Bcast(mydata, root = 0)
~~~

All other processes:

~~~
comm.Bcast(yourdata, root = 0)
~~~

29. Explain if the following MPI code segment is correct or not, and why:
Process 0 executes:

~~~
comm.Bcast(mydata, root = 0)
~~~

All other processes:

~~~
comm.Recv(mydata, source = 0, MPI.ANY_TAG, status = status)
~~~

30. Explain if the following MPI code segment is correct or not, and why:

Process 0 executes:

~~~
comm.Recv(yourdata, source = 1, tag = 0, status = status)
comm.Send(mydata, des = 1, tag = 0)
~~~

Process 1 executes:

~~~
comm.Recv(yourdata, source = 0, tag = 0, status = status)
comm.Send(mydata, des = 0, tag = 0)
~~~

31. Give an example of a master/slave computation using MPI-like pseudocode.

32. Understand and be able to read/trace through all codes discussed in class lectures.

33. Understand the principles of the communication tree among the processes in divide-and-conquer problems.

34. What are the four main characteristics of Parallel File Systems?

35. What are the two main differences between block-based and object-based parallel file systems?
