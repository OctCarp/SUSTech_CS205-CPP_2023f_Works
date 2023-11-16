## Maze Escape

### Description

Given a two-dimensional array of maze and an array of directions. Your task is to follow the given directions.

- If you can reach the endpoint before all your moves have gone, return "`Finish`".
- f you hit any walls or go outside the maze border, return "`Dead`".
- If you find yourself still in the maze after using all the moves, return "`Lost`".

The maze array will look like this:

```cpp
maze = [
  [1, 1, 1, 1, 1, 1, 1, 1, 0, 1],
  [1, 3, 1, 0, 1, 0, 0, 0, 0, 1],
  [1, 0, 1, 0, 0, 0, 1, 1, 0, 1],
  [1, 0, 1, 1, 1, 1, 1, 0, 0, 1],
  [1, 0, 1, 0, 0, 0, 0, 0, 0, 1],
  [1, 0, 1, 0, 1, 0, 1, 0, 0, 1],
  [1, 0, 1, 0, 1, 0, 0, 0, 0, 0],
  [1, 0, 1, 0, 1, 0, 1, 1, 0, 1],
  [1, 0, 0, 0, 1, 0, 0, 0, 0, 1],
  [1, 1, 1, 0, 1, 1, 1, 1, 2, 1]
]

// 0 = Safe place to walk
// 1 = Wall
// 2 = Start Point
// 3 = Finish Point
// N = North, E = East, W = West and S = South
```

See the below examples for a better understanding:

```
["N", "E", "E"] ➞ "Dead"
// Hitting the wall should return "Dead".

["N", "N", "N", "E"] ➞ "Lost"
// Couldn't reach the finish point.

["N", "W", "W", "W", "N", "N", "N", "N", "W", "W", "S", "S", "S", "S", "W", "W", "N", "N", "N", "N", "N", "N", "N"] ➞ "Finish"
```

### Input

a sequence of letters indicating the directions

### Output

"`Finish`", "`Dead`", or "`Lost`"

### Sample Input 1 

```
N
E
E
```

### Sample Output 1

```
Result: Dead
```

### Hint

#### The C code template

```C
#include <stdio.h>
#include <string.h>

#define MAX_ROWS 10
#define MAX_COLS 10
#define MAX_DIRS 100

/* Assuming the use of C99 or later for the use of 'bool' type */
#include <stdbool.h>
#include <stdlib.h>

int exitMaze(int maze[MAX_ROWS][MAX_COLS], const char directions[][2], int numDirections) {

}

int main() {
  int maze[MAX_ROWS][MAX_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 3, 1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 2, 1}
  };

  char directions[MAX_DIRS][2];
  int numDirections = 0;
  char input[2];

// Enter directions (N, E, S, W), one per line. Enter ' ' to finish input
  while (numDirections < MAX_DIRS) {
    char buf[200];
    fflush(stdout);
    if (!fgets(buf, sizeof buf, stdin)) {
      break;
    }
    buf[strcspn(buf, "\n")] = '\0';
    if (buf[0] == '\0') {
      /* empty line */
      break;
    }
    sscanf(buf, "%1s", &input);
    if (strcmp(input, "N") == 0 || strcmp(input, "E") == 0 ||
        strcmp(input, "S") == 0 || strcmp(input, "W") == 0) {
      strcpy(directions[numDirections++], input);
    } else {
      printf("Invalid direction entered. Please enter N, E, S, or W.\n");
    }
  }

  int result = exitMaze(maze, directions, numDirections);
  const char* resultString = (result == 1) ? "Finish" : (result == 0) ? "Dead" : "Lost";
  printf("Result: %s\n", resultString);

  return 0;
}
```

#### The C++ code template

```CPP
#include <iostream>
#include <string>

using namespace std;

const int MAX_ROWS = 10; // Maximum number of rows in the maze
const int MAX_COLS = 10; // Maximum number of columns in the maze
const int MAX_DIRS = 100; // Maximum number of directions

string exitMaze(int maze[MAX_ROWS][MAX_COLS], string directions[], int numDirections) {


}

int main() {
  int maze[MAX_ROWS][MAX_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 3, 1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 2, 1}
  };

string directions[MAX_DIRS];
 int numDirections = 0;
  string input = "";

// Enter directions (N, E, S, W), one per line. Enter ' ' to finish input
  while (numDirections < MAX_DIRS) {
    getline(cin,input);
    if (input == "") {
      break;
    }
    if (input == "N" || input == "E" || input == "S" || input == "W") {
      directions[numDirections++] = input;
    } else {
      cout << "Invalid direction entered. Please enter N, E, S, or W." << endl;
    }
  }

  string result = exitMaze(maze, directions, numDirections);
  cout << "Result: " << result << endl;

  return 0;
  }
```