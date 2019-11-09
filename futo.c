/*
 * Name: Ram Bala
 *
 * futo.c takes a text file describing a futoshiki puzzle
 * and outputs the solved file by processing through the file
 * using arrays
 *
 */

#include <stdio.h>
#include <stdlib.h>

int solve(int puzzle[], const int constraints[], int size);
int readPuzzle(const char *name, int **puzzle, int **constraints, int *size);
void printPuzzle(const int puzzle[], const int constraints[], int size);
int isLegal(int row, int col, int num, const int puzzle[], const int constraints[], int size);
int checkTop(int index, int num, const int puzzle[], const int constraints[], int size);
int checkBottom(int index, int num, const int puzzle[], const int constraints[], int size);
int checkRight(int index, int num, const int puzzle[], const int constraints[], int size);
int checkLeft(int index, int num, const int puzzle[], const int constraints[], int size);

#ifndef NOMAIN   /* ignore: this is to remove the main function for testing purposes */

int main() {
    char filename[20];
    int *puzzle;       /* array for puzzle numbers */
    int *constraints;  /* array for puzzle constraints */
    int size;          /* size of puzzle */
    printf("Puzzle file: ");
    fflush(stdout);
    scanf("%20s", filename);

    if (!readPuzzle(filename, &puzzle, &constraints, &size)) {
        printf("Unable to open puzzle file: %s\n", filename);
        return 1;
    }

    printf("PUZZLE:\n");
    printPuzzle(puzzle, constraints, size);

    printf("\nSOLUTION:\n");
    if (solve(puzzle, constraints, size)) {
        printPuzzle(puzzle, constraints, size);
    }
    else {
        printf("No solution exists.\n");
    }
    return EXIT_SUCCESS;
}

#endif  /* ignore */


/*
 * readPuzzle processes the text file and places the values
 * into puzzle array as well as the corresponding constraints
 */
int readPuzzle(const char *name, int **puzzle, int **constraints, int *size) {
    FILE* file;
    char *all_array;
    int *vals; /* points to the puzzle array */
    int *vals2; /* points to constraints array */
    char value;
    int count;
    int const_val;
    int i;
    int total; /* find a way to calculate later (mac vs dos/linux) */
    int get2constraint; /* difference in array from puzzle value to constraint */

    file = fopen(name, "r"); /* open file */
    if (!file) return 0; /* check if file is able to be open */

    fscanf(file, "%d", &*size); /* get dimension of array */
    get2constraint = *size * 2 + 3;

    total = (2 * *size + 1) * (2 * *size + 1);

    vals = (int*) malloc(*size * *size * sizeof(int));
    *puzzle = vals; /* puzzle array space dynamically allocated */

    vals2 = (int*) malloc(*size * *size * sizeof(int));
    *constraints = vals2; /* constraints array space allocated */

    /* read text file and assign save to all_array */
    all_array = (char *) malloc(total * sizeof(char));

    i = 0;
    while (!feof(file)) {
        fscanf(file, "%c", &all_array[i]);
        i++;
    }

    count = 0;
    for (i = 0; i < total; i++) {
        value = all_array[i];
        const_val = 0;
        if (value == 45) {
            vals[count] = 0; /* if hyphen, make 0 for puzzle array */

            /* check to the right */
            if (all_array[i + 1] == ' ') {
                const_val = const_val | 0;
                vals2[count] = const_val;
            }
            if (all_array[i + 1] == 'v') {
                const_val = const_val | 8;
                vals2[count] = const_val;
            }
            if (all_array[i + 1] == '^') {
                const_val = const_val | 4;
                vals2[count] = const_val;
            }
            if (all_array[i + 1] == '>') {
                const_val = const_val | 2;
                vals2[count] = const_val;
            }
            if (all_array[i + 1] == '<') {
                const_val = const_val | 1;
                vals2[count] = const_val;
            }

            /* check bottom */
            if (all_array[i + get2constraint] == ' ') {
                const_val = const_val | 0;
                vals2[count] = const_val;
            }
            if (all_array[i + get2constraint] == 'v') {
                const_val = const_val | 8;
                vals2[count] = const_val;
            }
            if (all_array[i + get2constraint] == '^') {
                const_val = const_val | 4;
                vals2[count] = const_val;
            }
            if (all_array[i + get2constraint] == '>') {
                const_val = const_val | 2;
                vals2[count] = const_val;
            }
            if (all_array[i + get2constraint] == '<') {
                const_val = const_val | 1;
                vals2[count] = const_val;
            }

            count++;
        }
        if (value >= 48 && value <= 57) {
            vals[count] = value - 48; /* check and place number value for puzzle array */

            /* check to the right */
            if (all_array[i + 1] == ' ') {
                vals2[count] = 0;
            }
            if (all_array[i + 1] == 'v') {
                const_val = const_val | 8;
                vals2[count] = const_val;
            }
            if (all_array[i + 1] == '^') {
                const_val = const_val | 4;
                vals2[count] = const_val;
            }
            if (all_array[i + 1] == '>') {
                const_val = const_val | 2;
                vals2[count] = const_val;
            }
            if (all_array[i + 1] == '<') {
                const_val = const_val | 1;
                vals2[count] = const_val;
            }

            /* check bottom */
            if (all_array[i + get2constraint] == ' ') {
                vals2[count] = 0;
            }
            if (all_array[i + get2constraint] == 'v') {
                const_val = const_val | 8;
                vals2[count] = const_val;
            }
            if (all_array[i + get2constraint] == '^') {
                const_val = const_val | 4;
                vals2[count] = const_val;
            }
            if (all_array[i + get2constraint] == '>') {
                const_val = const_val | 2;
                vals2[count] = const_val;
            }
            if (all_array[i + get2constraint] == '<') {
                const_val = const_val | 1;
                vals2[count] = const_val;
            }

            count++;
        }
    }
    vals2[*size * *size - 1] = 0; /* set the last value of the constraints array as 0 */

    return 1;
}

