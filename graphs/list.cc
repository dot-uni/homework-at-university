#include "list.h"

void List::delete_list() {
    Node* tmp;
    while (left_ != nullptr) {
        tmp = left_->next_;
        delete left_;
        left_ = tmp;
    }
}

int List::front() const {
    if (left_ == nullptr) throw std::runtime_error("Список пуст");
    return left_->value_;
}

int List::back() const {
    if (right_ == nullptr) throw std::runtime_error("Список пуст");
    return right_->value_;
}

bool List::is_empty() const {
    if (size_ == 0) return true;
    return false;
}

void List::push_front(int value) {
    ++size_;
    Node* newnode = new Node{value, nullptr, nullptr};
    newnode->next_ = left_;
    if (left_ == nullptr) right_ = newnode;
    else {
        left_->prev_ = newnode;
    }
    left_ = newnode;    
}

void List::push_back(int value) {
    ++size_;
    Node* newnode = new Node{value, nullptr, nullptr};
    newnode->prev_ = right_;
    if (right_ == nullptr) left_ = newnode;
    else {
        right_->next_ = newnode;
    }
    right_ = newnode;
}

int List::pop_front() {
    if (left_ == nullptr) throw std::runtime_error("Список пуст");
    int value = left_->value_;
    Node* newleft = left_->next_;
    if (newleft != nullptr) newleft->prev_ = nullptr;
    delete left_;
    left_ = newleft;

    --size_;
    if (size_ == 0) right_ = nullptr;
    return value;
}

int List::pop_back() {
    if (right_ == nullptr) throw std::runtime_error("Список пуст");
    int value = right_->value_;
    Node* newright = right_->prev_;
    if (newright != nullptr) newright->prev_ = nullptr;
    delete right_;
    right_ = newright;

    --size_;
    if (size_ == 0) left_ = nullptr;
    return value;
}