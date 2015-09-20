#include "MLMachine.h"

MLMachine::MLMachine(){
    _first=false;
    _trainingRate=0;
    for(int i=0;i<8;i++) _hypothesis[i]=0;
}


MLMachine::MLMachine(bool first, double rate)
{
    _first = first;
    _trainingRate = rate;
    for(int i=0;i<8;i++) _hypothesis[i]=0.5;
}

void MLMachine::registerOpponentMove(int pos){
   _board.setPosition(pos, false);
}

double MLMachine::absol(double n){
    const double ret[2]={n,-n};
    return ret[n<0];
}

double* MLMachine::getHypothesis(){
    return _hypothesis;
}

void MLMachine::setHypothesis(double *hyp){
    for(int i=0;i<8;i++)_hypothesis[i] = hyp[i];
}

void MLMachine::resetBoard(){
    _board.resetBoard();
}

void MLMachine::updateHypothesis(){
    root * history = _board.getHistory();
    trainingSet* sets = getTrainingSet(history);
    node* currNode = history->head;
    do {
        double h_x = evaluateBoard(currNode);
        for(int i=0;i<8;i++){
            _hypothesis[i] += _trainingRate * sets->features[i] * (sets->y - h_x)/8.0;
        }
        currNode = currNode->next;
        sets = sets->next;
        for(int i=0;i<8;i++) cout<<_hypothesis[i]<< " ";
        cout <<endl;
    } while(sets!=NULL);
}

int MLMachine::choose(){
    node* successors = getSuccessors();

    int bestPosition = successors->data;
    double bestScore = evaluateBoard(successors);

    while(successors->next!=NULL){
        successors = successors->next;
        double score =  evaluateBoard(successors);
        if(bestScore < score){
            bestScore = score;
            bestPosition = successors->data;
        }
    }

    _board.setPosition(bestPosition,true);
    return bestPosition;
}

node* MLMachine::getSuccessors(){
    node * currBoard = _board.getHistory()->tail;
    node* frontNode,* backNode;
    int* board = currBoard->board;

    frontNode = NULL;
    backNode = NULL;

    int insert = 1;
    for(int i=0; i<9; i++){
        if(board[i]==0){
            node* newNode = new node;
            newNode->data = i;

            int* tempBoard = new int;
            int* tempTracker = new int;
            int* tempZeros = new int;

            tempBoard = copyArray(board,9);
            tempBoard[i] = insert;

            tempTracker = copyArray(currBoard->tracker,8);
            tempZeros = copyArray(currBoard->zeros,8);

            tempTracker[i/3] += insert;
            tempZeros[i/3]--;

            tempTracker[(i%3)+3] += insert;
            tempZeros[(i%3)+3]--;

            if(i/4.0 == i/4){
                tempTracker[6] += insert;
                tempZeros[6]--;
            }
            if(i%2==0 && i < 7 && i!=0){
                tempTracker[7] += insert;
                tempZeros[7]--;
            }

            newNode->board = tempBoard;
            newNode->tracker = tempTracker;
            newNode->zeros = tempZeros;
            newNode->next = NULL;

            if(frontNode == NULL) frontNode= newNode;
            if(backNode != NULL) backNode->next = newNode;

            backNode = newNode;
        }
    }
    return frontNode;
}

double MLMachine::evaluateBoard(node * evalBoard){
    int* features = getFeatures(evalBoard);

    double evaluation=0;
    for(int i=0;i<8;i++) evaluation+=_hypothesis[i]*features[i]; 

    return evaluation;
}

int* MLMachine::getFeatures(node * featBoard){
    int * features = new int[8];
    features[0]=1;
    for(int i = 1; i < 8; i++) features[i] = 0;
    for(int i = 0; i < 8; i++){
        if(featBoard->zeros[i]==3) features[1]++;
        if(featBoard->zeros[i]==2) features[(featBoard->tracker[i]==1?2:3)]++;
        if(featBoard->zeros[i]==1 && featBoard->tracker[i]!=0)  features[(featBoard->tracker[i]==2?4:5)]++;
        if(featBoard->zeros[i]==0 && abs(featBoard->tracker[i])>1) features[(featBoard->tracker[i]==3?6:7)]++;
    }
    return features;
    /*
     * 0 - number of empty rows
     * 1 - number of rows with only one o
     * 2 - number of rows with only one x
     * 3 - number of rows with only two o
     * 4 - number of rows with only two x
     * 5 - number of rows with all o
     * 6 - number of rows with all x
     */
}

int MLMachine::getWinner(node * evalBoard){
    for(int i=0;i<9;i++){
        if(evalBoard->tracker[i]==3)return 1;
        if(evalBoard->tracker[i]==-3)return 0;
    }return -1;
}

trainingSet* MLMachine::getTrainingSet(root * history){
    //feature + evaluation
    trainingSet* firstSet;
    trainingSet* movingSet;
    node* currNode = history->head;
    int winner = getWinner(history->tail);

    for(int i=0;i<history->data;i++){
        int val=(winner?100:-100);
        trainingSet* currSet = new trainingSet;

        currSet->next = NULL;
        currSet->features = getFeatures(currNode);

        if(winner==-1) val = 0;

        //cout << "number of total games:" << history->data;

        if(i >= history->data-2)
            currSet->y = val;
        else{
            node* tempNode = currNode->next->next;
            currSet->y = evaluateBoard(tempNode);
            //currSet->y = evaluateBoard(currNode);
        }

        if(!i)
            firstSet = currSet;
        else
            movingSet->next = currSet;

        movingSet = currSet;
        currNode = currNode->next;
    }

    return firstSet;
}
