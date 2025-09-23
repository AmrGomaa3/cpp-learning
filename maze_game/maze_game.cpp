#include <iostream>
#include <limits>
#include <stdexcept>


// constant variables
constexpr int COL {10};
constexpr int ROW {10};
int CURRENT_ROW {1};
int CURRENT_COL {1};
constexpr int WINNING_ROW {8};
constexpr int WINNING_COL {5};


// function prototypes
void createMaze(char arr[][COL]);
void printMaze(char arr[][COL]);
char getCharInput(bool reset=false);
void movePlayer(char maze[][COL], int row, int col, char move);
void restartGame(char maze[][COL]);


int main() {
    char maze[ROW][COL];

    createMaze(maze);

    while (true) {
        printMaze(maze);
        std::cout << "Enter a or d or w or s to move or enter r to restart or q to exit: ";

        char input {getCharInput()};

        if (input == 'q') return EXIT_SUCCESS;
        else if (input == 'r') {
            restartGame(maze);
            continue;
        }

        try {
            movePlayer(maze, CURRENT_ROW, CURRENT_COL, input);
        }
        catch (const std::invalid_argument& e) {
            continue;
        }

        if (CURRENT_ROW == WINNING_ROW && CURRENT_COL == WINNING_COL) {
            printMaze(maze);
            std::cout << "Congratulations!\n" << "Restart? (y/n): ";

            char choice {getCharInput(true)};

            if (choice == 'n') return EXIT_SUCCESS;
            else if (choice == 'y') {
                restartGame(maze);
            }
        }
    }
}


void createMaze(char arr[][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (i == 0 || i == ROW - 1 || j == 0 || j == COL - 1) arr[i][j] = '#';
            else if (i == 1 && j == 1) arr[i][j] = 'P';
            else if (i == WINNING_ROW && j == WINNING_COL) arr[i][j] = 'E';
            else if (i == 2 && j != 6) arr[i][j] = '#';
            else if (i == 4 && j != 8 && j != 2) arr[i][j] = '#';
            else if (i == 6 && j != 8 && j != 2) arr[i][j] = '#';
            else if (i == 7 && j == 7) arr[i][j] = '#';
            else if (i == 8 && (j == 6 || j == 4 || j == 2)) arr[i][j] = '#';
            else arr[i][j] = '.';
        }
    }
}


void printMaze(char arr[][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            std::cout << arr[i][j] << " ";
        }

        std::cout << "\n";
    }
}


char getCharInput(bool reset) {
    char input;

    while (true) {
        std::cin >> input;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard leftover junk
            continue;
        }

        if (reset) {
            if (input != 'y' && input != 'n') continue;
        } else {
            if (input != 'a' && input != 's' && input != 'w' && input != 'd' && input != 'q' && input != 'r') continue;
        }

        break;
    }

    return input;
}


void movePlayer(char maze[][COL], int row, int col, char move) {
    int newRow {row};
    int newCol {col};

    if (move == 'a') newCol--;
    else if (move == 'd') newCol++;
    else if (move == 'w') newRow--;
    else if (move == 's') newRow++;

    if (maze[newRow][newCol] == '#') throw std::invalid_argument("");

    maze[newRow][newCol] = 'P';

    if (row == 1 && col == 1) maze[row][col] = 'S';
    else maze[row][col] = '.';

    if (newRow != row) CURRENT_ROW = newRow;
    else CURRENT_COL = newCol;
}


void restartGame(char maze[][COL]) {
    CURRENT_COL = 1;
    CURRENT_ROW = 1;
    createMaze(maze);
}
