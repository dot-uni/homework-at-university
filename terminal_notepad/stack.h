#ifndef STACK_H
#define STACK_H

#include <string>
#include "node_stack.h"

template <typename T> class Stack 
{
    Node<T>* head_;
    size_t size_;
    public:
        Stack() : head_(nullptr), size_(0) {}
        Stack(const T& data) : head_(new Node<T>{data, nullptr}), size_(1) {}
        Stack(const T* data, size_t n) {
            if (n <= 0) throw std::runtime_error("Размер стека должен быть натуральным числом.");
            size_ = n;
            head_ = new Node<T>{data[0], nullptr};
            for (size_t i = 1; i < n; ++i) {
                Node<T>* tmp = new Node<T>(data[i], head_);
                head_ = tmp;
            } 
        }
        Stack(const Stack<T>& tmp);
        Stack(Stack&& tmp) noexcept;
        Stack<T>& operator=(const Stack<T>& tmp);
        Stack<T>& operator=(Stack&& tmp) noexcept; 
        ~Stack() { delete_stack(); }
    public:
        size_t size() const;
        void push(const T& obj);
        void push_range(const T* container, size_t size);
        T pop();
        T& top();
        const T& top() const;
        void clear();
        bool empty() const;
    private:
        void delete_stack();
        void copy_stack(const Stack<T>& tmp);
};

template <typename T>
Stack<T>::Stack(const Stack& tmp) {
    copy_stack(tmp);
}

template <typename T> 
Stack<T>::Stack(Stack<T>&& tmp) noexcept : head_(tmp.head_), size_(tmp.size_) {
    tmp.head_ = nullptr;
    tmp.size_ = 0;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& tmp) {
    if (*this == tmp) return *this;
    delete_stack();
    copy_stack(tmp);
    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& tmp) noexcept {
    if (*this == tmp) return *this;
    delete_stack();
    head_ = tmp.head_;
    size_ = tmp.size_;
    tmp.head_ = nullptr;
    tmp.size_ = 0;
    return *this;
}

template <typename T> 
size_t Stack<T>::size() const { return size_; }

template <typename T> 
void Stack<T>::push(const T& obj) {
    Node<T>* new_node = new Node<T>{obj, head_};
    head_ = new_node;
    size_++;
}

template <typename T>
void Stack<T>::push_range(const T* container, size_t size) {
    if (size <= 0) throw std::runtime_error("Значение переменной size должно быть натуральным числом.");
    for (size_t i = 0; i < size; ++i) {
        push(container[i]);
    }
}

template <typename T> 
T Stack<T>::pop() {
    if (empty()) throw std::runtime_error("Стек пустой\n");
    size_--;
    T data = head_->get_data();
    Node<T>* new_head = head_->get_next();
    delete head_;
    head_ = new_head;
    return data; 
} 

template <typename T> 
T& Stack<T>::top() {
    return head_->data_();
}

template <typename T> 
const T& Stack<T>::top() const {
    return head_->data_();
}

template <typename T> 
void Stack<T>::clear() {
    delete_stack();
    head_=nullptr;
    size_ = 0;
}

template <typename T> 
bool Stack<T>::empty() const { return (size_ == 0); }

template <typename T>
void Stack<T>::delete_stack() {
    while (head_ != nullptr) {
        Node<T>* tmp = head_;
        head_ = head_->get_next();
        delete tmp;
    } 
}

template <typename T>
void Stack<T>::copy_stack(const Stack<T>& tmp) {
    int n = tmp.size_;
    T* container = new T[n];
    Node<T>* p = tmp;
    for (size_t i = n-1; i >= 0; --i) {
        container[i] = p->get_data();
        p = p->get_next();
    }
    push_range(container, n);
    delete[] container;
}

#endif