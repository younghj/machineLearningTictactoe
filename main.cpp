//change things to curses.h
#include "Global.h"
#include <string>
#include <cmath>
#include "Board.h"
#include "Player.h"

using namespace std;

Player machine(0,0); // allow training rate to change;

int askForType(bool test=false);
double playGame(int totalNumberOfGames, Player * one, Player * two, double * hypothesis=0, bool verbose=false, int * score=0);
void optimizeTrainingRate(int totalNumberOfGames, double &mainRate);

int main()
{
    double mainRate;
    cout << "Test for best Training Rate? ";
    bool test;
    cin >> test;

    double * mainHypothesis=0;
    int totalNumberOfGames;

    if(test){
        cout << "How many games per iteration of testing? ";
        cin >> totalNumberOfGames;
        optimizeTrainingRate(totalNumberOfGames,mainRate);
    }
    else{
        cout << "How many games for training? ";
        cin >> totalNumberOfGames;

        cout << "Training Rate: ";
        cin >> mainRate;
        int twoType = askForType(true);

        machine.setTrainingRate(mainRate,true);
        Player two(twoType,mainRate);

        playGame(totalNumberOfGames, &machine, &two, mainHypothesis);
    }


    while(true){
        cout << endl << endl;
        int otherPlayerType = askForType();
        Player other(otherPlayerType,mainRate);

        if(otherPlayerType!=3){
            cout << "How many games?" << endl;
            cin >> totalNumberOfGames;
        }else
            totalNumberOfGames=100;


        bool verbose = otherPlayerType==3;
        playGame(totalNumberOfGames, &machine, &other, mainHypothesis, verbose);

    }

    return 0;
}

//Functions

int askForType(bool test){
    int type;
    bool exitCondition;
    if(test)
        cout << "Dumb_Random:1 Smart_Random:2" << endl;
    else
        cout << "Dumb_Random:1 Smart_Random:2 Human:3" << endl;

    do{
        cout << "Please choose a type: " ;
        cin >> type;
        exitCondition = (test && (type==1 || type==2)) || (!test && type>0 && type<4);
    }while(!exitCondition);

    return type;
}

double playGame(int totalNumberOfGames, Player * one, Player * two, double * hypothesis, bool verbose, int * score){

    bool firstPlayerTurn=true, firstPlayerStartedGame=true;
    int position, scoreKeeper[3]={0};
    Board board;

    for(int playedGames=0;playedGames<totalNumberOfGames;playedGames++){
        int whoWon=2;
        if(verbose) board.draw();
        while(whoWon==2) {
            do{
                node* tail = board.getHistory()->tail;
                position = (firstPlayerTurn?one:two)->choose(tail);
            }while(board.positionCheck(position));

            board.setPosition(position, firstPlayerTurn);

            if(one->getType()==0 && !firstPlayerTurn)
                one->seeOpponentMove(position);

            if(verbose) board.draw();
            firstPlayerTurn=!firstPlayerTurn;
            whoWon = board.win(firstPlayerTurn);
        }

        if(one->getType()==0) {
            one->updateHypothesis();
        }

        if(whoWon == 0){
            if(verbose) cout << "Tie!" << endl;
            scoreKeeper[2]+=1;
            firstPlayerStartedGame=!firstPlayerStartedGame;
            firstPlayerTurn = firstPlayerStartedGame;
        }
        else{
            if(verbose) cout << "Player " << (!firstPlayerTurn ? "1" : "2") << " won!" << endl;
            scoreKeeper[firstPlayerTurn]+=1;
        }

        board.resetBoard();
        if(one->getType()==0) one->resetInternalBoard();

        if(playedGames+1==totalNumberOfGames){
            cout << "Player 1: " << scoreKeeper[0] << endl;
            cout << "Player 2: " << scoreKeeper[1] << endl;
            cout << "Tie: " << scoreKeeper[2] << endl;
        }
    }

    double ratio=0;
    ratio = scoreKeeper[0]/double(totalNumberOfGames);
    if(hypothesis){
        double * tempHypothesis = one->getMLHypothesis();
        for(int i=0; i<8 ;i++) hypothesis[i]=tempHypothesis[i];
        for(int i=0; i<3 ;i++) score[i] = scoreKeeper[i];
    }

    cout << "Ratio: " << ratio << endl << endl;
    return ratio;
}

void optimizeTrainingRate(int totalNumberOfGames, double &mainRate){
    bool manualTest;
    int consecutiveLow = 0; 
    double bestTraining,
           currRate,
           bestOne,
           bestTwo,
           bestTie,
           ratio,
           upRate,
           maxRate,
           bestRatio=0;
    double bestHypothesis[8]={0};

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
        currRate = 0.0001;
        upRate = 0.0001;
        maxRate = 0.01;
    }

    int twoType = askForType(true);

    for(double rateBeingTested=currRate;
            rateBeingTested<maxRate+upRate && consecutiveLow < 10;
            rateBeingTested+=upRate){

        Player one(0,rateBeingTested),
               two(twoType,rateBeingTested);
        double testHypothesis[8]={0};
        int endScore[3]={0};

        ratio = playGame(totalNumberOfGames, &one, &two, testHypothesis, false, endScore);

        if(ratio > bestRatio){
            bestRatio = ratio;
            bestTraining = rateBeingTested;
            bestOne= endScore[0];
            bestTwo= endScore[1];
            bestTie = endScore[2];
            consecutiveLow = 0;
            for(int i=0; i<8;i++)
                bestHypothesis[i] = testHypothesis[i];
        }else{
            consecutiveLow++;
        }
    }

    cout << "best trainingrate is " << bestTraining << endl;
    cout << "best player1:" << bestOne << endl;
    cout << "best player2:" << bestTwo << endl;
    cout << "best tie:" << bestTie << endl;
    cout << "best ratio:" << bestRatio << endl;

    mainRate = bestTraining;
    machine.setTrainingRate(bestTraining, true);
    machine.setMLHypothesis(bestHypothesis);
}

