#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "sudokuHelper.h"

// Reading in the file and returning array of squares
struct square *readIn(char *filename){
    // Getting the file
    FILE *file = fopen(filename, "r");

    // Creating the values array
    struct square *values = malloc(81 * sizeof(struct square));
    char c;

    // Creating the squares
    for (int i=0; i<81; ++i){
        // Get the next non-whitespace char
        c = getc(file);
        while (c == ' ' || c == '\n') c = getc(file);

        // If c is a number, keep the number, otherwise c=0
        if (!(c > '0' && c <='9')) c = '0';
        values[i].value = c-'0';
    }

    // Returning the array of squares
    return values;
}

// Putting squares into groups to check them
struct group *createGroups(struct square *squares){

    // Creating the array of groups
    struct group *groups = malloc(27 * sizeof(struct group));

    // Rows
    for (int i=0; i<9; ++i){
        for(int j=9*i; j<9*i+9; ++j) groups[i].squares[j-9*i] = &squares[j];
    }

    // Columns
    for (int i=0; i<9; ++i){
        for (int j=0; j<9; ++j) groups[i+9].squares[j] = &squares[i+9*j];
    }

    // Boxes
    for (int i=0; i<3; ++i){
        for (int j=0; j<3; ++j){
            for (int k=0; k<3; ++k) {
                for (int l=0; l<3; ++l) groups[18+i+3*j].squares[k+3*l] = &squares[i*27 + j*9 + k*3 + l];
            }
        }
    }

    // Returning the array of groups
    return groups;
}

int checkDone(struct group gp){
    int nums[9] = {0,0,0,0,0,0,0,0,0};
    for (int i=0; i<=9; ++i) {
        int tmp = gp.squares[i]->value;
        if (!tmp) return 0;
        nums[tmp-1] += 1;
    }
    for (int i = 0; i < 9; i++) {
        if (nums[i] != 1) return 0;
    }
    return 1;
}

// Solving the Sudoku
int solveSudoku(struct square *squares, struct group *groups){

    // Changing the first zero
    for(int i=0; i<81; ++i){
        if (squares[i].value) continue;
        for (int j=1; j<9; ++j){
            squares[i].value=j;
            int passed=1;
            for (int k=0; k<27; ++k) {
                passed = checkDone(groups[k]);
                if (!passed) break;
            }
            // If current passes, then check further
            if (passed) passed = solveSudoku(squares, groups);
            // If a solution exists, return 1
            if (passed) return 1;
        }
        // If nothing passes, reset to 0.
        squares[i].value = 0;
    }
    return 0;

}


// Printing the Sudoku
void printSudoku(struct square *squares){
    // Variable to hold value of square
    int n;

    // Running through all squares
    for (int i=0; i<81; ++i){
        // Print value
        n = squares[i].value;
        printf("%d", n);

        // If end of sudoku -> newline
        if (i==80) printf("\n");
        // If end of every 3rd, print horizontal line
        else if (i%27 == 26) printf("\n------+-------+------\n");
        // If end of line, go to new line
        else if (i%9 == 8) printf("\n");
        // If end of square, print vertical bar
        else if (i%3==2) printf(" | ");
        // Otherwise print whitespace to separate numbers
        else printf(" ");
    }

    return;
}
