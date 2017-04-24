---
layout: page
title: Assignment 3 (50 points) - Due on Friday September 16th
---

**You can work as a two-member team for this assignment**

For this assignment, you are to design, implement, test, and execute an MPI4PY
program inside a Jupyter notebook that can read a number of data files
concurrently, process the contents of these files, and aggregate the final information.

The target data files are a subset of the *job_events* table of the Google
Trace Data. The Google Trace Data contains the system logs of a 12,000-machine
data center for the duration of one month. This includes information about
machine status, status of submitted jobs, and status of tasks spawned by these
jobs. The full Google Trace Data is more than 170 GB in size. A sequential
attempt to process this data set will take more than 24 hours! The detailed
information about the google trace data can be found at Google cluster-usage
traces format and schema and Google cluster data traces.

The full *job_events* Google Data Set consists of 500 comma-separated data
files. The records of each file contain 8 fields:

- Field 1: time,INTEGER
- Field 2: missing info,INTEGER
- Field 3: job ID,INTEGER
- Field 4: event type,INTEGER
- Field 5: user,STRING_HASH
- Field 6: scheduling class,INTEGER
- Field 7: job name,STRING_HASH
- Field 8: logical job name,STRING_HASH

For each entry in the *job_events* data files, Field 4, event type, represents
the state of the job at the time stamp time (Field 1). There are 9 different states:

- SUBMIT (0): A task or job became eligible for scheduling.
- SCHEDULE (1): A job or task was scheduled on a machine. (It may not start
  running immediately due to code-shipping time, etc.) For jobs, this occurs
  the first time any task of the job is scheduled on a machine.
- EVICT(2): A task or job was descheduled because of a higher priority task or
job, because the scheduler overcommitted and the actual demand exceeded the
machine capacity, because the machine on which it was running became unusable
(e.g. taken offline for repairs), or because a disk holding the task’s data was lost.
- FAIL(3): A task or job was descheduled (or, in rare cases, ceased to be
  eligible for scheduling while it was pending) due to a task failure.
- FINISH(4): A task or job completed normally.
- KILL(5): A task or job was cancelled by the user or a driver program or
because another job or task on which this job was dependent died.
- LOST(6): A task or job was presumably terminated, but a record indicating its
termination was missing from our source data.
- UPDATE_PENDING(7): A task or job’s scheduling class, resource
requirements, or constraints were updated while it was waiting to be scheduled.
- UPDATE_RUNNING(8): A task or job’s scheduling class, resource
requirements, or constraints were updated while it was scheduled.

You are to write an MPI program that will count the number of job instances
for each of the 9 different states above. To make the execution and debugging
manageable for your first program, you will process 16 files out of the entire
500 file data set. These 16 files are located at **/scratch2/lngo/gtrace_small**
for this assignment. Start by making a data subdirectory in your /scratch2/$USER
directory and then copying the 16 files into it.

Your MPI program must satisfy the following conditions:

1. The program can hardcode the path to your subdirectory that contains the 16 data files. 

2. Your program can use a static file assignment strategy.  You can assume that
the number of data files (16) are evenly divisible by the number of processes
{1,2,4,8,16}. As all the data files follow the same naming scheme,
part-00???-of-00500.csv, each process should calculate its set of files to read
based on its rank and the size of the communicator
(e.g., total number of processes) and then assign to a variable the name
of the file(s) to open for reading (one at a time).

3. After opening each designated file, each MPI process will read through
the file line by line and count the occurrences of each *event_type* in the
file, storing the results for all event types in an array.  

4. When the MPI process finishes reading its files, it will send the counts of
each event type as a vector to process 0.  Your program should use a REDUCE call
for this step.  Process 0 will  aggregate the counts of the individual *event_type*
from  information collected from all participating processes using one reduce call.

5. Process 0 will print out the final aggregation using the following format:

Event Type                     Count

SUBMIT                           ????

SCHEDULE                     ????

EVICT                              ????

FAIL                                 ????

FINISH                             ????

KILL                                  ????

LOST                                ????

UPDATE_PENDING        ????

UPDATE_RUNNING        ????


6. You will test your program on a number of processes that is {1, 2, 4, 8, 16}.  
In your testing, be sure that your program runs correctly on all numbers of processes.

7. Extra credit (+5):  
- Add timing calls to your program to measure run time
- Collect the run times for different number of processes {1,2,4,8,16}
- Calculate the speedup of different number of processes {1,2,4,8,16} and use Python's matplotlib
to display a speedup graph

### Submission instructions:
Submit this version of the program by emailing the notebook containing the
MPI4PY program and the resulting output to the TA. If you work on this assignment
as a team, you must also include a document that describes how the work is
divided between the members of the team (e.g., what each member knows and does
  not know about the assignment).
