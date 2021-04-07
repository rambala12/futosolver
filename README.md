# Futo Solver
This program reads a futoshiki puzzle defined in a text file. The program then solves the puzzle and displays the completed puzzle. 
## What is a futoshiki puzzle?
A futoshiki puzzle is similar to a sudoku puzzle, where the solutions consists of numbers the obey certain rules. A futoshiki puzzle board is always n-by-n size and certain positions/blocks have constraints regarding numbers around them. For example, one box can have a constraint that it must be greater than the box above it. The numbers used in the puzzle can only be 1 through n.
## Creating a puzzle file
The first line of the file contains the value of n. The following lines create a board figure to describe the constraints. An example is shown below.
```
4
| - - - - |
|        V|
| - 2 - - |
| ^       |
| - - - - |
|         |
| ->- - 3 |
```
The text puzzle has one row with values and a row below to add constraints. The "-" value indicates a blank space that must be filled. The may also puzzle contain some numbers already. The "V" character means the value below must be less than the value above, the "^" character means the value below must be greater than value above, the ">" character means the value to the left must be greater than the value to the right, and the "<" character means the value to the left must be less than the value to the right. 
## Using the program
The program will prompt you to enter an input file. Enter the name of the file where the puzzle is defined (example: "puzz.txt"). The program will then solve and output a text based visual of the solution. 

