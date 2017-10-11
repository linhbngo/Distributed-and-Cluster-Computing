#!/usr/bin/env python
import sys
import csv

# for nonHDFS run
movieFile = "./movielens/movies.csv"

# for HDFS run
#movieFile = "./movies.csv"
movieList = {}

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
        genreList = movieList[ratingInfo[1]]["genre"]
        rating = float(ratingInfo[2])
        for genre in genreList.split("|"):
            print ("%s\t%s" % (genre, rating))
    except ValueError:
        continue