/*
 * printPuzzle takes the puzzle and constraints arrays and
 * prints the formatted puzzle to the screen using these arrays
 */
void printPuzzle(const int *puzzle, const int *constraints, int size) {
    int i;
    int x;
    int y;
    int j;

    x = 0;
    y = 0;
    for (i = 0; i < size * 2 - 1; i++) {
        /* if an even row, print boxes and left right constraints */
        if (i % 2 == 0) {
            printf("|");
            for (j = 0; j < size; j++) {
                /* Printing puzzle */
                if (puzzle[x * size + j] == 0) {
                    printf("-");
                } else {
                    printf("%d", puzzle[x * size + j]);
                }
                /* Printing constraints */
                if (j == size - 1) {
                    printf("|");
                    break;
                }
                if (constraints[x * size + j] == 0 || (constraints[x * size + j] == 4)||
                    (constraints[x * size + j] == 8)) {
                    printf(" ");
                }
                if ((constraints[x * size + j] & 1) == 1) {
                    printf("<");
                }
                if ((constraints[x * size + j] & 2) == 2) {
                    printf(">");
                }

            }
            x++;
            printf("\n");
        } else { /* if odd, print constraints row only */
            printf("|");
            for (j = 0; j < size; j++) {
                if (constraints[y * size + j] == 0 || constraints[y * size + j] == 1 ||
                    constraints[y * size + j] == 2) {
                    printf(" ");
                }
                if ((constraints[y * size + j] & 4) == 4) {
                    printf("^");
                }
                if ((constraints[y * size + j] & 8) == 8) {
                    printf("v");
                }
                if (j == size - 1) {
                    printf("|");
                    break;
                }
                printf(" ");
            }
            y++;
            printf("\n");
        }
    }

    return;
}

/*
 * solve uses recursive backtracking to try different values
 * to test which values are ultimately correct
 */
int solve(int *puzzle, const int *constraints, int size) {
    int row;
    int col;
    int num;
    int index;
    int i;
    int count;
    count = 0;


    for (i = 0; i < size * size; i++) {
        if (puzzle[i] != 0) {
            count++;
        }
    }
    if (count == size * size) {
        return 1;
    } else {
        index = 0;
        while (puzzle[index] != 0) {
            index++;
        }
    }
    col = index % size;
    row = index / size;

    for (num = 1; num <= size; num++) {
        if (isLegal(row, col, num, puzzle, constraints, size) == 1) {
            puzzle[index] = num;
            if (solve(puzzle, constraints, size)) {
                return 1;
            } else {
                puzzle[index] = 0;
            }
        }
    }
    return 0;

}

