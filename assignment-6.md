---
layout: page
title: Assignment 6 (40 points) - Due on Wednesday November 23rd
---

**You can work as a two-member team for this assignment**

For this assignment, you are to develop solutions for the following challenges
that were described in the intro-to-hadoop.ipynb notebook.

1. Modify the wordcount application so that punctuations and capitalization are no longer factors in determining unique words. Name the map and reduce files *wordcountEnhancedMapper.py* and *wordcountEnhancedReducer.py*.

2. Modify the average rating application so that only movies with averaged ratings higher than 3.75 and rated at least 5000 times are collected. Name the map and reduce files *avgRatingFilteredMapper.py* and *avgRatingFilteredReducer.py*.

3. Modify the user application to correct the error in calculating the users that that rate movies most frequently. Name the map and reduce files  *userCorrectMapper.py* and *userCorrectReducer.py*.

4. Enhance the user study from question 3 so that only users who provide frequent reviews on movies contain the genre with the highest rating (as calculated from section 2.2 in the intro-to-hadoop.ipynb notebook) are selected.
Name the map and reduce files *userGenreMapper.py* and *userGenreReducer.py*.

### Submission instructions:
Submission for this assignment is a compressed file containing:
- The four map/reduce pairs for the questions listed above.
- A README document containing any assumptions that have been made for the answers.
- If working as a team, a document that describes how the work is divided between the members of the team with justification (e.g., what each member knows and does not know about the assignment) is also required for the final email.

For each group, only one submission is needed.
