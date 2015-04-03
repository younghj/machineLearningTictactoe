#include "Board.h"

Board::Board()
{
    for (int i = 0; i < 4; ++i)
        _scoreKeeper[i]=0;

    node *currBoard = new node;
    currBoard->board = copyArray(_board,sizeof(_board));
    currBoard->tracker = copyArray(_boardTracker,sizeof(_boardTracker));
    currBoard->zeros = copyArray(_zeroTracker,sizeof(_zeroTracker));
    currBoard->next = NULL;

    _currGameHistory = new root;
    _currGameHistory->head = currBoard;
    _currGameHistory->tail = currBoard;
    _currGameHistory->data = 1;

    resetBoard();
    draw();
}

bool Board::positionCheck(int position)
{
    return abs(_board[position]);
}

void Board::setPosition(int position, bool firstPlayerTurn)
{
    int addVal = firstPlayerTurn ? -1 : 1;

    _board[position] = addVal;
    _boardTracker[position/3] += addVal;
    _zeroTracker[position/3]--;

    _boardTracker[(position%3)+3] += addVal;
    _zeroTracker[(position%3)+3]--;

    if(position/4.0 == position/4){
        _boardTracker[6] += addVal;
        _zeroTracker[6]--;
    }

    if(position==2 || position==4 || position==6){
        _boardTracker[7] += addVal;
        _zeroTracker[7]--;
    }

    node *currBoard = new node;
    currBoard->board = copyArray(_board,sizeof(_board));
    currBoard->tracker = copyArray(_boardTracker,sizeof(_boardTracker));
    currBoard->zeros = copyArray(_zeroTracker,sizeof(_zeroTracker));
    currBoard->next = NULL;

    _currGameHistory->tail->next = currBoard;
    _currGameHistory->tail = currBoard;
    _currGameHistory->data += 1;
}

int Board::win()
{
    for (int i = 0; i < 8; ++i)
        if(abs(_boardTracker[i])==3){
            return 2; //someone won
        } 

    for (int i = 0; i < 9; ++i)
        if(_board[i]==0){
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
    for (int i = 0; i < 9; ++i) _board[i]=0;
    for (int i = 0; i < 8; ++i) _boardTracker[i]=0;
    for (int i = 0; i < 8; ++i) _zeroTracker[i]=3;
    resetHistory();
}

void Board::resetHistory()
{
    cout << "hereh";
    if(_currGameHistory->tail==_currGameHistory->head){ return; }

    cout << "out";
    _currGameHistory->tail = _currGameHistory->head;
    _currGameHistory->data = 1;

    node* temp = _currGameHistory->head;
    node* startBoard = temp;

    while(temp){
        startBoard = temp->next;
        delete temp;
        temp = startBoard;
    }
}

char Board::drawSymbol(int val)
{
    switch(_board[val]){
        case -1 : return 'x';
        case 1: return 'o';
        default: return '0'+val;
    }
}

int* Board::copyArray(int array[], int length){
    int* temp = new int[length];
    for(int i=0; i < length; i++) temp[i]=array[i];
    return temp;
}

//test Function
void Board::testDraw()
{
    for (int i = 0; i < 8; ++i) cout << _boardTracker[i] << endl;
    for (int i = 0; i < 8; ++i) cout << _zeroTracker[i] << endl;
}



