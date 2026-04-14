#ifndef NODE_H
#define NODE_H

template <typename T> class Node 
{
    T data_;
    Node<T>* next_;
    public:
        Node(T data, Node<T>* next) : data_(data), next_(next) {} 
        T get_data() const { return data_; }
        Node<T>* get_next() const { return next_; }
};

#endif