#ifndef BOARD_H
#define BOARD_H
class Board
{
    public:
        Board();
        void draw();
        void resetBoard();
        bool setPosition(int position, bool firstPlayerTurn);
        int win();
        void testDraw();

    private:
        /* data */
};
#endif
