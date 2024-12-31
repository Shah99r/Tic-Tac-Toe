#include <iostream>
#include <string>

using namespace std;

struct Player {
    string name;
    char mark;
};

struct Game {
    char board[3][3];
    char turn;
    bool gameEnd;

    // Initialize the board with numbers
    void initializeBoard() {
        char num = '1';
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = num++;
            }
        }
        turn = 'X';
        gameEnd = false;
    }

void displayBoard() const {
  int size = 3;
    for (int i = 0; i < size; i++) {
        // Print each row of cells
        for (int j = 0; j < size; j++) {
            cout << "   " << board[i][j] << "   "; // Add spaces around each cell
            if (j < size - 1) cout << "|";        // Add vertical separators
        }
        cout << endl;

        // Print horizontal separators between rows
        if (i < size - 1) {
            for (int k = 0; k < size; k++) {
                cout << "-------";               // Add dashes to separate rows
                if (k < size - 1) cout << "+";   // Add "+" at intersections
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

  cout << "*****************************************************\n";
  cout << "*                                                   *\n";
  cout << "*            -- Welcome to Tic-Tac-Toe! --          *\n";
  cout << "*                  -- Player Menu --                *\n";
  cout << "*                                                   *\n";
  cout << "*****************************************************\n";

  game.initializeBoard();
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
        }else if(isTie(game)) {
            game.displayBoard();
            cout << "The game is a tie!\n";
            game.gameEnd = true;
        }else{
            game.turn = (game.turn == 'X') ? 'O' : 'X'; // Switch turns
      }
    }

    return 0;
}

void initializePlayers() {
    cout << "Enter Player 1's name: ";
    getline(cin, p1.name);
    p1.mark = 'X';

    cout << "Enter Player 2's name: ";
    getline(cin, p2.name);
    p2.mark = 'O';
}

void addMark(Game& game, Player& currentPlayer) {
    char mark;
    while (true) {
        cout << currentPlayer.name << "'s turn (" << currentPlayer.mark << "). Enter a position (1-9): ";
        cin >> mark;

        if (mark >= '1' && mark <= '9') {
            int row = (mark - '1') / 3;
            int col = (mark - '1') % 3;

            if (game.board[row][col] != 'X' && game.board[row][col] != 'O') {
                game.board[row][col] = currentPlayer.mark;
                break;
            } else {
                cout << "Position already taken. Try again.\n";
            }
        } else {
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
        }
    }
}

bool isWinner(Game& game, Player& currentPlayer) {
    char mark = currentPlayer.mark;

    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++) {
        if ((game.board[i][0] == mark && game.board[i][1] == mark && game.board[i][2] == mark) || 
            (game.board[0][i] == mark && game.board[1][i] == mark && game.board[2][i] == mark)) {
            return true;
        }
    }

    if ((game.board[0][0] == mark && game.board[1][1] == mark && game.board[2][2] == mark) ||
        (game.board[0][2] == mark && game.board[1][1] == mark && game.board[2][0] == mark)) {
        return true;
    }

    return false;
}

bool isTie(Game& game) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game.board[i][j] != 'X' && game.board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

void clearScreen() {
  system("CLS");
}
