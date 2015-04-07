//change things to curses.h
#include "Global.h"
#include <string>
#include <cmath>
#include "Board.h"
#include "Player.h"
//#include <dlib/svm.h>

using namespace std;

int main(int argc, char *argv[])
    //argv=arguments
    //argc=number of arguments
{
    //system("clear");
    bool firstPlayerTurn=true;
    int numGame, count=0, position;
    int scoreKeeper[3]={0};
    int oneType, twoType;
    int win;
    Board board;

    cout << "How many games would you like to play?" << endl;
    cin >> numGame;
    oneType = 0;
    twoType = 2;

    //cout << "Random:0 Human:1 ML:2" << endl;
    //cout << "Please choose type for Player 1:" << endl;
    //cin >> oneType;
    //cout << "Please choose type for Player 2:" << endl;
    //cin >> twoType;

    Player one(oneType,firstPlayerTurn), two(twoType,!firstPlayerTurn);
    clock_t startTime = clock();

    if(numGame < 1) goto end;


startGame:
    win=2;
    while(win==2) {
choose:
        node* tail = board.getHistory()->tail;
        //drawNode(tail);
        position = (firstPlayerTurn?one:two).choose(tail);

        if(board.positionCheck(position)) goto choose;
        board.setPosition(position, firstPlayerTurn);

        board.draw();
        firstPlayerTurn=!firstPlayerTurn;
        win = board.win(firstPlayerTurn);
    }

    if(one.getType()==2) one.brain.updateHypothesis(board.getHistory());
    if(two.getType()==2) two.brain.updateHypothesis(board.getHistory());

    if(win == 0){
        cout << "Tie!" << endl;
        scoreKeeper[2]+=1;
    }
    else{
        cout << "Player " << (!firstPlayerTurn ? "1" : "2") << " won!" << endl;
        scoreKeeper[firstPlayerTurn]+=1;
    }

    board.resetBoard();

    cout << count + 1 << "game" << endl;
    cout << "Player 1: " << scoreKeeper[0] << endl;
    cout << "Player 2: " << scoreKeeper[1] << endl;
    cout << "Tie: " << scoreKeeper[2] << endl;
    count++;
    if(count<numGame)
        goto startGame;

end:
    clock_t end = clock();

    double elapsed = double(end-startTime)/CLOCKS_PER_SEC;
    cout << elapsed << endl;

    return 0;
}
