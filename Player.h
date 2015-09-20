#ifndef PLAYER_H
#define PLAYER_H 

#include "MLMachine.h"

class Player
{
public:
    int choose(node * currBoard);
    Player();
    Player(int type, double trainingRate);
    int getType();
    bool isPlayerOne();
    double* getMLHypothesis();
    void setMLHypothesis(double* hyp);
    void seeOpponentMove(int pos);
    void updateHypothesis();
    void resetInternalBoard();
    void setTrainingRate(double rate, bool reset);


private:
    int chooseRandom(node* currBoard);
    int chooseDumbRandom();
    int chooseHuman();
    int chooseML();

    int _type;
    MLMachine _brain;
};

#endif
