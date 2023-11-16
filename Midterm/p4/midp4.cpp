#include <iostream>
#include <string>

using namespace std;
using pii = pair<int, int>;

#define x first
#define y second

const int MAX_ROWS = 10; // Maximum number of rows in the maze
const int MAX_COLS = 10; // Maximum number of columns in the maze
const int MAX_DIRS = 100; // Maximum number of directions

string exitMaze(int maze[MAX_ROWS][MAX_COLS], string directions[], int numDirections) {
    pii cur;
    bool find_start = false;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (maze[i][j] == 2) {
                cur.x = i;
                cur.y = j;
                find_start = true;
                break;
            }
        }
        if (find_start) { break; }
    }

    for (int i = 0; i < numDirections; ++i) {
        char d = directions[i][0];
        switch (d) {
            case 'N':
                cur.x = cur.x - 1;
                break;
            case 'S':
                cur.x = cur.x + 1;
                break;
            case 'W':
                cur.y = cur.y - 1;
                break;
            case 'E':
                cur.y = cur.y + 1;
                break;
            default:
                //never happens
                return "Dead";
        }

        if (cur.x < 0 || cur.x >= 10 || cur.y < 0 || cur.y >= 10) {
            return "Dead";
        }

        int res = maze[cur.x][cur.y];
        if (res == 3) {
            return "Finish";
        }
        if (res == 1) {
            return "Dead";
        }
    }

    return "Lost";
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
        getline(cin, input);
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