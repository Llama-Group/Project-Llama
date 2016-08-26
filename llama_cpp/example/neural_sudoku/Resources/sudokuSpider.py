#!/usr/bin/python

import urllib2
from BeautifulSoup import *
import csv

SUDOKU_COUNT = 991

sudokuPuz = csv.writer(open("puzzle.csv",  "w+"))
sudokuSol = csv.writer(open("solution.csv",  "w+"))

mode = 0
for id in range(1,  SUDOKU_COUNT+1):
    url = "http://www.lemo.dk/sudoku/sudoku.php?serial=" + str(id)
    solUrl = url + "&solution"
    print "Fetch sudoku", id
    for i in range(2):
        html = None
        if mode == 0:
            html = urllib2.urlopen(url).read()
        elif mode == 1:
            html = urllib2.urlopen(solUrl).read()
        bs = BeautifulSoup(html)
        table = bs.find(lambda tag: tag.name=="table" and tag.has_key("class") and tag["class"]=="s")
        
        if table:
            assumedTable = table.findAll(lambda tag: tag.name=="tr")
            rows = table.findAll("td")
            result = []
            for row, valueRow in enumerate(rows):
                if valueRow.renderContents() == "&nbsp;":
                    result.append(0)
                else:
                    result.append(int(valueRow.renderContents()))
            if mode == 0:
                sudokuPuz.writerow(result)
            elif mode == 1:
                sudokuSol.writerow(result)
            else:
                print "Wrong mode!"
            mode = mode ^ 1
        else:
            print "Sudoku not found!"
