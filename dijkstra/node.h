#ifndef NODE_H
#define NODE_H


template <typename T> class Node 
{
    T data_;
    Node<T>* next_;
    public:
        Node(const T& data) : data_(data), next_(nullptr) {} 
        Node(const T& data, Node<T>* next) : data_(data), next_(next) {} 
    public:
        T get_data() const { return data_; }
        Node<T>* get_next() const { return next_; }
        void set_data(const T& data) { data_ = data; }
        void set_next(Node<T>* next) { next_ = next; }
};

#endif