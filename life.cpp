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
void printGrid(Grid<char>);
void nextGeneration();

int main() {
    welcomeMessage();
    Grid<char> grid = readFileInput();
    printGrid(grid);

    nextGeneration();

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
    int row = stringToInteger(line);
    getline(input, line);
    int col = stringToInteger(line);

    // creating grid object
    Grid<char> grid(row, col);
    for (int r = 0; r < row; r++) {
        getline(input, line);
        for (int c = 0; c < col; c++) {
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
void printGrid(Grid<char> grid) {
    for (int r = 0; r < grid.nRows; r++) {
        for (int c = 0; c < grid.nCols; c++) {
            cout << grid[r][c];
        }
        cout << endl;
    }
}

void nextGeneration() {
     while (true) {
         string next = getLine("a)nimate, t)ick, q)uit? ");
         if(next == "a" || next == "t" || next == "q") {
             break;
         }
         cout << "Invalid choice; please try again." << endl;
     }

//     if (next == "a") {

//     } else if (next = "t") {

//     } else if (next = "q") {

//     }

}
