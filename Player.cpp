#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>


Player::Player()
{
    type = 0;
}

Player::Player(int typeInit)
{
    type = typeInit;
}

int Player::choose()
{
    switch (type){
        case 1:
            return chooseHuman();
            break;
        case 2:
            return chooseML();
            break;
        default:
            return chooseRandom();
    }
}

int Player::getType(){
    return type;
}

int Player::chooseRandom()
{
    return rand() % 9;
}

int Player::chooseHuman()
{
    int choose;
    std::cin >> choose;
    return choose;
}

int Player::chooseML()
{


    return -1;
}
