#include "Player.h"

Player::Player(bool firstPlayer)
{
    _type = 0;
    _isFirstPlayer = firstPlayer;
}

Player::Player(int typeInit, bool firstPlayer)
{
    _type = typeInit;
    _isFirstPlayer = firstPlayer;

    if(typeInit == 2){
        _brain = MLMachine();
    }
}

int Player::choose()
{
    switch (_type){
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
    return _type;
}

bool Player::isPlayerOne(){
    return _isFirstPlayer;
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


