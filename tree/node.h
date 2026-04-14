#ifndef NODE_H
#define NODE_H

/*

сгенерировать 3000 строк состоящие из 4 символов накидать в графф и его динамическое 
rebuild(val) найдет val в дереве, если не найдет то будет корнем, если будет то корень и переделать граф

*/

namespace tree 
{

enum class Child {
    Left, 
    Right
};

template <typename T> class Node 
{
    T val_;
    int count_ = 1;
    Node<T>* left_;
    Node<T>* right_;
    Node<T>* parent_;
    public:
        Node(const T& val) : val_(val), left_(nullptr), right_(nullptr), parent_(nullptr) {} 
        Node(const T& val, Node<T>* left, Node<T>* right) : val_(val), parent_(nullptr) {
            if (left == right) throw std::runtime_error("Указатели указывают на один и тот же узел.\n");
            left_ = left; right_ = right;
        } 
        ~Node() { delete_node(); }
    public:
        void increace_count();
        T get_val() const;
        Node<T>* get_left() const;
        Node<T>* get_right() const;
        Node<T>* get_parent() const;
        void set_val(T val);
        void set_left_right(Node<T>* left, Node<T>* right);
        void set_left(Node<T>* left);
        void set_right(Node<T>* right);
        void set_parent(Node<T>* parent, const Child& child_pos);
    private:
        void delete_node();
};

template <typename T> 
void Node<T>::increace_count() { ++count_; }

template <typename T> 
T Node<T>::get_val() const { return val_; }

template <typename T> 
Node<T>* Node<T>::get_left() const { return left_; }

template <typename T> 
Node<T>* Node<T>::get_right() const { return right_; }

template <typename T> 
Node<T>* Node<T>::get_parent() const { return parent_; }

template <typename T> 
void Node<T>::set_val(T val) { val_ = val; }

template <typename T> 
void Node<T>::set_left_right(Node<T>* left, Node<T>* right) {
    if (left == right) throw std::runtime_error("Указатели указывают на один и тот же узел.\n");
    left_ = left; right_ = right;
}

template <typename T> 
void Node<T>::set_left(Node<T>* left) {
    if (left == right_) throw std::runtime_error("Указатели указывают на один и тот же узел.\n");
    left_ = left;
}

template <typename T> 
void Node<T>::set_right(Node<T>* right) {
    if (left_ == right) throw std::runtime_error("Указатели указывают на один и тот же узел.\n");
    right_ = right;
}

template <typename T> 
void Node<T>::set_parent(Node<T>* parent, const Child& child_pos) {
    if (parent == nullptr) throw std::runtime_error("Значение переменной parent не должно быть равно nullptr.\n");
    T val_parent = parent->get_val();
    if (child_pos == Child::Left) {
        if (val_ < val_parent) {
            if (left_ != nullptr && left_->get_val() > val_parent) throw std::runtime_error("Значение переменной parent должно быть строго больше левого потомока данного узла\n");
            if (right_ != nullptr && right_->get_val() > val_parent) throw std::runtime_error("Значение переменной parent должно быть строго больше правого потомока данного узла\n");
            parent_ = parent;
        }
        else { throw std::runtime_error("Значение переменной parent должно быть строго больше значения данного узла\n"); }
    }
    else {
        if (val_ > val_parent) {
            if (left_ != nullptr && left_->get_val() < val_parent) throw std::runtime_error("Значение переменной parent должно быть строго меньше левого потомока данного узла\n");
            if (right_ != nullptr && right_->get_val() < val_parent) throw std::runtime_error("Значение переменной parent должно быть строго меньше правого потомока данного узла\n");
            parent_ = parent;
        }
        else { throw std::runtime_error("Значение переменной parent должно быть строго меньше значения данного узла\n"); }
    }
}

template <typename T> 
void Node<T>::delete_node() {
    delete left_;
    delete right_;
    delete parent_;
}

} // namespace tree

#endif