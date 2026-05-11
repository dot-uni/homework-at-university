#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "node.h"
#include "stack.h"

namespace tree 
{

template <typename T> class BinarySearchTree 
{
    Node<T>* root_;
    size_t deep_ = 0;

    public:
        BinarySearchTree() : root_(nullptr) {}
        BinarySearchTree(const T& val) : root_(new Node<T>{val}), deep_(1) {}
        template <size_t N> BinarySearchTree(const T (&vals)[N]);
        ~BinarySearchTree() { delete_tree(); }
    public:
        void add(const T& val);
        template <size_t N> void add(const T (&val)[N]);
        void remove(const T& val);
        void change_root(const T& val);
        bool contains(const T& val);
        void print() const;
    private:
        void delete_found_node(Node<T>* node, Node<T>* parent);
        void print_base(Node<T>* parent) const;
        void ligation_nodes(Node<T>* parent, Node<T>* child, void(*set_child)(Node<T>*));
        void delete_tree();
};


template <typename T> 
template <size_t N>
BinarySearchTree<T>::BinarySearchTree(const T (&vals)[N]) {
    if (N == 0) {
        root_ = nullptr;
        deep_ = 0;
    }
    else {
        root_ = new Node<T>{vals[0]};
        Node<T>* tmp_parent = root_;
        for (size_t i = 1; i < N; ++i) {
            T val_parent = tmp_parent->get_val();
            if (vals[i] == val_parent) {
                tmp_parent->increace_count();
                continue;
            }
            Node<T>* tmp_child = new Node<T>{vals[i]};
            if (vals[i] > val_parent) tmp_parent->set_right(tmp_child);
            else tmp_parent->set_left(tmp_child);
            ++deep_;

            tmp_parent = tmp_child;
        }
    }
}

template <typename T> 
void BinarySearchTree<T>::add(const T& val) {
    Node<T>* new_node = new Node<T>{val};
    if (root_ == nullptr) {
        root_ = new_node;
        deep_ = 0;
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
                parent->set_right(new_node);
                break;
            }
        }
        else {
            tmp = parent->get_left();
            if (tmp == nullptr) {
                parent->set_left(new_node);
                break;
            }
        }
        parent = tmp;
    }
}

template <typename T> 
template <size_t N> 
void BinarySearchTree<T>::add(const T (&val)[N]) {
    if (N == 0) throw std::runtime_error("Массив данных пуст\n");
    for (size_t i = 0; i < N; ++i) {
        add(val[i]);
    }
}

template <typename T> 
void BinarySearchTree<T>::remove(const T& val) {
    if (root_ == nullptr) throw std::runtime_error("Tree is empty\n");
    Node<T>* parent = root_;
    if (val == parent->get_val()) {
        delete_found_node(parent, nullptr);
        return;
    }
    while(true) {
        Node<T>* left_child = parent->get_left();
        if (left_child != nullptr && val == left_child->get_val()) {
            delete_found_node(left_child, parent);
            break;
        }
        Node<T>* right_child = parent->get_right();
        if (right_child != nullptr && val == right_child->get_val()) {
            delete_found_node(right_child, parent);
            break;
        }

        if (val > parent->get_val()) parent = right_child;
        else parent = left_child;

        if (parent == nullptr) throw std::runtime_error("There is no such value\n");
    }
}

template <typename T> 
void BinarySearchTree<T>::delete_found_node(Node<T>* node, Node<T>* parent) {
    Node<T>* left_child = node->get_left();
    Node<T>* right_child = node->get_right();
    T val = node->get_val();
    if (left_child == nullptr || right_child == nullptr) {
        delete node;
        Node<T>* tmp = nullptr;

        if (left_child != nullptr) tmp = left_child;
        else if (right_child != nullptr) tmp = right_child;

        if (parent != nullptr) {
            if (val > parent->get_val()) parent->set_right(tmp);
            else parent->set_left(tmp);
        }
    }
    else {
        Node<T>* parent = node;
        Node<T>* tmp = node->get_right();
        while (tmp != nullptr && tmp->get_left() != nullptr) {
            parent = tmp;
            tmp = tmp->get_left();
        }
        T node_val = node->get_val();
        node->set_val(tmp->get_val());
        tmp->set_val(node_val);
        delete_found_node(tmp, parent);
    }
}

template <typename T> 
void BinarySearchTree<T>::change_root(const T& val) {
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
bool BinarySearchTree<T>::contains(const T& val) {
    Node<T>* parent = root_;
    while(true) {
        if (val == parent->get_val()) return true;
        if (val > parent->get_val()) parent = parent->get_right();
        else parent = parent->get_left();
    }
    return false;
}

template <typename T> 
void BinarySearchTree<T>::print() const {
    if (root_ == nullptr) throw std::runtime_error("Дереро пустое\n");
    print_base(root_);
    std::cout << "\n";
}

template <typename T> 
void BinarySearchTree<T>::print_base(Node<T>* parent) const{
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
void BinarySearchTree<T>::delete_tree() {
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
        if (right_child == nullptr) {
            delete node;
            node = nullptr;
        }
        node = right_child;
    }
}

} // namespace tree

#endif 