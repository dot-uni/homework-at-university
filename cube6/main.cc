#include <iostream>
#include "cube6.h"


int main() {
    int n, cnt = 0;
    Cube6 cube;
    cube.print();
    
    std::cout << "Введите количество шагов: ";
    std::cin >> n;
    Move* moves = new Move[n];

    char direction;
    int steps;
    while (cnt != n) {
        std::cin >> direction >> steps;
        switch(direction) {
            case 'F': cube.mvforward(steps); break;
            case 'B': cube.mvbackward(steps); break;
            case 'R': cube.mvright(steps); break;
            case 'L': cube.mvleft(steps); break;
            default:
                throw std::runtime_error(std::string("Такого движения нету '") + direction + "'");
        }
        std::cout << "\n";
        cube.print();
        std::cout << "\n";
        cnt++;
    }
    // cube.move_direction(moves, n);
    // cube.print();
    delete[] moves;
    return 0;
}