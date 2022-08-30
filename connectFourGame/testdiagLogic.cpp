#include <iostream>
#include "connect4board.h"
#include <string>
#include <cassert>
using namespace std;


int main(){
    connect4board board;
    for(int missing=0; missing < 4; missing++){
        for(int i=0; i< 4; i++){
            for(int j = 0; j<i; j++){
                board.addChip(i,2);
            }
            if(i != missing){
                assert(board.addChip(i,1)==0);
            }
        }
        assert(board.addChip(missing,1) == 1);
        board.resetBoard();
    }

    for(int missing=0; missing < 4; missing++){
        for(int i=0; i< 4; i++){
            for(int j = 3-i; j>0; j--){
                board.addChip(i,1);
            }
            if(i != missing){
                assert(board.addChip(i,2)==0);
            }
        }
        assert(board.addChip(missing,2) == 2);
        board.resetBoard();
    }
    cout << "passed diagonal tests" << endl;


    
}
