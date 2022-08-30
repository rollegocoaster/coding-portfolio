#include <iostream>
#include "connect4board.h"

using namespace std;

connect4board::connect4board(){
    for(int i = 0; i < nrows; i++){
        for(int j = 0; j < ncols; j++){
            boardState[i][j] = 0;
        }
    }
    for(int i = 0; i< ncols; i++){
        topIndex[i] = 0;
    }
}

void connect4board::printBoard(){
    /* prints board to console
    */
    for(int i = nrows; i>=0; i--){
        for(int j = 0; j<ncols; j++){
            if(i==nrows){
                cout << "  " << j << "  ";
            } else {
                switch(boardState[i][j]){
                    case 0: cout << " --- ";
                    break;
                    case 1: cout << " (|) ";
                    break;
                    case 2: cout << " (2) ";
                }
            }
        }
        cout << endl;
    }
}

int connect4board::addChip(int col, int player){
    /* inputs a column index and a player and places a 
    chip in the next available row on that column. then checks
    if there is a winner
    Returns -1 if the column is full else returns
    the result of checkWin(index)

    */
    if(topIndex[col] >= nrows){
        return -1;
    } else {
        nchips++;
        boardState[topIndex[col]][col] = player;
        //cout << boardState[NROWS-1][col] << endl;
        int result = 0;
        topIndex[col]++;
        if(nchips >= 7)
            result = checkWin(col);
        //cout << boardState[NROWS-1][col] << endl;
        return result;

    }
}

int connect4board::checkWin(int col){
    /* inputs the row of the most recent move and checks if
    it results in a win 
    Returns 0 if it the board is not in a win state
    Returns -2 if the board is not in a win state and there are no moves left
    else returns the player number who won
    */
   
    int row = topIndex[col];
    //cout << row << endl;
    if(boardState[row][col] == 0) row--;
    int currPlayer = boardState[row][col];

    // check for win across row
    int tempcol;
    int numInARow = 0;
    for(tempcol = col; tempcol<ncols && boardState[row][tempcol] == currPlayer; tempcol++){
        numInARow ++;
        if(numInARow == 4){
            return currPlayer;
        }
    }
    for(tempcol = col-1; tempcol>=0 && boardState[row][tempcol] == currPlayer; tempcol--){
        numInARow ++;
        if(numInARow == 4){
            return currPlayer;
        }
    }
    // check if there is a win across the column
    if (row>=3){
        numInARow = 0;
        for(int tempRow = row; tempRow>=0; tempRow--){
            if(boardState[tempRow][col] != currPlayer){
                //cout << "test" << endl;
                break;
            }
            numInARow ++;
            
            //cout << numInARow << " " << tempRow << endl;
            if(numInARow == 4){
                return currPlayer;
            }
        }
    }
    // check diagonals
    numInARow = 0;
    for(int i = 0; row+i<nrows && col+i <ncols; i++){
        if(boardState[row+i][col+i] != currPlayer){
            break;
        }
        numInARow ++;
        if (numInARow == 4){
            return currPlayer;
        }
    }
    
    for(int i = -1; row+i>=0 && col+i>=0; i--){
        if(boardState[row+i][col+i] != currPlayer){
            break;
        }
        numInARow ++;
        if (numInARow == 4){
            return currPlayer;
        }
    }
    
    numInARow = 0;
    for(int i = 0; row+i<nrows && col-i >= 0; i++){
        if(boardState[row+i][col-i] != currPlayer){
            break;
        }
        numInARow ++;
        if (numInARow == 4){
            return currPlayer;
        }
    }
    
    for(int i = -1; row+i>=0 && col-i<ncols; i--){
        if(boardState[row+i][col-i] != currPlayer){
            break;
        }
        numInARow ++;
        if (numInARow == 4){
            //cout << "NIAR" <<  numInARow << endl;
            return currPlayer;
        }
    }
    for(int i = 0; i<ncols; i++){ // check if board is full
        if(topIndex[i] < nrows){
            return 0;
        }
    }
    return -2; // draw
}

void connect4board::resetBoard(){
     for(int i = 0; i < 6; i++){
        for(int j = 0; j<7; j++){
            boardState[i][j] = 0;
        }
    }
    for(int i = 0; i<7; i++){
        topIndex[i] = 0;
    }
    nchips = 0;
}