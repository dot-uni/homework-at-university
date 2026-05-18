#ifndef NODE_H
#define NODE_H

/*

сгенерировать 3000 строк состоящие из 4 символов накидать в графф и его динамическое 
rebuild(val) найдет val в дереве, если не найдет то будет корнем, если будет то корень и переделать граф

*/

namespace trs 
{

template <typename T> class Node 
{
    T val_;
    int count_ = 1;
    Node<T>* left_;
    Node<T>* right_;
    public:
        Node(const T& val) : val_(val), left_(nullptr), right_(nullptr) {} 
        Node(const T& val, Node<T>* left, Node<T>* right) : val_(val) {
            if (left == right) throw std::runtime_error("Указатели указывают на один и тот же узел.\n");
            left_ = left; right_ = right;
        } 
    public:
        void increace_count();
        T get_val() const;
        Node<T>* get_left() const;
        Node<T>* get_right() const;
        void set_val(T val);
        void set_left_right(Node<T>* left, Node<T>* right);
        void set_left(Node<T>* left);
        void set_right(Node<T>* right);
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
void Node<T>::set_val(T val) { val_ = val; }

template <typename T> 
void Node<T>::set_left_right(Node<T>* left, Node<T>* right) {
    if (left == right) throw std::runtime_error("Указатели указывают на один и тот же узел.\n");
    left_ = left; right_ = right;
}

template <typename T> 
void Node<T>::set_left(Node<T>* left) {
    if (left == right_ && left != nullptr) throw std::runtime_error("Указатели указывают на один и тот же узел.\n");
    left_ = left;
}

template <typename T> 
void Node<T>::set_right(Node<T>* right) {
    if (left_ == right && right != nullptr) throw std::runtime_error("Указатели указывают на один и тот же узел.\n");
    right_ = right;
}

} // namespace tree

#endif