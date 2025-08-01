#include <stdio.h>   // For standard input/output (printf, scanf)
#include <stdlib.h>  // For system("cls") or system("clear")
#include <stdbool.h> // For boolean type (true/false)

// Global game board
char board[3][3];

// Function prototypes
void initializeBoard();
void displayBoard();
bool isValidMove(int row, int col);
void makeMove(int row, int col, char player);
char checkWin();
bool checkDraw();

int main() {
    int row, col;
    int currentPlayer = 1; // 1 for Player X, 2 for Player O
    char playerMark;       // 'X' or 'O'
    char winner = ' ';
    int moves = 0;

    initializeBoard();

    do {
        // Clear screen for a cleaner display (works on most terminals)
        // For Windows: system("cls");
        // For Linux/macOS: system("clear");
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        displayBoard();

        // Determine current player's mark
        playerMark = (currentPlayer == 1) ? 'X' : 'O';
        printf("Player %d (%c), enter your move (row[1-3] col[1-3]): ", currentPlayer, playerMark);
        scanf("%d %d", &row, &col);

        // Adjust to 0-indexed array
        row--;
        col--;

        if (isValidMove(row, col)) {
            makeMove(row, col, playerMark);
            moves++;
            winner = checkWin();
            if (winner == ' ') { // If no winner yet, switch player
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
        } else {
            printf("Invalid move! That spot is already taken or out of bounds. Try again.\n");
            // Pause to allow user to read the message
            #ifdef _WIN32
                system("pause");
            #else
                printf("Press Enter to continue...");
                while(getchar() != '\n'); // Consume any left-over newlines
                getchar(); // Wait for user to press Enter
            #endif
        }

    } while (winner == ' ' && !checkDraw()); // Continue if no winner and no draw

    // Final board display
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    displayBoard();

    if (winner != ' ') {
        printf("\nPlayer %c wins! Congratulations!\n", winner);
    } else {
        printf("\nIt's a draw!\n");
    }

    return 0;
}

// Initializes the board with empty spaces represented by numbers 1-9 (or ' ')
void initializeBoard() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = ' '; // Initialize with spaces
        }
    }
}

// Displays the current state of the board
void displayBoard() {
    printf("\n\tTic-Tac-Toe\n\n");
    printf("     1   2   3\n");
    printf("   %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("  ---|---|---\n");
    printf("   %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("  ---|---|---\n");
    printf("   %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

// Checks if the chosen spot is within bounds and not already taken
bool isValidMove(int row, int col) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        return true;
    }
    return false;
}

// Places the player's mark on the board
void makeMove(int row, int col, char player) {
    board[row][col] = player;
}

// Checks if any player has won
// Returns 'X' if X wins, 'O' if O wins, ' ' if no winner yet
char checkWin() {
    int i;

    // Check rows
    for (i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return board[i][0];
        }
    }

    // Check columns
    for (i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i];
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return board[0][2];
    }

    return ' '; // No winner yet
}

// Checks if the game is a draw (all cells filled, no winner)
bool checkDraw() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false; // Found an empty spot, not a draw yet
            }
        }
    }
    return true; // All spots filled, and no winner (checked by main loop)
}