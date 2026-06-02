#include <iostream>
#include "hashmap.h"

std::string generate_word() {
    std::string word;
    for (int i = 0; i < 4; ++i) {
        char c = 'a' + rand() % 26;
        word += c;
    }
    return word;
}

bool search(const std::string& str, std::string* strs, int size) {
    for (int i = 0; i < size; ++i) {
        if (strs[i] == str) return true;
    }
    return false;
}

int main() {
    int n = 10000;
    std::string* strs = new std::string[n];
    int idx = 0;
    while (idx != n) {
        std::string str = generate_word();
        if (!search(str, strs, idx)) {
            strs[idx] = str;
            idx++;
        }
    }

    float load_factor = 0.75;
    Hashmap hashmap1{2, 100, load_factor};   
    // Hashmap hashmap2{7, 103};   
    // Hashmap hashmap3{11, 121};   
    // Hashmap hashmap4{2, 100};   

    for (int i = 0; i < n; ++i) {
        hashmap1.add(strs[i]);
        // hashmap2.add(strs[i]);
        // hashmap3.add(strs[i]);
        // hashmap4.add(strs[i]);
    }

    hashmap1.print("hashmap1");
    // hashmap2.print("hashmap2");
    // hashmap3.print("hashmap3");
    // hashmap4.print("hashmap4");
    delete[] strs;
    return 0;
}
