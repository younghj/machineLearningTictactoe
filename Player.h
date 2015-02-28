#ifndef PLAYER_H
#define PLAYER_H 
class Player
{
public:
    int choose();
    Player();
    Player(int type);
    int getType();
private:
    int chooseRandom();
    int chooseHuman();
    int chooseML();

    int type;
};

#endif
