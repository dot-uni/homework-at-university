#include <string>
#include "tic_tac_toe.h"

TicTacToe::TicTacToe() : TicTacToe(3) {
    
}

TicTacToe::TicTacToe(int size) {
    if (size > 1) size_ = size;
    else throw std::runtime_error("Значение размера поля должно быть больше 1.\n");

    cells_ = new int*[size_];
    for (int i = 0; i < size_; ++i) {
        cells_[i] = new int[size_];
    }
}

TicTacToe::~TicTacToe() {
    for (int i = 0; i < size_; ++i) {
        delete[] cells_[i];
    }
    delete[] cells_;
}