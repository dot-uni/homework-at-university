#include <iostream>
#include "tree.h"


int main() {
    int vals[] = {10, 5, 20, 15};
    trs::BinarySearchTree<int> tree(vals);
    tree.print();
    tree.change_root(20);
    tree.print();
}