#ifndef NODE_H
#define NODE_H

#include <string>

class Node 
{
    std::string data_;
    Node* next_;
    public:
        Node() : next_(nullptr) {} 
        Node(const std::string& data) : data_(data), next_(nullptr) {} 
        Node(const std::string& data, Node* next) : data_(data), next_(next) {} 
    public:
        std::string get_data() const { return data_; }
        Node* get_next() const { return next_; }
        void set_data(const std::string& data) { data_ = data; }
        void set_next(Node* next) { next_ = next; }
};

#endif