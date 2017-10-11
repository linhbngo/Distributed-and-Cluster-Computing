#!/usr/bin/env python

import sys
import csv

movieFile = "./movielens/movies.csv"
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
        movieTitle = movieList[ratingInfo[1]]["title"]
        movieGenre = movieList[ratingInfo[1]]["genre"]
        rating = float(ratingInfo[2])
        print ("%s\t%s\t%s" % (movieTitle, rating, movieGenre))
    except ValueError:
        continue