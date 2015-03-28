#ifndef PLAYER_H
#define PLAYER_H 

#include "Global.h"

class Player
{
public:
    int choose();
    Player(bool firstPlayer);
    Player(int type, bool firstPlayer);
    int getType();
    bool isPlayerOne();

private:
    int chooseRandom();
    int chooseHuman();
    int chooseML();

    int type;
    bool isFirstPlayer;
};

#endif
