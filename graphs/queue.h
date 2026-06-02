#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

class Queue
{   
    List container_;
    public:
        Queue() {}
        int front() const;
        int back() const;
        void push(int value);
        int pop();
        bool is_empty() const;
        size_t size() const;
};

#endif 