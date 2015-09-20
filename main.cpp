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
    bool test, manualTest;
    cout << "Test for best Training Rate?" << endl;
    cin >> test;

    int consecutiveLow = 0; 
    double bestTraining=0,
           bestRatio=0,
           currRate=0,
           bestOne=0,
           bestTwo=0,
           bestTie=0,
           bestHypothesis[8],
           ratio,
           upRate,
           maxRate;

    if(test){
        cout << "Do you want to manually set the values(1-manual, 0-preset value testing)";
        cin >> manualTest;

        if(manualTest){
            cout << "Starting rate:";
            cin >> currRate;
            cout << "Rate at which training rate goes up:";
            cin >> upRate;
            cout << "Ending rate:";
            cin >> maxRate;
        }else{
            currRate = 0.001;
            upRate = 0.001;
            maxRate = 0.1;
        }
    }

    int numGame;
    cout << "How many games would you like to play?" << endl;
    cin >> numGame;

    clock_t startTime = clock();

repeat:
    bool firstPlayerTurn=true;
    bool firstPlayerStartedGame=true;
    int count=0, position;
    int scoreKeeper[3]={0};
    int oneType, twoType;
    int win;
    Board board;

    oneType = 2;
    twoType = 0;

    //cout << "Random:0 Human:1 ML:2" << endl;
    //cout << "Please choose type for Player 1:" << endl;
    //cin >> oneType;
    //cout << "Please choose type for Player 2:" << endl;
    //cin >> twoType;

    if((oneType == 2 || twoType == 2) && !test){
        cout << "Training Rate:";
        cin >> currRate;
    }else if(!test) currRate = 0;

    Player one(oneType,firstPlayerTurn,currRate), two(twoType,!firstPlayerTurn,currRate);

    if(numGame < 1) goto end;


startGame:
    firstPlayerStartedGame = firstPlayerTurn;
    win=2;
    while(win==2) {
choose:
        node* tail = board.getHistory()->tail;
        position = (firstPlayerTurn?one:two).choose(tail);

        if(board.positionCheck(position)) goto choose;
        board.setPosition(position, firstPlayerTurn);

        if(one.getType()==2 && !firstPlayerTurn) one.seeOpponentMove(position);
        if(two.getType()==2 && firstPlayerTurn) two.seeOpponentMove(position);

        board.draw();
        firstPlayerTurn=!firstPlayerTurn;
        win = board.win(firstPlayerTurn);
    }

    if(one.getType()==2) one.brain.updateHypothesis();
    if(two.getType()==2) two.brain.updateHypothesis();

    if(win == 0){
        cout << "Tie!" << endl;
        scoreKeeper[2]+=1;
        firstPlayerStartedGame=!firstPlayerStartedGame;
        firstPlayerTurn = firstPlayerStartedGame;
    }
    else{
        cout << "Player " << (!firstPlayerTurn ? "1" : "2") << " won!" << endl;
        scoreKeeper[firstPlayerTurn]+=1;
    }

    board.resetBoard();
    if(one.getType()==2) one.brain.resetBoard();
    if(two.getType()==2) two.brain.resetBoard();

    cout << count + 1 << "game" << endl;
    cout << "Player 1: " << scoreKeeper[0] << endl;
    cout << "Player 2: " << scoreKeeper[1] << endl;
    cout << "Tie: " << scoreKeeper[2] << endl;
    count++;

    if(count<numGame)
        goto startGame;
    else if(test){
        double* tempHyp;
        if(oneType==2 || (oneType==2&&twoType==2)) {
            ratio = scoreKeeper[0]/double(numGame) + scoreKeeper[2]*0.1/double(numGame);
            tempHyp = one.getMLHypothesis();
        }
        else if(twoType==2) {
            ratio = scoreKeeper[1]/double(numGame) + scoreKeeper[2]*0.1/double(numGame);
            tempHyp = two.getMLHypothesis();
        }
        else{
            ratio = 0;
        }

        if(ratio > bestRatio){
            bestRatio = ratio;
            bestTraining = currRate;
            bestOne= scoreKeeper[0];
            bestTwo= scoreKeeper[1];
            bestTie = scoreKeeper[2];
            consecutiveLow = 0;
            for(int i=0; i<8;i++) bestHypothesis[i] = tempHyp[i];
        }else{
            consecutiveLow++;
        }

        if(currRate < maxRate && consecutiveLow < 10){
            currRate += upRate;
            goto repeat;
        }else{
            cout << "best trainingrate is " << bestTraining << endl;
            cout << "best player1:" << bestOne << endl;
            cout << "best player2:" << bestTwo << endl;
            cout << "best tie:" << bestTie << endl;
        }
    }


end:
    clock_t end = clock();

    double elapsed = double(end-startTime)/CLOCKS_PER_SEC;
    cout << elapsed << endl;

    bool play;
    cout << "Do you want to play with the brain?(0 or 1)";
    cin >> play;
    if(!test) bestTraining = currRate;

    if(play){
        Player human(1,true,bestTraining), machine(2,false,bestTraining);

        if(test){
            machine.setMLHypothesis(bestHypothesis);
        }
        else if(oneType==2 || twoType==2){
            if(oneType==2)
                machine.setMLHypothesis(one.getMLHypothesis());
            else
                machine.setMLHypothesis(two.getMLHypothesis());
        }

startGame_play:

        board.draw();

        win=2;
        while(win==2) {

choose_play:
            node* tail = board.getHistory()->tail;
            position = (firstPlayerTurn?human:machine).choose(tail);

            if(board.positionCheck(position)) goto choose_play;
            board.setPosition(position, firstPlayerTurn);

            if(machine.isPlayerOne() != firstPlayerTurn) machine.seeOpponentMove(position);

            board.draw();
            firstPlayerTurn=!firstPlayerTurn;
            win = board.win(firstPlayerTurn);
        }

        machine.brain.updateHypothesis();

        if(win == 0){
            cout << "Tie!" << endl;
        }
        else{
            cout << "Player " << (!firstPlayerTurn ? "1" : "2") << " won!" << endl;
        }

        board.resetBoard();
        if(machine.getType()==2) machine.brain.resetBoard();
        goto startGame_play;

    }

    return 0;
}
