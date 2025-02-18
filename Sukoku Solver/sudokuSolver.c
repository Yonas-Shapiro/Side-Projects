#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudokuHelper.h"


// int main(int argc, char *argv[]){

//     printf("%s\n", argv[1]);

//     struct square *sqrs = readIn(argv[1]);
//     printSudoku(sqrs);

//     free(sqrs);

//     return 0;
// }


int main(int argc, char *argv[]){

    // Ensure a file is provided.
    if (argc == 1) {
        printf("No file provided.\n");
        return 1;
    }

    // Getting the file name
    char *file = argv[1];

    // Creating the squares and groups
    struct square *fileSquares = readIn(file);
    struct group *fileGroups = createGroups(fileSquares);

    // Attempting to solve the sudoku
    int solved =  solveSudoku(fileSquares, fileGroups);
    
    // Success/error message
    if (solved) printSudoku(fileSquares);
    else printf("The sudoku has no solutions\n");

    printSudoku(fileSquares);

    // Freeing the storage
    free(fileGroups);
    free(fileSquares);

    return 0;
}
