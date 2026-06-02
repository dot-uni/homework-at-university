#include <iostream>
#include "tree.h"


int main() {
    trs::BinarySearchTree<int> tree;

    int x;
    while (std::cin >> x && x != 0) {
        tree.add(x);
        std::cout << "Дерево: ";
        tree.print();
    }

    int new_root;
    const trs::Node<int>* root = tree.root();
    std::cout << "Корнем дерева является: " << root->get_val() << "\n";
    std::cout << "Новый корень: ";
    std::cin >> new_root;
    tree.change_root(new_root);
    tree.print();

    return 0;
}