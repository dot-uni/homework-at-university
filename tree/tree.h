#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "node.h"
#include "stack.h"

namespace tree 
{

template <typename T> class BinaryTree 
{
    Node<T>* root_;
    size_t deep_ = 0;

    public:
        BinaryTree() : root_(nullptr) {}
        BinaryTree(const T& val) : root_(new Node<T>{val}), deep_(1) {}
        // BinaryTree(T* vals, size_t size);
        ~BinaryTree() { delete_tree(); }
    public:
        void add(const T& val);
        T remove(const T& val);
        void change_root(const T& val);
        bool contains(const T& val);
        void print() const;
    private:
        void remove_found_node(Node<T>* node, const Child& pos);
        void print_base(Node<T>* parent) const;
        void ligation_nodes(Node<T>* parent, Node<T>* child, void(*set_child)(Node<T>*));
        void set_two_childs();
        void delete_tree();
};

// template <typename T> 
// BinaryTree<T>::BinaryTree(T* vals, size_t size) : deep_(size) {
//     if (size <= 0) throw std::runtime_error("Переменная size является натуральным числом.\n");
//     root_ = new Node<T>{vals[0]};
//     Node<T>* tmp_parent = root_;
//     for (size_t i = 1; i < size; ++i) {
//         T val_parent = tmp_parent->get_val();
//         if (vals[i] == val_parent) tmp_parent->increace_count();

//         Node<T>* tmp_child = new Node<T>{vals[i]};
//         if (vals[i] > val_parent) tmp_parent->set_right(tmp_child);
//         else tmp_parent->set_left(tmp_child);
        
//         tmp_parent = tmp_child;
//     }
// }

template <typename T> 
void BinaryTree<T>::add(const T& val) {
    Node<T>* new_node = new Node<T>{val};
    if (root_ == nullptr) {
        root_ = new_node;
        return;
    }
    Node<T>* parent = root_;
    Node<T>* tmp = nullptr;
    while(true) {
        if (val == parent->get_val()) {
            parent->increace_count();
            delete new_node;
            break;
        }
        else if (val > parent->get_val()) {
            tmp = parent->get_right();
            if (tmp == nullptr) {
                new_node->set_parent(parent, Child::Right);
                parent->set_right(new_node);
                break;
            }
        }
        else {
            tmp = parent->get_left();
            if (tmp == nullptr) {
                new_node->set_parent(parent, Child::Left);
                parent->set_left(new_node);
                break;
            }
        }
        parent = tmp;
    }
}

// template <typename T> 
// T BinaryTree<T>::remove(const T& val) {
//     Node<T>* parent = root_;
//     while(true) {
//         Node<T>* left_child = parent->get_left();
//         if (left_child->get_val() == val) {
//             ligation_nodes(parent, left_child, parent->set_left());
//             break;
//         }
//         Node<T>* right_child = parent->get_right();
//         if (right_child->get_val() == val) {
//             ligation_nodes(parent, right_child, parent->set_right());
//             break;
//         }
//         if (left_child == nullptr && right_child == nullptr) {
//             throw std::runtime_error("Такого элемента в дереве нет.\n");
//         }
//         if (val > parent->get_val()) parent = parent->get_right();
//         else parent = parent->get_left();
//     }
// }

template <typename T> 
T BinaryTree<T>::remove(const T& val) {
    Node<T>* parent = root_;
    if (val == parent->get_val()) {}
    while(true) {
        Node<T>* left_child = parent->get_left();
        if (val == left_child->get_val()) {}
        Node<T>* right_child = parent->get_right();
        if (val == right_child->get_val()) {}
    }
}

template <typename T> 
void BinaryTree<T>::remove_found_node(Node<T>* node, const Child& pos) {
    Node<T>* parent = node->get_parent();
    Node<T>* left_child = node->get_left();
    Node<T>* right_child = node->get_right();
    if (left_child == nullptr && right_child == nullptr) {
        delete node;
        return;
    }
    else if (left_child == nullptr && right_child != nullptr) {
        if (pos == Child::Left) parent->set_left = right_child;
        else parent->set_right = right_child;
    }
    else if (left_child != nullptr && right_child == nullptr) {
        if (pos == Child::Left) parent->set_left = left_child;
        else parent->set_right = left_child;
    }
    else {
        Node<T>* min_child = left_child;
        while(true) {
            if (min_child->get_left() != nullptr) min_child = min_child->get_left();
            else break;
        }

        Node<T>* parent_min_child = min_child->get_parent();
        parent_min_child->set_left() = nullptr;

        if (pos == Child::Left) parent->set_left(min_child);
        else parent->set_right(min_child);

        min_child->set_right(right_child);
        if (min_child != left_child) min_child->set_left(left_child);
    }
}

template <typename T> 
void BinaryTree<T>::change_root(const T& val) {
    Node<T>* parent = root_;
    while(true) {
        Node<T>* left_child = parent->get_left();
        if (left_child->get_val() == val) {
            parent->set_left() = nullptr;
            
        }
        Node<T>* right_child = parent->get_right();
        if (right_child->get_val() == val) {

        }
        if (left_child == nullptr && right_child == nullptr) {
            throw std::runtime_error("Такого элемента в дереве нет.\n");
        }
        if (val > parent->get_val()) parent = parent->get_right();
        else parent = parent->get_left();
    }
}

template <typename T> 
bool BinaryTree<T>::contains(const T& val) {
    Node<T>* parent = root_;
    while(true) {
        if (val == parent->get_val()) return true;
        if (val > parent->get_val()) parent = parent->get_right();
        else parent = parent->get_left();
    }
    return false;
}

template <typename T> 
void BinaryTree<T>::print() const {
    if (root_ == nullptr) throw std::runtime_error("Дереро пустое\n");
    print_base(root_);
    std::cout << "\n";
}

template <typename T> 
void BinaryTree<T>::print_base(Node<T>* parent) const{
    Node<T>* left_child = parent->get_left();
    Node<T>* right_child = parent->get_right();
    if (left_child != nullptr) {
        print_base(left_child);
    }
    std::cout << parent->get_val() << " ";  
    if (right_child != nullptr) {
        print_base(right_child);
    }
}

template <typename T> 
void BinaryTree<T>::ligation_nodes(Node<T>* parent, Node<T>* found_child, void(*set_child)(Node<T>*)) {
    Node<T>* left = found_child->get_left();
    if (left == nullptr) parent->set_child(left);
    Node<T>* right = found_child->get_right();
    if (right == nullptr) parent->set_child(right);
}

template <typename T> 
void BinaryTree<T>::delete_tree() {
    Stack<Node<T>*> stack; 
    Node<T>* node = root_;
    while(node != nullptr || !stack.empty()) {
        while (node != nullptr) {
            stack.push(node);
            node = node->get_left();
        }

        node = stack.top();
        stack.pop();
        Node<T>* right_child = node->get_right();
        delete node;
        node = right_child;
    }
}

} // namespace tree

#endif 