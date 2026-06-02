#ifndef STACK_H
#define STACK_H

#include "list.h"

class Stack 
{
    List container_;
    public:
        Stack() {}
        int top() const;
        void push(int value);
        int pop();
        bool is_empty() const;
        size_t size() const { return container_.size(); }
};

#endif 