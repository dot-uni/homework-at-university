/*

Перекаты через развертку 
move(left, right)
в конструкторе создаем развертку куба (рандом и по 3 числам(тк 3 оставшихся определяются однозначно))

*/
#include <random>
#include <iostream>
#include "cube6.h"


Cube6::Cube6() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    top_ = (std::rand() % 3) + 1;
    do {
        forward_ = (std::rand() % 3) + 1;
    } while(forward_ == top_);
    right_ = 6 - top_ - forward_;
}

Cube6::Cube6(int x1, int x2, int x3) {
    auto foo = [](int x) { return (x >= 1 && x <= 6); };
    if (foo(x1) && foo(x2) && foo(x3)) {
        top_ = x1; forward_ = x2; right_ = x3;
    }
    else {
        throw std::runtime_error("Числа не подходят для шестигранного куба.");
    }
}

void Cube6::print() const {
    std::cout << "      B" << 7 - forward_ << "\n";
    std::cout << "      T" << top_ << "\n";
    std::cout << "L" << 7 - right_ << "    F" << forward_ << "     R" << right_ << "\n";
    std::cout << "      D" << 7 - top_ << "\n\n";
}

void Cube6::mvleft(int steps) {
    for (int i = 0; i < steps; ++i) {
        int tmp_right = right_;
        right_ = 7 - top_;
        top_ = tmp_right;
    }
}

void Cube6::mvright(int steps) {
    for (int i = 0; i < steps; ++i) {
        int tmp_top = top_;
        top_ = 7 - right_;
        right_ = tmp_top;
    }
}

void Cube6::mvforward(int steps) {
    for (int i = 0; i < steps; ++i) {
        int tmp_forward = forward_;
        forward_ = 7 - top_;
        top_ = tmp_forward;
    }
}

void Cube6::mvbackward(int steps) {
    for (int i = 0; i < steps; ++i) {
        int tmp_top = top_;
        top_ = 7 - forward_;
        forward_ = tmp_top;
    }
}

void Cube6::move_direction(Move* moves, int size) {
    for (int move = 0; move < size; ++move) {
        int steps = moves[move].steps;
        switch (moves[move].direction) {
            case 'F': mvforward(steps); break;
            case 'B': mvbackward(steps); break;
            case 'R': mvright(steps); break;
            case 'L': mvleft(steps); break;
            default:
                throw std::runtime_error(std::string("Такого движения нету '") + moves[move].direction + "'");
       }
    }
}