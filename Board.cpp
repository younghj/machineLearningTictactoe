#include "Board.h"
#include <iostream>
#include <cstdlib>

int board[9];
int boardTracker[8];

char drawSymbol(int val);

Board::Board()
{
    resetBoard();
    draw();
}

bool Board::setPosition(int position, bool firstPlayerTurn)
{
    if(board[position]){
        return 0;
    }
    else{
        int addVal = firstPlayerTurn ? -1 : 1;

        board[position] = addVal;
        boardTracker[position/3] += addVal;
        boardTracker[(position%3)+3] += addVal;

        if(position/4.0 == position/4)
            boardTracker[6] += addVal;
        if(position==2 || position==4 || position==6)
            boardTracker[7] += addVal;
    }
    return 1;
}

int Board::win(){
    for (int i = 0; i < 8; ++i)
        if(std::abs(boardTracker[i])==3) return 2;//win

    for (int i = 0; i < 9; ++i)
        if(board[i]==0) return 0;//no one has won yet

    return 1;//tie
}


void Board::draw()
{
    system("clear");
    std::cout << std::endl;
    for (int i = 0; i < 9; ++i)
    {
        std::cout << drawSymbol(i);
        if((i+1)%3){
            std::cout << "|";
        }
        else{
            std::cout << std::endl;
            std::cout << ((i!=8)?"-----":"");
            std::cout << std::endl;
        }
    }
}

void Board::resetBoard()
{
    for (int i = 0; i < 9; ++i)
        board[i]=0;
    for (int i = 0; i < 8; ++i)
        boardTracker[i]=0;
}

char drawSymbol(int val)
{
    switch(board[val]){
        case -1 : return 'x';
        case 1: return 'o';
        default: return '0'+val;
    }
}

//test Function
void Board::testDraw(){
    for (int i = 0; i < 8; ++i)
        std::cout << boardTracker[i] << std::endl;
}
