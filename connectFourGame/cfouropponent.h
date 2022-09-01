#include "connect4board.h"

#ifndef CFOUROPPONENT_H
#define CFOUROPPONENT_H

class cfouropponent {
    public: 
        connect4board board;
        cfouropponent(char);
        int opponentPlay(int = 2);
    private:
        char mode;
};

#endif