#ifndef CONNECT4BOARD_H
#define CONNECT4BOARD_H

#define NROWS 6
#define NCOLS 7
class connect4board {
    private:
        int nrows = NROWS;
        int ncols = NCOLS;
        int nchips = 0;
        int boardState[NROWS][NCOLS]; // array representing the connct 4 board
        
        int topIndex[NCOLS]; // array representing the lowest available row in each column (to fill)
        
        
    public:
        
        connect4board();
        
        void printBoard(); // displays the board in the terminal

        int addChip(int, int);
        /* returns: -1 if chip cannot be added
                    0 if no win
                    -2 if tie
                    player number if a player wins
        */

        int checkWin(int); // checks if the most recent move results in a win 
        /* returns: 0 if no win
                    -2 if tie
                    player number if a player wins
        */
        void resetBoard();

};

#endif