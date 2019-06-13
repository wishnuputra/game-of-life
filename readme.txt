This file contain the main program for running Game of Life.

The simulation of the Game of Life originally conceived by
the British mathematician J. H. Conway in 1970. The game
simulates the life cycle of bacteria using two dimensional
grid.
 
The simulation start with an initial pattern of cells on
the grid. The user type in the filename of the pattern.
Then convert the pattern into grid object. Consequently it
computes successive generations of cells according to
following rules:
 
 - A cell with 1 or fewer neighbors dies.
 - Locations with 2 neighbors remain stable.
 - Locations with 3 neighbors will create life.
 - A cell with 4 or more neighbors dies."