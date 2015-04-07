#include "Player.h"

Player::Player(bool firstPlayer){
    _type = 0;
    _isFirstPlayer = firstPlayer;
    brain = MLMachine();
    srand(time(0));
}

Player::Player(int typeInit, bool firstPlayer){
    _type = typeInit;
    _isFirstPlayer = firstPlayer;
    brain = MLMachine(firstPlayer, 0.5);
    srand(time(0));
}

int Player::choose(node * currBoard){
    switch (_type){
        case 1:
            return chooseHuman();
            break;
        case 2:
            cout << "here" << currBoard;
            return chooseML(currBoard);
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

int Player::chooseRandom(){
    return rand() % 9;
}

int Player::chooseHuman(){
    int choose;
    std::cin >> choose;
    return choose;
}

int Player::chooseML(node * currBoard){
    return brain.choose(currBoard);
}


