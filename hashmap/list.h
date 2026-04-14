#ifndef LIST_H
#define LIST_H

#include "node.h"

class List 
{   
    Node* head_;
    size_t count_ = 0;
    public:
        List() : head_(nullptr) {}
        List(std::string data) : head_(new Node{data, nullptr}), count_(1) {}
        ~List() { delete_list(); }
    public:
        void add(const std::string& data);
        void remove(const std::string& data);
        bool contains(const std::string& data) const;
        size_t get_count() const { return count_; } 
    private:
        void delete_list();
};


#endif