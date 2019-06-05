// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
#include "strlib.h"
using namespace std;

void welcomeMessage();
Grid<char> readFileInput();
void printGrid(Grid<char> &grid);
void nextGeneration(Grid<char> &grid);
void tickLife(Grid<char> &grid);
void animateLife(Grid<char> &grid);
int countNeighbors(Grid<char> &grid, int r, int c);
void updateGrid(Grid<char> &grid);

int main() {
    welcomeMessage();
    Grid<char> grid = readFileInput();
    printGrid(grid);

    nextGeneration(grid);

    cout << "Have a nice Life!" << endl;
    return 0;
}

/**
 * Method: welcomeMessage
 * --------------
 * This method will print the welcome message
 */
void welcomeMessage() {
    cout << "Welcome to the CS 106B Game of Life," << endl;
    cout << "a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbors dies." << endl;
    cout << "- Locations with 2 neighbors remain stable." << endl;
    cout << "- Locations with 3 neighbors will create life." << endl;
    cout << "- A cell with 4 or more neighbors dies." << endl;
}

/**
 * Method readFileInput
 * --------------------
 * This method will read a file that user typed in.
 * if the file doesn't exist, it will reprompt until it
 * found the available file. Then it will convert the file
 * into a grid object.
 */
Grid<char> readFileInput() {
    ifstream input;
    promptUserForFile(input, "Grid input file name?");

    // obtaining number of rows and columns
    string line;
    getline(input, line);
    int numRow = stringToInteger(line);
    getline(input, line);
    int numCol = stringToInteger(line);

    // creating grid object
    Grid<char> grid(numRow, numCol);
    for (int r = 0; r < numRow; r++) {
        getline(input, line);
        for (int c = 0; c < numCol; c++) {
            grid[r][c] = line[c];
        }
    }

    return grid;
}

/**
 * Method: printGrid
 * ------------------
 * This method will print the grid elements for each
 * rows and columns.
 */
void printGrid(Grid<char> &grid) {
    for (int r = 0; r < grid.nRows; r++) {
        for (int c = 0; c < grid.nCols; c++) {
            cout << grid[r][c];
        }
        cout << endl;
    }
}

void nextGeneration(Grid<char> &grid) {
    string nextAction;
    while (true) {
         nextAction = toLowerCase(getLine("a)nimate, t)ick, q)uit? "));
         if (nextAction == "a") {
              animateLife(grid);
         } else if (nextAction == "t") {
              tickLife(grid);
         } else if (nextAction == "q") {
             break;
         } else {
             cout << "Invalid choice; please try again." << endl;
         }
     }
}

void tickLife(Grid<char> &grid) {
    int neighbors;
    for (int r = 0; r < grid.nRows; r++) {
        for (int c = 0; c < grid.nCols; c++){
            char ch = grid[r][c];
            neighbors = countNeighbors(grid, r, c);
            //cout << "Grid[" << r << "][" << c << "] : " << neighbors << endl;
            if (neighbors >= 4 && ch == 'X') {
                grid[r][c] = 'x';
            } else if (neighbors == 3 && ch == '-') {
                grid[r][c] = '+';
            } else if (neighbors <= 2 && ch == 'X') {
                grid[r][c] = 'x';
            }
        }
    }
    updateGrid(grid);
    printGrid(grid);
}

void animateLife(Grid<char> &grid) {

}

int countNeighbors(Grid<char> &grid, int i, int j) {
    int counter = 0;
    for (int r = i - 1; r <= i + 1; r++) {
        for (int c = j - 1; c <= j + 1; c++) {
            if (grid.inBounds(r, c)) {
                char ch = grid[r][c];
                if (ch == 'X' || ch == 'x')
                    counter++;
            }
        }
    }
    return counter;
}

void updateGrid(Grid<char> &grid) {
    for (int r = 0; r < grid.numRows(); r ++) {
        for (int c = 0; c < grid.numCols(); c++) {
            char ch = grid[r][c];
            if (ch == 'x')
                grid[r][c] = '-';
            if (ch == '+')
                grid[r][c] = 'X';
        }
    }
}



