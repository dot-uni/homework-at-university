/*

Перекаты через развертку 
move(left, right)
в конструкторе создаем развертку куба (рандом и по 3 числам(тк 3 оставшихся определяются однозначно))

*/
#include <random>
#include <iostream>
#include "cube6.h"


Cube6::Cube6() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::array<int, 6> sides {1,2,3,4,5,6};
    std::shuffle(sides.begin(), sides.end(), gen);
    top_ = sides[0];
    for (int x : sides) {
        if (x != top_ && x != 7-top_) {
            forward_ = x;
            break;
        }
    }
    for (int x : sides) {
        if (x != top_ &&
            x != 7-top_ &&
            x != forward_ &&
            x != 7-forward_) {
            right_ = x;
            break;
        }
    }
}

Cube6::Cube6(int top, int forw, int right) {
    auto foo = [](int x) { return (x >= 1 && x <= 6); };
    if (foo(top) && foo(forw) && foo(right)) {
        top_ = top; forward_ = forw; right_ = right;
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

void Cube6::move_direction(const Move* const moves, int size) {
    for (int i = 0; i < size; ++i) {
        int steps = moves[i].steps;
        switch (moves[i].direction) {
            case 'F': mvforward(steps); break;
            case 'B': mvbackward(steps); break;
            case 'R': mvright(steps); break;
            case 'L': mvleft(steps); break;
            default:
                throw std::runtime_error(std::string("Такого движения нету '") + moves[i].direction + "'");
       }
       print();
    }
}