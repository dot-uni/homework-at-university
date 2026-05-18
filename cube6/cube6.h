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
        Cube6(int top, int forw, int right);
    public:
        void print() const;
        void mvleft(int steps);
        void mvright(int steps);
        void mvforward(int steps);
        void mvbackward(int steps);
        void move_direction(const Move* const moves, int size);
};

#endif 