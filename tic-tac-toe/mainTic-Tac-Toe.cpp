// This is main file
// keep both [ .exe ] versions of the game modes in the same directory
// run this file
#include<iostream>
#include<cstdlib>

using namespace std;

int getGameMode();

void clearScreen() {
    system("CLS");
}

int main(){
    int gameMode = getGameMode();

    if(gameMode == 1){
        cout << "Running the Player vs Player mode...\n";
        clearScreen();
        //for executing the pvp mode
        system("pvp-version.exe");
    }else if(gameMode == 2){
        cout << "Running the Player vs AI mode...\n";
        clearScreen();
        // for executing the pvAI mode 
        system("pvAI.exe");
    }else{
        cout << "invalid game mode selected\n";
    }

    return 0;

}


int getGameMode(){
    int mode;
    cout << "Select game mode\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs AI\n";
    cout << "Enter Game mode (1 or 2): ";
    cin >> mode;
    return mode;
}