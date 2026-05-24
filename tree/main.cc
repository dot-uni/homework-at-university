#include <iostream>
#include "tree.h"


int main() {
    int vals[] = {10, 5, 20, 15, 25, 13, 17};
    trs::BinarySearchTree<int> tree(vals);
    tree.print();
    tree.change_root(15);
    tree.print();
}