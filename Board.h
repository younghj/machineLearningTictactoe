#ifndef BOARD_H
#define BOARD_H

#include "Global.h"

class Board
{
    public:
        Board();
        void draw();
        void resetBoard();
        void setPosition(int position, bool firstPlayerTurn);
        int win();
        void testDraw();
        bool positionCheck(int position);

    private:
        /* data */
        int _board[9];
        int _boardTracker[8];
        int _zeroTracker[8];
        int _scoreKeeper[4];
        root *_currGameHistory;

        char drawSymbol(int val);
        void resetHistory();
        int* copyArray(int array[],int length);
};
#endif
