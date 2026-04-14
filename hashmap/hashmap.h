// 0 - c-1
// список конкретного размера
// h и c - не изменяются, вводятся
// строки из 4 символов, строчные латинские буквы
// add, contains, remove 
// в файл принтится только массив от 0 - (с-1) и количесво элементов в каждой ячейке
// добавлено 10000 уникальных строк из 4 строчных символов
// и закинули в excel для создания графиков всех четырех хэшмапов
// contains возвращает есть ли объект в hashmap или нет

/*

Саморасширяющиеся хэшмапы

*/

#ifndef HASHMAP_H
#define HASHMAP_H

#include "list.h"

class Hashmap 
{
    List** array_;
    int h_, c_;
    size_t size_;
    float load_factor_;

    public:
        Hashmap(int h, int c) : h_(h), c_(c), size_(0), load_factor_(0) {
            array_ = new List*[c_];
            for (int i = 0; i < c_; ++i) {
                array_[i] = new List{};
            }
        }
        Hashmap(int h, int c, int load_factor) : Hashmap(h, c) { 
            if (load_factor <= 0) {
                throw std::runtime_error("Значение load_factor должно быть положительно.\n");
            }
            load_factor_ = load_factor; 
        }
        ~Hashmap();
    public:
        void add(const std::string& data);
        void remove(const std::string& data);
        bool contains(const std::string& data) const;
        void print(const std::string& file_name) const;
    private:
        void extension();
        int hash(const std::string& data) const; 
        inline bool load_check() const;
};

#endif