#include <stdio.h>
#include <stdlib.h>

int checkTop(int index, int num, const int puzzle[], const int constraints[], int size);
int checkBottom(int index, int num, const int puzzle[], const int constraints[], int size);
int checkRight(int index, int num, const int puzzle[], const int constraints[], int size);
int checkLeft(int index, int num, const int puzzle[], const int constraints[], int size);

int main() {
    int check;
    int puzzle[16] = {0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,3};
    int constraints[16] = {0,0,0,8,4,0,4,0,0,0,0,0,2,0,0,0};
    int index;
    int num;
    int size;

    check = checkTop(index, num, puzzle, constraints, size);



}

/*function header comment goes here */
int checkTop(int index, int num, const int puzzle[], const int constraints[], int size) {
    int constraints_check = 1;

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

/*function header comment goes here */
int checkBottom(int index, int num, const int puzzle, const int constraints, int size) {
    int constraints_check;
    constraints_check = 1;

    //bottom
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

/*function header comment goes here */
int checkLeft(int index, int num, const int *puzzle, const int *constraints, int size) {
    int constraints_check;
    constraints_check = 1;
    //left
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

/*function header comment goes here */
int checkRight(int index, int num, const int *puzzle, const int *constraints, int size) {
    int constraints_check;
    constraints_check =1;

    // right
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