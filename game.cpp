#include <iostream>
#include <vector>
#include <limits>
#ifdef _WIN32
    #include <cstdlib>
#endif
class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;
public:
    TicTacToe() {
        board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
        currentPlayer = 'X';
    }
    void displayBoard() {
        clearScreen();
        std::cout << "\n\tTic-Tac-Toe\n\n";
        std::cout << "     1   2   3\n";
        for (int i = 0; i < 3; ++i) {
            std::cout << " " << (i + 1) << "   ";
            for (int j = 0; j < 3; ++j) {
                std::cout << board[i][j];
                if (j < 2) std::cout << " | ";
            }
            if (i < 2) std::cout << "\n    ---|---|---\n";
        }
        std::cout << "\n\n";
    }
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    bool makeMove(int row, int col) {
        row--; col--;
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = currentPlayer;
            return true;
        }
        return false;
    }
    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    char checkWin() {
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
                return board[i][0];
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
                return board[0][i];
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
            return board[0][0];
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
            return board[0][2];
        return ' ';
    }
    bool isBoardFull() {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == ' ') return false;
            }
        }
        return true;
    }
    char getCurrentPlayer() const { return currentPlayer; }
};
int main() {
    TicTacToe game;
    int row, col;
    char winner = ' ';
    while (winner == ' ' && !game.isBoardFull()) {
        game.displayBoard();
        std::cout << "Player " << game.getCurrentPlayer() << ", enter move (row[1-3] col[1-3]): ";  
        if (!(std::cin >> row >> col)) {
            std::cout << "Invalid input! Please enter numbers.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (game.makeMove(row, col)) {
            winner = game.checkWin();
            if (winner == ' ') {
                game.switchPlayer();
            }
        } else {
            std::cout << "Invalid move! Spot taken or out of bounds. Press Enter to try again...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    game.displayBoard();
    if (winner != ' ') {
        std::cout << "Player " << winner << " wins! Congratulations!\n";
    } else {
        std::cout << "It's a draw!\n";
    }
    return 0;
}
