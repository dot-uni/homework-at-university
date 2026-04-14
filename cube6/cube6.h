#ifndef CUBE6_H
#define CUBE6_H

struct Move 
{
    char direction;
    int steps;
};

class Cube6
{
    int top_, forward_, right_;
    public:
        Cube6();
        Cube6(int x1, int x2, int x3);
    public:
        void print() const;
        void mvleft(int steps);
        void mvright(int steps);
        void mvforward(int steps);
        void mvbackward(int steps);
        void move_direction(Move* moves, int size);
};

#endif 