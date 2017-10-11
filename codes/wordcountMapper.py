#!/usr/bin/env python                                          
import sys                                                                                                
for oneLine in sys.stdin:
    oneLine = oneLine.strip()
    for word in oneLine.split(" "):
        if word != "":
            print ('%s\t%s' % (word, 1)) 