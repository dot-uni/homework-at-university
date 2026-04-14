#include "list.h"

void List::delete_list() {
    while (head_ != nullptr) {
        Node* tmp = head_->get_next();
        delete head_;
        head_ = tmp;
    }   
    count_ = 0;
}

void List::add(const std::string& data) {
    Node* new_node = new Node{data, head_};
    head_ = new_node;
    count_ += 1;
}

void List::remove(const std::string& data) {
    if (head_->get_data() == data) {
        Node* tmp = head_->get_next();
        delete head_;
        head_ = tmp;
        count_ -= 1; 
        return;
    }
    else {
        Node* prev = head_;
        Node* next = head_->get_next();
        while (next != nullptr) {
            if (next->get_data() == data) {
                Node* tmp = next->get_next();
                delete next;
                prev->set_next(tmp);
                count_ -= 1; 
                return;
            }
            prev = next;
            next = next->get_next();
        }
    }
    throw std::runtime_error("Такого элемента в списке нет\n");
}

bool List::contains(const std::string& data) const{
    for (Node* tmp = head_; tmp != nullptr; tmp=tmp->get_next()) {
        if (tmp->get_data() == data) return true;
    }
    return false;
}