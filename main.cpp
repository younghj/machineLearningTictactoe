//change things to curses.h
#include "Global.h"
#include <string>
#include <cmath>
#include <ctime>
#include "Board.h"
#include "Player.h"
//#include <dlib/svm.h>

using namespace std;

int main(int argc, char *argv[])
    //argv=arguments
    //argc=number of arguments
{
    //system("clear");
    bool firstPlayerTurn;
    int numGame, count=0, position;
    int scoreKeeper[3]={0};
    int oneType, twoType;
    Board board;

    cout << "How many games would you like to play?" << endl;
    cin >> numGame;
    cout << "Random:0 Human:1 ML:2" << endl;
    cout << "Please choose type for Player 1:" << endl;
    cin >> oneType;
    cout << "Please choose type for Player 2:" << endl;
    cin >> twoType;

    Player one(oneType), two(twoType);
    firstPlayerTurn = true;
    clock_t startTime = clock();

startGame:
   while(!board.win()) {
choose:
        if(firstPlayerTurn) position=one.choose();
        else position=two.choose();

        if(board.positionCheck(position)) goto choose;

        board.setPosition(position, firstPlayerTurn);
        board.draw();
        //board.testDraw();
        firstPlayerTurn=!firstPlayerTurn;
    }

    if(board.win()==1){
        cout << "Tie!" << endl;
        scoreKeeper[2]+=1;
    }
    else{
        cout << "Player " << (!firstPlayerTurn ? "1" : "2") << " won!" << endl;
        scoreKeeper[firstPlayerTurn]+=1;
    }

    board.resetBoard();
    //system("clear");

    cout << count + 1 << "game" << endl;
    cout << "Player 1: " << scoreKeeper[0] << endl;
    cout << "Player 2: " << scoreKeeper[1] << endl;
    cout << "Tie: " << scoreKeeper[2] << endl;
    count++;
    if(count<numGame)
        goto startGame;

    clock_t end = clock();
    
    double elapsed = double(end-startTime)/CLOCKS_PER_SEC;
    cout << elapsed << endl;

    return 0;
}
