#ifndef PLAYER_H
#define PLAYER_H 

#include "MLMachine.h"

class Player
{
public:
    int choose(node * currBoard);
    Player(bool firstPlayer);
    Player(int type, bool firstPlayer, double trainingRate);
    int getType();
    bool isPlayerOne();
    double* getMLHypothesis();
    void setMLHypothesis(double* hyp);
    void seeOpponentMove(int pos);

    MLMachine brain;

private:
    int chooseRandom(node* currBoard);
    int chooseHuman();
    int chooseML();

    int _type;
    bool _isFirstPlayer;
};

#endif
