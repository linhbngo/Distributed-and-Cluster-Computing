---
layout: page
title: Assignment 2 (50 points) - Due on Friday September 2nd
---

### Part I: Working with Palmetto (10 points)

Write a PBS job that satisfies the following requirements:

1. The job requires 4 physical compute nodes, each of which has 8 computing cores and 10GB of memory, for 30 minutes and returns output and error logs.
2. The script will use the pbsdsh command to return the host name of all the allocated nodes. Detailed instructions on pbsdsh can be found on its [man page](http://linux.die.net/man/1/pbsdsh). From the head node of Palmetto, submit this script and collect the output file when the job is finished. 

### Part II: Working with CloudLab (40 points)

Perform the following tasks on the CloudLab platform:

1. Create an account on www.cloudlab.us and join the PDC-edu-Lab project

2. Set up public/private key so that you can log into any future authorized CloudLab nodes from inside your Palmetto account

3. Create/instantiate a 3-node cluster profile using XenVM, then test your public/private key set up by logging into the three nodes, one by one, from Palmetto. 

4. Write and submit a PBS job such that:
    - The job requires 3 physical compute chunks for 30 minutes and returns output and error logs. 
    - From each physical chunk, the job should contact one node from your CloudLab cluster and request the full hostname of that node (hint: passwordless ssh +  sending Linux commands via ssh). 

### Grading and Submission
For both part 1 and 2, you are to email the class grader (lilix [at] g.clemson.edu) your PBS scripts and the PBS output logs. 
Also for part 2.3, as soon as you have instantiated your Xen-VM cluster, you need to send an email to the class grader (lilix [at] g.clemson.edu) with the URL to your experiment. Failure to do this will cost you half the point for part 2.3. 
