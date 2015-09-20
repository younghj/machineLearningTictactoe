#include "Player.h"

int smartRandHelper(node* board, int zeroPos);

Player::Player(bool firstPlayer){
    _type = 0;
    _isFirstPlayer = firstPlayer;
    brain = MLMachine();
    srand(time(0));
}

Player::Player(int typeInit, bool firstPlayer, double trainingRate){
    _type = typeInit;
    _isFirstPlayer = firstPlayer;
    brain = MLMachine(firstPlayer, trainingRate);
    srand(time(0));
}

double* Player::getMLHypothesis(){
    return brain.getHypothesis();
}

void Player::setMLHypothesis(double *hyp){
    brain.setHypothesis(hyp);
}

int Player::choose(node * currBoard){
    switch (_type){
        case 1:
            return chooseHuman();
            break;
        case 2:
            return chooseML();
            break;
        default:
            return chooseRandom(currBoard);
    }
}

int Player::getType(){
    return _type;
}

bool Player::isPlayerOne(){
    return _isFirstPlayer;
}

int Player::chooseRandom(node * currBoard){
    int track[5], counter=0;
    for(int i =0; i<8;i++){
        if(abs(currBoard->tracker[i])==2){
            track[counter]=i;
            counter++;
        }
    }
    if(counter==0){
        int pos= rand()%9;
        while(currBoard->board[pos]!=0){
            pos= rand()%9;
        }
        return pos;
    }
    int availablePositions[5];
    for(int i=0;i<counter;i++){
        availablePositions[i]= smartRandHelper(currBoard,track[i]);
    }
    if(counter==1) return availablePositions[0];
    return availablePositions[rand()%counter];
}

int smartRandHelper(node * board,int zeroPos){
    int pos=9;
    int * testBoard = board->board;
    if(zeroPos<3){
        for(int i=zeroPos*3;i<zeroPos*3+3;i++){
            if(testBoard[i]==0)
                return i;
        }
    }else if(zeroPos<6){
        for(int i=zeroPos-3;i<zeroPos+4;i+=3){
            if(testBoard[i]==0)
                return i;
        }
    }else if(zeroPos==6){
        for(int i=0;i<9;i+=4){
            if(testBoard[i]==0)
                return i;
        }
    }else{
        for(int i=2;i<7;i+=2){
            if(testBoard[i]==0)
                return i;
        }
    }

    return pos;
}

int Player::chooseHuman(){
    int choose;
    std::cin >> choose;
    return choose;
}

int Player::chooseML(){
    int pos = brain.choose();
    return pos;
}

void Player::seeOpponentMove(int pos){
    brain.registerOpponentMove(pos);
}
