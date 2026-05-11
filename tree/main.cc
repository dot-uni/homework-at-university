#include <iostream>
#include "tree.h"

int main() {
    tree::BinarySearchTree<int> tree;
    tree.add({56,34, 12, 24, 1287, 214, 1248});
    tree.print();
    tree.remove(1);
    tree.print();
    return 0;
}