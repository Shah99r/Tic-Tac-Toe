
// ------------------- This is code for player vs AI mode ----------------------

#include <iostream>
#include <vector>
#include <algorithm> // For easily checking rows, columns and diagonals

using namespace std;

void clearScreen() {
    system("CLS");
}

struct Game {
    vector<vector<string>> board; 
    char turn; 
    bool gameEnd;
    int size;

    void initializeBoard(int boardSize) {
        size = boardSize;
        board.resize(size, vector<string>(size));
        int num = 1;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = to_string(num++);  // Store numbers as strings for consistant results
            }
        }
        turn = 'X'; 
        gameEnd = false;
    }

void displayBoard() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            
            if (board[i][j].length() == 1) {
                cout << "   " << board[i][j] << "   ";  
            } else {
                cout << "  " << board[i][j] << "   ";  
            }
            if (j < size - 1) cout << "|";        
        }
        cout << endl;

        
        if (i < size - 1) {
            for (int k = 0; k < size; k++) {
                cout << "-------";               
                if (k < size - 1) cout << "+";   
            }
            cout << endl;
        }
    }
        cout << endl;
    }

    bool isWinner(char mark) {
        // Check rows and columns
        for (int i = 0; i < size; i++) {
                                                         //using a lambda function to make the code compact and efficient
            if (all_of(board[i].begin(), board[i].end(), [mark](const string& c) { return c == string(1, mark); }))
                return true;
            if (all_of(board.begin(), board.end(), [i, mark](const vector<string>& row) { return row[i] == string(1, mark); }))
                return true;
        }
        // Check diagonals
        if (all_of(board.begin(), board.end(), [&, idx = 0](const vector<string>& row) mutable { return row[idx++] == string(1, mark); }))
            return true;
        if (all_of(board.begin(), board.end(), [&, idx = size - 1](const vector<string>& row) mutable { return row[idx--] == string(1, mark); }))
            return true;
        return false;
    }

    bool isTie() {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (board[i][j] != "X" && board[i][j] != "O")
                    return false;
        return true;
    }

    void playerMove() {
        int position;
        while (true) {
            cout << "Your turn (X). Enter a position: ";
            cin >> position;
            if (position >= 1 && position <= size * size) {
                int row = (position - 1) / size;
                int col = (position - 1) % size;
                if (board[row][col] != "X" && board[row][col] != "O") {
                    board[row][col] = "X";  
                    break;
                } else {
                    cout << "Position already taken. Try again.\n";
                }
            } else {
                cout << "Invalid input. Enter a number between 1 and " << size * size << ".\n";
            }
        }
    }

    void computerMove() {
        clearScreen(); 
        cout << "Computer's turn (O):\n";
        if (tryWinningMove('O') || tryBlockingMove('X') || tryStrategicMove() || tryRandomMove())
            return;
    }

    bool tryWinningMove(char mark) {
        return findBestMove(mark);
    }

    bool tryBlockingMove(char mark) {
        return findBestMove(mark);
    }

    bool findBestMove(char mark) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] != "X" && board[i][j] != "O") {
                    string temp = board[i][j];
                    board[i][j] = string(1, mark); 
                    if (isWinner(mark)) {
                        board[i][j] = "O";  
                        return true;
                    }
                    board[i][j] = temp;  
                }
            }
        }
        return false;
    }

    bool tryStrategicMove() {
        if (board[size / 2][size / 2] != "X" && board[size / 2][size / 2] != "O") {
            board[size / 2][size / 2] = "O";  
            return true;
        }
        return false;
    }

    bool tryRandomMove() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] != "X" && board[i][j] != "O") {
                    board[i][j] = "O";  
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    Game game;
    int boardSize;

    cout << "*****************************************************\n";
    cout << "*                                                   *\n";
    cout << "*            -- Welcome to Tic-Tac-Toe! --          *\n";
    cout << "*                  -- Player vs AI --               *\n";
    cout << "*                                                   *\n";
    cout << "*****************************************************\n\n";

    cout << "Enter the size of the grid (3 to 5): ";
    cin >> boardSize;
    while (boardSize < 3 || boardSize > 5) {
        cout << "Invalid size. Enter 3, 4, or 5: ";
        cin >> boardSize;
    }

    game.initializeBoard(boardSize);

    while (!game.gameEnd) {
        clearScreen(); 
        game.displayBoard();
        if (game.turn == 'X') {
            game.playerMove();
        } else {
            game.computerMove();
        }

        if (game.isWinner(game.turn)) {
            clearScreen();
            game.displayBoard();
            cout << (game.turn == 'X' ? "You win!" : "Computer wins!") << endl;
            game.gameEnd = true;
        } else if (game.isTie()) {
            clearScreen();
            game.displayBoard();
            cout << "It's a tie!" << endl;
            game.gameEnd = true;
        } else {
            game.turn = (game.turn == 'X') ? 'O' : 'X';
        }
    }

    return 0;
}
