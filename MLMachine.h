#ifndef MLMACHINE_H
#define MLMACHINE_H

#include "Global.h"

class MLMachine
{

public:
    MLMachine();
    MLMachine(bool first, double rate);
    void updateHypothesis(root * history);
    int choose(node * currBoard);


private:
    /* data */
    double _trainingRate;
    double _hypothesis[8];
    bool _first;

    int getWinner(node * evalBoard);
    node* getSuccessors(node * currBoard);
    double evaluateBoard(node * evalBoard);
    int* getFeatures(node * featBoard);
    trainingSet* getTrainingSet(root * history);
    double absol(double n);
};

#endif
