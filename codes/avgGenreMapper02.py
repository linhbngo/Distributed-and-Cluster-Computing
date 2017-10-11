#!/usr/bin/env python

import sys
import csv
import json

# for nonHDFS run
# movieFile = "./movielens/movies.csv"

# for HDFS run
movieFile = "./movies.csv"

movieList = {}
genreList = {}

with open(movieFile, mode = 'r') as infile:
    reader = csv.reader(infile)
    for row in reader:
        movieList[row[0]] = {}
        movieList[row[0]]["title"] = row[1]
        movieList[row[0]]["genre"] = row[2]

for oneMovie in sys.stdin:
    oneMovie = oneMovie.strip()
    ratingInfo = oneMovie.split(",")
    try:
        genres = movieList[ratingInfo[1]]["genre"]
        rating = float(ratingInfo[2])
        for genre in genres.split("|"):
            if genre in genreList:
                genreList[genre]["total_rating"] += rating
                genreList[genre]["total_count"] += 1
            else:
                genreList[genre] = {}
                genreList[genre]["total_rating"] = rating
                genreList[genre]["total_count"] = 1
    except ValueError:
        continue
        
for genre in genreList:
    print ("%s\t%s" % (genre, json.dumps(genreList[genre])))