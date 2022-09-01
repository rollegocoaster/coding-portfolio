#include <iostream>
#include "cfouropponent.h"
#include "connect4board.h"
#include <vector>

using namespace std;

cfouropponent::cfouropponent(char m){
    mode = m;
}

 int parse(int r, int c, int player, int inArow, int dirr, int dirc, connect4board board,bool change=false,int iteration=1){
        
        if(r < 0 || c < 0 || r > NROWS-1 || c > NCOLS-1) return inArow;
        
        int chip = board.getBoardVal(r, c);
        if(chip == player){
            inArow++;
            return parse(r+dirr,c+dirc,player,inArow,dirr,dirc,board,iteration=iteration+1);
        } else if (chip == 0 || change || iteration!=1)
            return inArow; 
        else
            return -parse(r+dirr,c+dirc,chip,inArow,dirr,dirc,board,change=true,iteration=iteration+1)-1;
}

int greedyAI(connect4board board, int player){
    /*
    * greedyAI Idea: parse through the available options and assign each move a value based on how many chips in a row there are 
    *          (e.g ) 3 ai chips in a row = score of 3
    *                 3 opponent chips in a row = score of -3
    *  then select the option with the greatest absolute value (preferring positive values if there is a tie)
    *  and if there is a tie among multiple values select one at random
    */         
    vector<int> bestMoves;
    int nInaRow[NCOLS] = {0,0,0,0,0,0,0};
    int maxtemp, row, max;
    int d[4][2] = {{-1,0},{0,1},{1,1},{-1,1}};
    for(int col=0; col<NCOLS; col++){
        maxtemp = 0;
        row = board.getTopIndexOf(col);
        if(row >= NROWS) {
            cout << "I can't put that there" << endl;
            continue;
        }
        int temp, temp2;
        // parse through each direction and get what the greatest number of chips in a row is
        for(int i=0; i<4; i++){
            temp = parse(row+d[i][0],col+d[i][1],player,0,d[i][0],d[i][1],board);
            if(temp >= 0) temp++;
            else temp--;
            int temp2 = parse(row-d[i][0],col-d[i][1],player,0,-d[i][0],-d[i][1],board);
            if((temp > 0) == (temp2>0)){
                temp+=temp2;
            } else 
                 if(abs(temp2) > abs(maxtemp)){
                    maxtemp=temp2;
            }
            if(abs(temp) > abs(maxtemp)){
                maxtemp=temp;
            }
        }
        // update the bestMoves vector if needed
        nInaRow[col] = maxtemp;
        if(abs(maxtemp) > abs(max)){
            bestMoves.clear();
            bestMoves.push_back(col);
            max = maxtemp;
        }else if(abs(maxtemp) == abs(max)){
            bestMoves.push_back(col);
            if(maxtemp<0){
                bestMoves.push_back(col);
            }
        }
    }
    // choose a random move from the list of best moves
    if (bestMoves.size() == 0){
        return rand()%NCOLS;
    } else {

        int choiceIndex = rand()%bestMoves.size();
        int choice = bestMoves[choiceIndex];
        return choice;
    }
}

int cfouropponent::opponentPlay(int player){
    int result;
    switch(mode){
        default:
        case '1': // second player
            GETINPUT: cout << "player "<< player << " select which column to put a chip";
            char userInput;
            int result;
            cin >> userInput;
            if(userInput >= '0' && userInput <= '6'){
                int col = int(userInput) - 48;
                result = board.addChip(col,player);
                // if the player adds a chip to a full column continue asking for input until user inputs a column that is not fulll
                if(result == -1){
                    cout << "oops you cant put a chip there " << endl;
                    goto GETINPUT;
                }
            } else {
                result = -1;
            }
        break;
        
        case '2':
        case '3': 
            do{
                int choice = rand()%7;
                result = board.addChip(choice,player);
            }while(result == -1);
            return result;
            break;
        case '5': // greedy ai vs greedyAI
        case '4': // player vs greedyAI
            do{
                int choice = greedyAI(board,player);
                result = board.addChip(choice,player);
            }while(result == -1);
            return result;
        
    }
    return result;
}