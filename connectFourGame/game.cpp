#include <iostream>
#include "connect4board.h"
#include <string>
#include <stdlib.h>     /* srand, rand */
using namespace std;

int randomSelector(int player, connect4board* board){
    int result;
    do{
        int choice = rand()%7;
        result = board->addChip(choice,player);
    }while(result == -1);
    return result;
}


int main(){

    connect4board board;
    char userInput;
    int player = 1;
    int result;
    char mode;
    cout << "how do you want to play?" << endl;
    cout << "1: player vs player" << endl;
    cout << "2: player vs randomSelector" << endl;
    cout << "3: randomSelector vs randomSelector" << endl;
    cin >> mode;
    srand(time(NULL));

    while(true){
        // print the board to terminal and get input from player
        
        board.printBoard();
        if( mode != '3'){
            cout << "player " << player << " select which column to put a chip (or input anything else to quit):";
            cin >> userInput;
            if(userInput >= '0' && userInput <= '6'){
                int col = int(userInput) - 48;
                result = board.addChip(col,player);
                // if the player adds a chip to a full column continue asking for input until user inputs a column that is not fulll
                while(result == -1){
                    cout << "oops you cant put a chip there " << endl ;
                    cout << " player " << player << " select which column to put a chip:";
                    cin >> userInput;
                    if(userInput >= '0' && userInput <= '6'){
                        int col = int(userInput) - 48;
                        result = board.addChip(col,player);
                    } else { 
                        return -1;
                        cout << "quitting" << endl;
                    }
                }
            } else { // if player inputs a character that doesn't represent a column stop the game
                cout << "quitting" << endl;
                return -1;
            }
        } else {
           result = randomSelector(player,&board);
           cout << endl << "============================" << endl;
        }
        if(result > 0){
            cout << endl << "PLAYER " << player << " WINS" << endl;
            board.printBoard();
            cout << "PLAYER " << player << " WINS" << endl;
            
            return player; 
        } else if (result == -2) { // if result was a draw end the game
            cout << "DRAW" << endl;
            board.printBoard();
            return -2;
        }
        switch(mode) {
            default:
            case '1': // switch player
                player = player == 2 ? 1: 2;
                break;
            case '2': // player 2 picks randomly
                if(randomSelector(2,&board) > 0){
                    cout << endl << "PLAYER " << player << " WINS" << endl;
                    board.printBoard();
                    cout << "PLAYER " << player << " WINS" << endl;
                    
                    return player; 
                }
                break;

        }
    }

    return -1; //
}