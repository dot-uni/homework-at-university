#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "node.h"

template <typename T> class Queue final 
{   
    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;

    public:
        Queue() : head_(nullptr), tail_(nullptr), size_(0) {}
        Queue(const T& val) : size_(1) {
            head_ = new Node<T>{val};
            tail_ = head_;
        }
        Queue(const T& val_1, const T& val_2) : size_(2) {
            head_ = new Node<T>{val_1};
            tail_ = new Node<T>{val_2};
        }
        ~Queue() { delete_queue(); }
    public: 
        T front() const;
        T back() const;
        void push(T val);
        T pop();
        bool empty() const;
        void print() const {
            for (Node<T>* tmp = head_; tmp != nullptr; tmp=tmp->get_next()) {
                std::cout << tmp->get_data() << " ";
            }
            std::cout << "\n";
        }
    private:
        void delete_queue();
};

template <typename T>
T Queue<T>::front() const {
    if (head_ == nullptr) throw std::runtime_error("Очередь пустая");
    return head_->get_data();
}

template <typename T>
T Queue<T>::back() const {
    if (tail_ == nullptr) throw std::runtime_error("Очередь пустая");
    return tail_->get_data();
}

template <typename T>
void Queue<T>::push(T val) {
    Node<T>* new_node = new Node<T>{val};
    if (size_ == 0) {
        tail_ = new_node;
        head_ = tail_;
    }
    else {
        tail_->set_next(new_node);
        tail_ = new_node;
    }
    ++size_;
}

template <typename T>
T Queue<T>::pop() {
    if (head_ == nullptr) throw std::runtime_error("Очередь пустая");
    Node<T>* old_head = head_;
    Node<T>* new_head = head_->get_next();
    head_ = new_head;
    if (size_ == 1) {
        tail_ = head_;
    }
    --size_;
    return old_head->get_data();
}

template <typename T>
bool Queue<T>::empty() const {
    if (size_ == 0) return true;
    return false;
}

template <typename T>
void Queue<T>::delete_queue() {
    Node<T>* node = head_;
    while (node != nullptr) {
        Node<T>* tmp = node->get_next();
        delete node;
        node = tmp;
    }
}

#endif