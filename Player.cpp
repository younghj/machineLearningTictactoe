#include "Player.h"

Player::Player(bool firstPlayer)
{
    type = 0;
    isFirstPlayer = firstPlayer;
}

Player::Player(int typeInit, bool firstPlayer)
{
    type = typeInit;
    isFirstPlayer = firstPlayer;
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

bool Player::isPlayerOne(){
    return isFirstPlayer;
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


