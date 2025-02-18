#ifndef SUDUKULAYOUT_H
#define SUDUKULAYOUT_H

// Structs
struct square {
    int value;
};
struct group { 
    struct square *squares [9];
};

// Creation functions
struct square *readIn(char *fileName);
struct group *createGroups(struct square *squares);

// Solving function
int solveSudoku(struct square *squares, struct group *groups);

// Printing out the grid
void printSudoku(struct square *squares);

#endif