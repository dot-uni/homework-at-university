#include <iostream>
#include "cube6.h"

struct Move;

int main() {
    int n, cnt = 0;
    Cube6 cube{1, 5, 2};
    cube.print();

    std::cin >> n;
    Move* moves = new Move[n];

    char direction;
    int steps;
    while (cnt != n) {
        std::cin >> direction >> steps;
        moves[cnt].direction = direction;
        moves[cnt].steps = steps;
        cnt++;
    }
    cube.move_direction(moves, n);
    cube.print();
    delete[] moves;
    return 0;
}