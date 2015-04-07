#ifndef PLAYER_H
#define PLAYER_H 

#include "MLMachine.h"

class Player
{
public:
    int choose(node * currBoard);
    Player(bool firstPlayer);
    Player(int type, bool firstPlayer);
    int getType();
    bool isPlayerOne();

    MLMachine brain;

private:
    int chooseRandom();
    int chooseHuman();
    int chooseML(node * currBoard);

    int _type;
    bool _isFirstPlayer;
};

#endif
