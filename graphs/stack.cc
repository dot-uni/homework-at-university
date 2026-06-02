#include "stack.h"

int Stack::top() const {
    if (container_.is_empty()) throw std::runtime_error("Стэк пуст");
    return container_.front();
}

void Stack::push(int value) {
    container_.push_front(value);
}

int Stack::pop() {
    if (container_.is_empty()) throw std::runtime_error("Стэк пуст");
    return container_.pop_front();
}

bool Stack::is_empty() const {
    if (container_.is_empty()) return true;
    return false;
}