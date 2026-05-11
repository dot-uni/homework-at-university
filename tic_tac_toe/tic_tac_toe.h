#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

class TicTacToe final
{   
    int size_;
    int** cells_;
    TicTacToe(int size);
    TicTacToe();
    ~TicTacToe();
};

#endif 