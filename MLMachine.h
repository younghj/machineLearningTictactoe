#ifndef MLMACHINE_H
#define MLMACHINE_H

#include "Global.h"

class MLMachine
{

public:
    MLMachine();
    node* getSuccessors();
    double evaluateBoard();

private:
    /* data */
    int _trainingRate;
    int _hypothesis[8];
};

#endif
