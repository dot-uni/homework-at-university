#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "node.h"
#include "stack.h"

namespace trs
{

enum Mark {
    Root,
    Left,
    Right
};

template <typename T> class BinarySearchTree final
{
    Node<T>* root_;
    public:
        BinarySearchTree() : root_(nullptr) {}
        BinarySearchTree(const T& val) : root_(new Node<T>{val}) {}
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
        void left_rotation(std::pair<Node<T>*, Mark>& tnode, std::pair<Node<T>*, Mark>& parent, Node<T>* parent_above);
        void right_rotation(std::pair<Node<T>*, Mark>& tnode, std::pair<Node<T>*, Mark>& parent, Node<T>* parent_above);
        void change_root(Stack<std::pair<Node<T>*, Mark>>& path, const T& val);
        Node<T>* find_node(Node<T>* root, const T& val);
        void delete_found_node(Node<T>* node, Node<T>* parent);
        void print_base(Node<T>* parent) const;
        void ligation_nodes(Node<T>* parent, Node<T>* child, void(*set_child)(Node<T>*));
        void delete_tree();
};


template <typename T> 
template <size_t N>
BinarySearchTree<T>::BinarySearchTree(const T (&vals)[N]) : root_(nullptr) {
    for (size_t i = 0; i < N; ++i) {
        add(vals[i]);
    }
}

template <typename T> 
void BinarySearchTree<T>::add(const T& val) {
    if (root_ == nullptr) {
        root_ = new Node<T>{val};
        return;
    }
    Node<T>* parent = root_;
    Node<T>* tmp = nullptr;
    while(parent != nullptr) {
        if (val == parent->get_val()) {
            parent->increace_count();
            break;
        }
        else if (val > parent->get_val()) {
            tmp = parent->get_right();
            if (tmp == nullptr) {
                Node<T>* new_node = new Node<T>{val};
                parent->set_right(new_node);
                break;
            }
        }
        else {
            tmp = parent->get_left();
            if (tmp == nullptr) {
                Node<T>* new_node = new Node<T>{val};
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
    while(parent != nullptr) {
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
        Node<T>* tmp = nullptr;
        if (left_child != nullptr) tmp = left_child;
        else if (right_child != nullptr) tmp = right_child;

        if (parent != nullptr) {
            Node<T>* right_parent_child = parent->get_right();
            if (right_parent_child != nullptr && val == right_parent_child->get_val()) parent->set_right(tmp);
            else parent->set_left(tmp);
        }
        else {
            root_ = tmp;
        }
        delete node;
    }
    else {
        Node<T>* parent_node = node;
        Node<T>* tmp = right_child;
        while (tmp->get_left() != nullptr) {
            parent_node = tmp;
            tmp = tmp->get_left();
        }
        node->set_val(tmp->get_val());
        tmp->set_val(val);
        delete_found_node(tmp, parent_node);
    }
}

template <typename T> 
void BinarySearchTree<T>::left_rotation(std::pair<Node<T>*, Mark>& tnode, std::pair<Node<T>*, Mark>& parent, Node<T>* parent_above) {
    Node<T>* left_node = tnode.first->get_left();
    tnode.first->set_left(parent.first);
    parent.first->set_right(left_node);
    tnode.second = parent.second;
    switch(parent.second) {
        case Left:
            parent_above->set_left(tnode.first); break;
        case Right:
            parent_above->set_right(tnode.first); break;
        case Root:
            root_ = tnode.first;
    }  
}

template <typename T> 
void BinarySearchTree<T>::right_rotation(std::pair<Node<T>*, Mark>& tnode, std::pair<Node<T>*, Mark>& parent, Node<T>* parent_above) {
    Node<T>* right_node = tnode.first->get_right();
    tnode.first->set_right(parent.first);
    parent.first->set_left(right_node);
    tnode.second = parent.second;
    switch(parent.second) {
        case Left:
            parent_above->set_left(tnode.first); break;
        case Right:
            parent_above->set_right(tnode.first); break;
        case Root:
            root_ = tnode.first;
    }  
}

template <typename T> 
void BinarySearchTree<T>::change_root(const T& val) {
    if (root_ == nullptr) throw std::runtime_error("Дерево пустое");
    Node<T>* node = root_;
    Node<T>* tmp = nullptr;
    Stack<std::pair<Node<T>*, Mark>> path{{root_, Root}}; 
    while(true) {
        Mark side;
        T val_node = node->get_val();
        if (val == val_node) {
            change_root(path, val);
            return;
        } 
        else if (val > val_node) {
            tmp = node->get_right();
            side = Right;
        } 
        else {
            tmp = node->get_left();
            side = Left;
        }
        if (tmp == nullptr) break;
        node = tmp;
        path.push({node, side});
    }
    throw std::runtime_error("Такого элемента не существует");
}

template <typename T> 
void BinarySearchTree<T>::change_root(Stack<std::pair<Node<T>*, Mark>>& path, const T& val) {
    auto tnode = path.pop();
    std::cout << "OLD ROOT = " << root_->get_val() << "\n";
    while (!path.empty()) {
        Node<T>* parent_above = nullptr;
        auto parent = path.pop();
        if (path.size() != 0) parent_above = path.top().first;
        switch(tnode.second) {
            case Left: 
                right_rotation(tnode, parent, parent_above); break;
            case Right:
                left_rotation(tnode, parent, parent_above); break;
            default:
                break;
        }
    }
    std::cout << "NEW ROOT = " << root_->get_val() << "\n";
}

template <typename T> 
bool BinarySearchTree<T>::contains(const T& val) {
    Node<T>* parent = root_;
    while(parent != nullptr) {
        if (val == parent->get_val()) return true;
        else if (val > parent->get_val()) parent = parent->get_right();
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
Node<T>* BinarySearchTree<T>::find_node(Node<T>* root, const T& val) {
    Node<T>* tmp = root;
    while (tmp != nullptr) {
        if (val == tmp->get_val()) return tmp;
        else if (val > tmp->get_val()) {
            tmp = tmp->get_right();
        }
        else {
            tmp = tmp->get_left();
        }
    }
    return nullptr;
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