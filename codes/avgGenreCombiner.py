#!/usr/bin/env python

import sys
import csv
import json

genreList = {}

for line in sys.stdin:
    line = line.strip()
    genre, ratingString = line.split("\t", 1)
    ratingInfo = json.loads(ratingString)

    if genre in genreList:
        genreList[genre]["total_rating"] += ratingInfo["total_rating"]
        genreList[genre]["total_count"] += ratingInfo["total_count"]
    else:
        genreList[genre] = {}
        genreList[genre]["total_rating"] = ratingInfo["total_rating"]
        genreList[genre]["total_count"] = 1

for genre in genreList:
    print ("%s\t%s" % (genre, json.dumps(genreList[genre])))