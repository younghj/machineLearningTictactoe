#include "Board.h"

Board::Board()
{
    for (int i = 0; i < 4; ++i) _scoreKeeper[i]=0;

    _currGameHistory = new root;
    _currGameHistory->head = NULL;
    _currGameHistory->tail = NULL;
    resetBoard();

    node *currBoard = new node;
    currBoard->board = copyArray(_board,sizeof(_board));

    currBoard->tracker = copyArray(_boardTracker,sizeof(_boardTracker));
    currBoard->zeros = copyArray(_zeroTracker,sizeof(_zeroTracker));
    currBoard->next = NULL;


    _currGameHistory->head = currBoard;
    _currGameHistory->tail = currBoard;
    _currGameHistory->data = 1;
}

root* Board::getHistory(){
    return _currGameHistory;
}

bool Board::positionCheck(int position)
{
    return abs(_board[position]);
}

void Board::setPosition(int position, bool firstPlayerTurn)
{
    int addVal = firstPlayerTurn ? 1 : -1;

    _board[position] = addVal;
    _boardTracker[position/3] += addVal;
    _zeroTracker[position/3]--;

    _boardTracker[(position%3)+3] += addVal;
    _zeroTracker[(position%3)+3]--;

    if(position/4.0 == position/4){
        _boardTracker[6] += addVal;
        _zeroTracker[6]--;
    }

    if(position%2==0 && position < 7 && position!=0){
        _boardTracker[7] += addVal;
        _zeroTracker[7]--;
    }

    node *currBoard = new node;
    currBoard->data = position;
    currBoard->board = copyArray(_board,sizeof(_board));
    currBoard->tracker = copyArray(_boardTracker,sizeof(_boardTracker));
    currBoard->zeros = copyArray(_zeroTracker,sizeof(_zeroTracker));
    currBoard->next = NULL;

    _currGameHistory->tail->next = currBoard;
    _currGameHistory->tail = currBoard;
    _currGameHistory->data += 1;
}

int Board::win(bool turn)
{
    for (int i = 0; i < 8; ++i)
        if(abs(_boardTracker[i])==3) return (!turn?1:-1); //someone won

    for (int i = 0; i < 9; ++i){
        if(_board[i]==0){
            return 2; //keep on going
        } 
    }
    
    return 0;//tie
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
    for (int i = 0; i < 9; ++i) _board[i]=0;
    for (int i = 0; i < 8; ++i) _boardTracker[i]=0;
    for (int i = 0; i < 8; ++i) _zeroTracker[i]=3;
    resetHistory();
}

void Board::resetHistory()
{
    if(_currGameHistory->tail==_currGameHistory->head){ return; }
    _currGameHistory->tail = _currGameHistory->head;
    _currGameHistory->data = 1;

    deleteNode(_currGameHistory->head->next);
    _currGameHistory->head->next=NULL;
}

char Board::drawSymbol(int val)
{
    switch(_board[val]){
        case -1 : return 'x';
        case 1: return 'o';
        default: return '0'+val;
    }
}

