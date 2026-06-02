#include "queue.h"

int Queue::front() const {
    if (container_.is_empty()) throw std::runtime_error("Очередь пуста");
    return container_.front();
}

int Queue::back() const {
    if (container_.is_empty()) throw std::runtime_error("Очередь пуста");
    return container_.back();
}

void Queue::push(int value) {
    container_.push_back(value);
}

int Queue::pop() {
    if (container_.is_empty()) throw std::runtime_error("Очередь пуста");
    return container_.pop_front();
}

bool Queue::is_empty() const {
    if (container_.is_empty()) return true;
    return false;
}

size_t Queue::size() const {
    return container_.size();
}