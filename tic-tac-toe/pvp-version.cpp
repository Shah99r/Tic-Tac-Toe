
// ------------------ This is code for player vs player mode -------------------

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For easily checking rows, columns and diagonals

using namespace std;

struct Player {
    string name;
    char mark;
};

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
                board[i][j] = to_string(num++); // Store numbers as strings for consistant results
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
};

Player p1, p2;
Game game;

void initializePlayers();
void addMark(Game& game, Player& currentPlayer);
bool isWinner(Game& game, Player& currentPlayer);
bool isTie(Game& game);
void clearScreen();

int main() {
    int boardSize;
    
    cout << "*****************************************************\n";
    cout << "*                                                   *\n";
    cout << "*            -- Welcome to Tic-Tac-Toe! --          *\n";
    cout << "*                -- Player vs Player --             *\n";
    cout << "*                                                   *\n";
    cout << "*****************************************************\n\n";

    cout << "Enter the size of the grid (3 to 5): ";
    cin >> boardSize;

    
    while (boardSize < 3 || boardSize > 5) {
        cout << "Invalid size. Please enter 3, 4, or 5: ";
        cin >> boardSize;
    }
    

    game.initializeBoard(boardSize);
    initializePlayers();

    while (!game.gameEnd) {
        clearScreen();
        game.displayBoard();

        Player& currentPlayer = (game.turn == 'X') ? p1 : p2;
        addMark(game, currentPlayer);

        if (isWinner(game, currentPlayer)) {
            game.displayBoard();
            cout << currentPlayer.name << " wins the game!\n";
            game.gameEnd = true;
        } else if (isTie(game)) {
            game.displayBoard();
            cout << "The game is a tie!\n";
            game.gameEnd = true;
        } else {
            game.turn = (game.turn == 'X') ? 'O' : 'X'; // Switch turns
        }
    }

    return 0;
}

void initializePlayers() {
    cin.ignore(); 
    cout << "Enter Player 1's name: ";
    getline(cin, p1.name);
    p1.mark = 'X';

    cout << "Enter Player 2's name: ";
    getline(cin, p2.name);
    p2.mark = 'O';
}

void addMark(Game& game, Player& currentPlayer) {
    string mark;
    while (true) {
        cout << currentPlayer.name << "'s turn (" << currentPlayer.mark << "). Enter a position: ";
        cin >> mark;

        try {
            int position = stoi(mark);
            if (position >= 1 && position <= game.size * game.size) {
                int row = (position - 1) / game.size;
                int col = (position - 1) % game.size;

                if (game.board[row][col] != "X" && game.board[row][col] != "O") {
                    game.board[row][col] = string(1, currentPlayer.mark);
                    break;
                } else {
                    cout << "Position already taken. Try again.\n";
                }
            } else {
                cout << "Invalid input. Please enter a number between 1 and " 
                     << game.size * game.size << ".\n";
            }
        } catch (invalid_argument&) {
            cout << "Invalid input. Please enter a number between 1 and " 
                 << game.size * game.size << ".\n";
        }
    }
}

bool isWinner(Game& game, Player& currentPlayer) {
    char mark = currentPlayer.mark;

    // Check rows and columns
    for (int i = 0; i < game.size; i++) {
                                                                    //using a lambda function to make the code compact and efficient
        if (all_of(game.board[i].begin(), game.board[i].end(), [mark](const string& c) { return c == string(1, mark); })) 
            return true;
        if (all_of(game.board.begin(), game.board.end(), [i, mark](const vector<string>& row) { return row[i] == string(1, mark); })) 
            return true;
    }

    // Check diagonals
    if (all_of(game.board.begin(), game.board.end(), [&, idx = 0](const vector<string>& row) mutable { return row[idx++] == string(1, mark); }))
        return true;
    if (all_of(game.board.begin(), game.board.end(), [&, idx = game.size - 1](const vector<string>& row) mutable { return row[idx--] == string(1, mark); }))
        return true;

    return false;
}

bool isTie(Game& game) {
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (game.board[i][j] != "X" && game.board[i][j] != "O") {
                return false;
            }
        }
    }
    return true;
}

void clearScreen() {

    system("CLS");

}
