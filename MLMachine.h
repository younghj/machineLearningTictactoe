#ifndef MLMACHINE_H
#define MLMACHINE_H

#include "Global.h"
#include "Board.h"

class MLMachine
{

public:
    MLMachine();
    MLMachine(bool first, double rate);
    void updateHypothesis();
    int choose();
    double* getHypothesis();
    void setHypothesis(double* hyp);
    void registerOpponentMove(int pos);
    void resetBoard();

private:
    /* data */
    double _trainingRate;
    double _hypothesis[8];
    bool _first;
    Board _board;

    int getWinner(node * evalBoard);
    node* getSuccessors();
    double evaluateBoard(node * evalBoard);
    int* getFeatures(node * featBoard);
    trainingSet* getTrainingSet(root * history);
    double absol(double n);
};

#endif
