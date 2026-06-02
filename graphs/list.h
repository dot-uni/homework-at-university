#ifndef LIST_H
#define LIST_H

#include <string>

struct Node 
{
    int value_;
    Node* prev_;
    Node* next_;
};

class List 
{   
    size_t size_;
    Node* left_;
    Node* right_;
    public:
        List() : size_(0), left_(nullptr), right_(nullptr) {}
        ~List() { delete_list(); } 
    public:
        int front() const;
        int back() const;
        size_t size() const { return size_; }
        bool is_empty() const;
        void push_front(int value);
        void push_back(int value);
        int pop_front();
        int pop_back();
    private:
        void delete_list();
};

#endif