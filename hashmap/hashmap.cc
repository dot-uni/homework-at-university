#include <fstream>
#include <iostream>
#include <cmath>
#include "hashmap.h"


Hashmap::~Hashmap() {
    for (int i = 0; i < c_; ++i) {
        delete array_[i];
    }
    delete [] array_;
}

void Hashmap::extension() {
    int new_c = c_ * 2;
    List** new_array = new List*[new_c];
    for (int i = 0; i < c_; ++i) {
        new_array[i] = array_[i];
    }
    for (int i = c_; i < new_c; ++i) {
        new_array[i] = new List{};
    }
    c_ = new_c;
    array_ = new_array;
}

int Hashmap::hash(const std::string& data) const{
    int res = 0;
    auto foo = [this](char symb, int i) { return (int)symb * pow(h_, i); };
    for (int i = 0; i < 4; ++i) {
        res += foo(data[i], i);
    }
    return res % c_;
}

void Hashmap::add(const std::string& data) {
    int idx = hash(data);
    if (!array_[idx]->contains(data)) {
        array_[idx]->add(data);
        size_++;
        if (load_factor_ != 0 && load_check()) extension(); 
    }
}

void Hashmap::remove(const std::string& data) {
    int idx = hash(data);
    if (array_[idx]->contains(data)) { 
        array_[idx]->remove(data);
        size_--;
    }
    else throw std::runtime_error(std::string("Такого элемента в списке нет '") + data + "'\n");
}

bool Hashmap::contains(const std::string& data) const {
    int idx = hash(data);
    return array_[idx]->contains(data);
}

void Hashmap::print(const std::string& file_name) const {   
    std::ofstream file(file_name+".txt", std::ios::out);
    for (int i = 0; i < c_; ++i) {
        file << i << ";" << array_[i]->get_count() << "\n";
    }
}

inline bool Hashmap::load_check() const {
    return (c_ * load_factor_) < size_;
}