/* isLegal determines if a number is legal for placement in the puzzle array */
int isLegal(int row, int col, int num, const int *puzzle, const int *constraints, int size) {
    int index;
    int i;

    index = row * size + col;

    /* if top row, no need to check for above constraints */
    if (row == 0) {
        if (checkLeft(index, num, puzzle, constraints, size) == 0) {
            return 0;
        }
        if (checkRight(index, num, puzzle, constraints, size) == 0) {
            return 0;
        }
        if (checkBottom(index, num, puzzle, constraints, size) == 0) {
            return 0;
        }
    } else if (col == 0) {
        if (checkRight(index, num, puzzle, constraints, size) == 0) {
            return 0;
        }
        if (checkBottom(index, num, puzzle, constraints, size) == 0) {
            return 0;
        }
        if (checkTop(index, num, puzzle, constraints, size) == 0) {
            return 0;
        }
    } else {
        if (checkRight(index, num, puzzle, constraints, size) == 0) {
            return 0;
        }
        if (checkBottom(index, num, puzzle, constraints, size) == 0) {
            return 0;
        }if (checkLeft(index, num, puzzle, constraints, size) == 0) {
            return 0;
        }
        if (checkTop(index, num, puzzle, constraints, size) == 0) {
            return 0;
        }
    }

    /* check if number is already in the row */
    for (i = 0; i < size; i++) {
        if (i == col) {
            i++;
        }
        index = row * size + i;
        if (num == puzzle[index]) {
            return 0;
        }
    }

    /* check if number is already in the column */
    for (i = 0; i < size; i++) {
        if (i == row) {
            i++;
        }
        index = i * size + col;
        if (num == puzzle[index]) {
            return 0;
        }
    }

    return 1;
}

/* checkTop checks the constraints above an element */
int checkTop(int index, int num, const int *puzzle, const int *constraints, int size) {
    int constraints_check;
    constraints_check = 1;

    if (puzzle[index - size] != 0) {
        if ((constraints[index - size] & 8) == 8) {
            /* run check to see if p[index] > p[index + size] */
            if (num < puzzle[index - size]) {
                constraints_check = 1;
            } else {
                constraints_check = 0;
            }
        }
        if ((constraints[index - size] & 4) == 4) {
            /* run check to see if p[index] < p[index + size] */
            if (num > puzzle[index - size]) {
                constraints_check = 1;
            } else {
                constraints_check = 0;
            }
        }
    }

    return constraints_check;
}

/* checkBottom checks the constraints below an element */
int checkBottom(int index, int num, const int *puzzle, const int *constraints, int size) {
    int constraints_check;
    constraints_check = 1;

    if (puzzle[index + size] != 0) {
        if ((constraints[index] & 8) == 8) {
            /* run check to see if p[index] > p[index + size] */
            if (num > puzzle[index + size]) {
                constraints_check = 1;
            } else {
                constraints_check = 0;
            }
        }
        if ((constraints[index] & 4) == 4) {
            /* run check to see if p[index] < p[index + size] */
            if (num < puzzle[index + size]) {
                constraints_check = 1;
            } else {
                constraints_check = 0;
            }
        }
    }

    return constraints_check;
}

/* checkLeft checks the constraints to the left of an element */
int checkLeft(int index, int num, const int *puzzle, const int *constraints, int size) {
    int constraints_check;
    constraints_check = 1;

    if (puzzle[size - 1] != 0) {
        if ((constraints[index - 1] & 2) == 2) {
            /* run check to see if p[index] > p[index + 1] */
            if (num < puzzle[index - 1]) {
                constraints_check = 1;
            } else {
                constraints_check = 0;
            }
        }
        if ((constraints[index - 1] & 1) == 1) {
            /* run check to see if p[index] < p[index - 1] */
            if (num > puzzle[index - 1]) {
                constraints_check = 1;
            } else {
                constraints_check = 0;
            }
        }
    }

    return constraints_check;
}

/* checkRight checks the constraints to the right of an element */
int checkRight(int index, int num, const int *puzzle, const int *constraints, int size) {
    int constraints_check;
    constraints_check =1;

    if (puzzle[size + 1] != 0) {
        if ((constraints[index] & 2) == 2) {
            /* run check to see if p[index] > p[index + 1] */
            if (num > puzzle[index + 1]) {
                constraints_check = 1;
            } else {
                constraints_check = 0;
            }
        }
        if ((constraints[index] & 1) == 1) {
            /* run check to see if p[index] < p[index - 1] */
            if (num < puzzle[index + 1]) {
                constraints_check = 1;
            } else {
                constraints_check = 0;
            }
        }
    }

    return constraints_check;
}

