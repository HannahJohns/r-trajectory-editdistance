IEF SUMMARY:

adaptation of editdistance measurement for tracks with data points.

basically, the R function editdistance takes two tracks which are represented by dataframe and have two equal-sized vectors one of which for x coordinates and the other is for y coordinates. additionally, it takes other parameters describing the environment characteristics such as vertical and horizontal spacing of grids where the data points lie on and time_spacing which is set to 1.0 by default meaning that one step of time has the same length as one unit on grid. for time stretch and squeeze this parameter can be tweaked up.

INSTALLATION:
There are two ways. One is running the source.R then executing the test.R which serves as main. The other is building an R package from the source.R then importing it to R-base then running the test.R

for building R package, please refer to "Writing R Extensions" (http://cran.r-project.org/doc/manuals/r-release/R-exts.html)

for both options, you need to compile C source which is located under C SRC folder. A simple call to "R CMD SHLIB editDistance2.c" will do the job creating a .so file. then, you need to refer to this file from source.R. then you are good to go.

FUTURE WORK, ISSUES:
Based on this package, an official R package can be developed with good documentation. Maybe, borrowing some ideas from this implementation, an editdistance funtion that takes a custom cost function can be implemented. Here the cost depends on the mass center shifts of track points, the time points are recorded and distance between them.
Please drop a message if you are interested in colloborating.
Peace.

