#ifndef NODE_STACK_H
#define NODE_STACK_H

template <typename T> class Node_Stack 
{
    T data_;
    Node_Stack<T>* next_;
    public:
        Node_Stack(T data, Node_Stack<T>* next) : data_(data), next_(next) {} 
        T get_data() const { return data_; }
        Node_Stack<T>* get_next() const { return next_; }
};

#endif