#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <cstdlib>
#include "Board.h"
#include "Player.h"

int main(int argc, char *argv[])
    //argv=arguments
    //argc=number of arguments
{
    bool firstPlayerTurn;
    std::cout << "How many games would you like to play?" << std::endl;
    int numGame, count=0;
    std::cin >> numGame;

    Board board;

    int oneType, twoType;

    std::cout << "Random:0 Human:1 ML:2" << std::endl;
    std::cout << "Please choose type for Player 1:" << std::endl;
    std::cin >> oneType;

    std::cout << "Please choose type for Player 2:" << std::endl;
    std::cin >> twoType;

    Player one(oneType), two(twoType);
startGame:

    firstPlayerTurn = true;

    while(!board.win()) {
        int position;
choose:
        std::cout << "Done" << std::endl;

        std::cout << "Player " << (firstPlayerTurn ? "1" : "2") << std::endl;
        std::cout << "Please enter a position (0 to 8)" << std::endl;
        if(firstPlayerTurn)
            position = one.choose();
        else
            position = two.choose();

        if(!board.setPosition(position, firstPlayerTurn)) goto choose;
        board.draw();
        board.testDraw();
        firstPlayerTurn=!firstPlayerTurn;
    }

    if(board.win()==1){
        std::cout << "Tie!" << std::endl;
    }
    else{
        firstPlayerTurn=!firstPlayerTurn;
        std::cout << "Player " << (firstPlayerTurn ? "1" : "2") << " won!" << std::endl;
    }

    board.resetBoard();
    system("clear");

    count++;
    if(count<numGame)
        goto startGame;

    return 0;
}
