#!/usr/bin/env python

import sys

for oneMovie in sys.stdin:
    oneMovie = oneMovie.strip()
    ratingInfo = oneMovie.split(",")
    try:
        movieID = ratingInfo[1]
        rating = float(ratingInfo[2])
        print ("%s\t%s" % (movieID, rating))
    except ValueError:
        continue