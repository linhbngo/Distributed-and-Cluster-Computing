---
layout: page
title: Assignment 5 (40 points) - Due on Friday November 4th
---

**You can work as a two-member team for this assignment**

For this assignment, you are to deploy, observe, and record the behavior of
Hadoop in the event of node failure.

1. Deploy a 4-node Hadoop cluster on CloudLab using instructions to setup
Hortonworks' Hadoop distribution. This Hadoop cluster will have one namenode
and four datanodes. There should be no datanode-related services running on the namenode. Hadoop components to be installed include HDFS, YARN+MapReduce2, Tez, Zookeeper, and Ambari Metrics.  

2. Copy the **movielens** data set from the MapReduce lectures to the namenode
on your Hadoop cluster and upload this dataset onto HDFS.

Once this second step is completed, email the link of the Ambari Server page to the TA.

3. Using a local terminal (not the in-browser one accompanied with CloudLab), run *hdfs fsck* on the ratings.csv file and record the result on a log file.

4. Using the Ambari interface, shut down all Hadoop services on one of the **datanode**. Wait for at least five minutes, then rerun *hdfs fsck* on the ratings.csv file and record the result on a second log file.  

### Submission instructions:
Submissions for this assignment include:
- Initial email with link to Ambari server after steps 1 and 2 are completed.
- Final email containing the two log files for steps 3 and 4. The log files should be prefixed with the last names of the members of the team (or of the submitter).
- If working as a team, a document that describes how the work is divided between the members of the team with justification (e.g., what each member knows and does not know about the assignment) is also required for the final email.

For each group, only one set of submissions is needed.

#### There is absolutely no late submission for this assignment. 
