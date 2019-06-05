/*
 * Title: Game Of Life
 * File: life.cpp
 * Author: Wishnuputra Dhanu
 * Date: 5 June 2019
 * ---------------------------------------------------------------
 * This file contain the main program for running Game of Life.
 * The simulation of the Game of Life originally conceived by
 * the British mathematician J. H. Conway in 1970. The game
 * simulates the life cycle of bacteria using two dimensional
 * grid.
 *
 * The simulation start with an initial pattern of cells on
 * the grid. The user type in the filename of the pattern.
 * Then convert the pattern into grid object. Consequently it
 * computes successive generations of cells according to
 * following rules:
 *
 * - A cell with 1 or fewer neighbors dies.
 * - Locations with 2 neighbors remain stable.
 * - Locations with 3 neighbors will create life.
 * - A cell with 4 or more neighbors dies."
 *
 */

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
void printGrid(Grid<char> &grid, LifeGUI &gui);
void nextGeneration(Grid<char> &grid, LifeGUI &gui);
void tickLife(Grid<char> &grid, LifeGUI &gui);
void animateLife(Grid<char> &grid, LifeGUI &gui);
int countCells(Grid<char> &grid, int r, int c);
void updateGrid(Grid<char> &grid);
void printConsoleCleared();
void printEqualSign(int num);

int main() {
    LifeGUI gui;
    welcomeMessage();
    Grid<char> grid = readFileInput();
    gui.resize(grid.nRows, grid.nCols);
    printGrid(grid, gui);
    //drawGraphics(grid,gui);
    nextGeneration(grid, gui);

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
void printGrid(Grid<char> &grid, LifeGUI &gui) {
    for (int r = 0; r < grid.nRows; r++) {
        for (int c = 0; c < grid.nCols; c++) {
            char ch = grid[r][c];
            //cout << grid[r][c];
            gui.drawCell(r, c, ch == 'X');
        }
        //cout << endl;
    }
}

/**
 * Method: nextGeneration
 * -----------------------
 * Update the grid from one generation to the
 * next generation.
 */
void nextGeneration(Grid<char> &grid, LifeGUI &gui) {
    string nextAction;
    while (true) {
         nextAction = toLowerCase(getLine("a)nimate, t)ick, q)uit? "));
         if (nextAction == "a") {
              animateLife(grid, gui);
         } else if (nextAction == "t") {
              tickLife(grid, gui);
         } else if (nextAction == "q") {
             break;
         } else {
             cout << "Invalid choice; please try again." << endl;
         }
     }
}

/**
 * Method: tickLife
 * -----------------
 * This method will proceed to the next generation by one step.
 */
void tickLife(Grid<char> &grid, LifeGUI &gui) {
    int cells;
    Grid<char> newGrid = grid;
    for (int r = 0; r < grid.nRows; r++) {
        for (int c = 0; c < grid.nCols; c++){
            char ch = grid[r][c];
            cells = countCells(grid, r, c);
            //cout << "Grid[" << r << "][" << c << "] : " << neighbors << endl;
            if (cells <= 2 && ch == 'X')
                newGrid[r][c] = '-';
            if (cells == 3 && ch == '-')
                newGrid[r][c] = 'X';
            if (cells >= 5 && ch == 'X')
                newGrid[r][c] = '-';
        }
    }
    grid = newGrid;
    printGrid(grid, gui);
}

void animateLife(Grid<char> &grid, LifeGUI &gui) {
    int numFrame = getInteger("How many frames? ");
    for (int i = 0; i < numFrame; i++) {
        tickLife(grid, gui);
        //printConsoleCleared();
    }
}

/**
 * Method: countCells
 * ---------------------------------------------------
 * This method will count the number of cells present
 * inside 3x3 area.
 * ---------------------------------------------------
 * Input parameter:
 * grid: the grid of the colony.
 * i: the row index when this method is called.
 * j: the column index when this method is called.
 * ---------------------------------------------------
 * --> return : number of cells inside 3x3 area.
 */
int countCells(Grid<char> &grid, int i, int j) {
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

/**
 * Method: printConsoleCleared
 * ----------------------------
 * This method will print the text "console cleared"
 * at the end of the grid.
 */
void printConsoleCleared() {
    printEqualSign(20);
    cout << " (console cleared) ";
    printEqualSign(20);
    cout << endl;
}

/**
 * Method: printEqualSign
 * -----------------------
 * Print n number of equal signs
 */
void printEqualSign(int n) {
    for (int i = 0; i < n; i++) {
        cout << "=";
    }
}

