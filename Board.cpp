#include "Board.h"

Board::Board()
{
    resetBoard();
    for (int i = 0; i < 4; ++i)
        scoreKeeper[i]=0;

    root *currGameHistory = new root;
    node *currBoard = new node;

    currBoard->data = board;
    currBoard->next = NULL;

    currGameHistory->head = currBoard;
    currGameHistory->tail = currBoard;
    currGameHistory->data = 1;

    draw();
}

bool Board::positionCheck(int position)
{
    return abs(board[position]);
}

void Board::setPosition(int position, bool firstPlayerTurn)
{
    int addVal = firstPlayerTurn ? -1 : 1;

    board[position] = addVal;
    boardTracker[position/3] += addVal;
    zeroTracker[position/3]--;

    boardTracker[(position%3)+3] += addVal;
    zeroTracker[(position%3)+3]--;

    if(position/4.0 == position/4){
        boardTracker[6] += addVal;
        zeroTracker[6]--;
    }

    if(position==2 || position==4 || position==6){
        boardTracker[7] += addVal;
        zeroTracker[7]--;
    }

    node *currBoard = new node;
    currBoard->data = board;
    currBoard->next = NULL;

    currGameHistory->tail->next = currBoard;
    currGameHistory->tail = currBoard;
    currGameHistory->data +=1;
}

int Board::win(){
    for (int i = 0; i < 8; ++i)
        if(abs(boardTracker[i])==3){
            return 2; //someone won
        } 

    for (int i = 0; i < 9; ++i)
        if(board[i]==0){
            return 0; //no one has won yet
        } 

    return 1;//tie
}


void Board::draw()
{
    //system("clear");
    cout << endl;
    for (int i = 0; i < 9; ++i)
    {
        cout << drawSymbol(i);
        if((i+1)%3){
            cout << "|";
        }
        else{
            cout << endl;
            cout << ((i!=8)?"-----":"");
            cout << endl;
        }
    }
}

void Board::resetBoard()
{
    for (int i = 0; i < 9; ++i) board[i]=0;
    for (int i = 0; i < 8; ++i) boardTracker[i]=0;
    for (int i = 0; i < 8; ++i) zeroTracker[i]=3;
    //resetHistory();
}

void Board::resetHistory(){
    if(!currGameHistory){ return; }

    currGameHistory->tail = currGameHistory->head;
    currGameHistory->data = 1;

    node* temp = currGameHistory->head;
    node* startBoard = temp;

    while(temp){
        startBoard = temp->next;
        delete temp;
        temp = startBoard;
    }
}

char Board::drawSymbol(int val)
{
    switch(board[val]){
        case -1 : return 'x';
        case 1: return 'o';
        default: return '0'+val;
    }
}

//test Function
void Board::testDraw(){
    for (int i = 0; i < 8; ++i) cout << boardTracker[i] << endl;
    for (int i = 0; i < 8; ++i) cout << zeroTracker[i] << endl;
}



