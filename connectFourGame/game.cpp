#include <iostream>
#include "connect4board.h"
#include "cfouropponent.h"
#include <string>
#include <stdlib.h>     /* srand, rand */
using namespace std;




void checkGameOver(int result, int player, connect4board board){
    if(result > 0){
            cout << endl << "PLAYER "<< player << " WINS" << endl;
            board.printBoard();
            cout << "PLAYER " << player << " WINS" << endl;
            exit(0);
        } else if (result == -2) { // if result was a draw end the game
            cout << "DRAW" << endl;
            board.printBoard();
            exit(0);
        } else if (result == -1) {
            cout << "quitting" << endl;
            exit(0);
        }
}

int main(){
    string line;
    char userInput, mode;
    int turn = 0;
    int result, player = 1;
    cout << "how do you want to play?" << endl;
    cout << "1: player vs player" << endl;
    cout << "2: player vs randomSelector" << endl;
    cout << "3: randomSelector vs randomSelector" << endl;
    cout << "4: player vs AI" << endl;
    cout << "5: AI vs AI" << endl;
    getline(cin,line);
    mode = line[0];
    srand(time(0));
    cfouropponent cfourgame(mode);
    while(true){
        // print the board to terminal and get input from player
        cout << "round " << turn++ << endl << endl;
        cfourgame.board.printBoard();
        if( mode != '3' && mode != '5'){
            GETINPUT:
            cout << "player 1 select which column to put a chip (or input anything else to quit):";
            cin >> userInput;
            if(userInput >= '0' && userInput <= '6'){
                int col = int(userInput) - 48;
                result = cfourgame.board.addChip(col,player);
                // if the player adds a chip to a full column continue asking for input until user inputs a column that is not fulll
                if(result == -1){
                    cout << "oops you cant put a chip there " << endl ;
                    goto GETINPUT;
                }
            } else { // if player inputs a character that doesn't represent a column stop the game
                cout << "quitting" << endl;
                return -1;
            }
        } else {
           cout << "press enter to continue" << endl;
           getline(cin,line);
           if(line == "quit"){
                exit(0);
           }
           result = cfourgame.opponentPlay(1);
           cout << endl << "============================" << endl;
        }
        checkGameOver(result, 1, cfourgame.board);
        result = cfourgame.opponentPlay();
        checkGameOver(result,2,cfourgame.board);
        
    }

    return -1; //
}