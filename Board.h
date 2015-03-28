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
        int board[9];
        int boardTracker[8];
        int zeroTracker[8];
        int scoreKeeper[4];
        root *currGameHistory;

        char drawSymbol(int val);
        void resetHistory();
};
#endif
