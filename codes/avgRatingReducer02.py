#!/usr/bin/env python
import sys
import csv

movieFile = "./movies.csv"
movieList = {}

with open(movieFile, mode = 'r') as infile:
    reader = csv.reader(infile)
    for row in reader:
        movieList[row[0]] = {}
        movieList[row[0]]["title"] = row[1]
        movieList[row[0]]["genre"] = row[2]

current_movie = None
current_rating_sum = 0
current_rating_count = 0

for line in sys.stdin:
    line = line.strip()
    movie, rating = line.split("\t", 1)
    try:
        rating = float(rating)
    except ValueError:
        continue

    if current_movie == movie:
        current_rating_sum += rating
        current_rating_count += 1
    else:
        if current_movie:
            rating_average = current_rating_sum / current_rating_count
            movieTitle = movieList[current_movie]["title"]
            movieGenres = movieList[current_movie]["genre"]
            print ("%s\t%s\t%s" % (movieTitle, rating_average, movieGenres))    
        current_movie = movie
        current_rating_sum = rating
        current_rating_count = 1

if current_movie == movie:
    rating_average = current_rating_sum / current_rating_count
    movieTitle = movieList[current_movie]["title"]
    movieGenres = movieList[current_movie]["genre"]
    print ("%s\t%s\t%s" % (movieTitle, rating_average, movieGenres))