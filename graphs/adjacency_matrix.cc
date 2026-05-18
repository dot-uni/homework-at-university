#include <fstream>
#include "adjacency_matrix.h"


grph::AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& matrix) : matrix_(nullptr), size_(0), matrix_size_(0) {
    copy_matrix(matrix.get_matrix(), matrix.get_size());
}

grph::AdjacencyMatrix::AdjacencyMatrix(AdjacencyMatrix&& matrix) : matrix_(nullptr), size_(0), matrix_size_(0) {
    matrix_ = matrix.get_matrix();
    size_ = matrix.get_size();
    matrix_size_ = matrix.get_matrix_size();
}

grph::AdjacencyMatrix& grph::AdjacencyMatrix::operator=(const AdjacencyMatrix& matrix) {
    if (&matrix == this) return *this;
    copy_matrix(matrix.get_matrix(), matrix.get_size());
    return *this;
}

grph::AdjacencyMatrix& grph::AdjacencyMatrix::operator=(AdjacencyMatrix&& matrix) {
    if (&matrix == this) return *this;
    matrix_ = matrix.get_matrix();
    size_ = matrix.get_size();
    matrix_size_ = matrix.get_matrix_size();
    return *this;
}

grph::AdjacencyMatrix::AdjacencyMatrix(char* file_name) : matrix_(nullptr), size_(0) {
    std::ifstream file(file_name, std::ios::in);        
    if (!file.good()) throw std::runtime_error("Такой файл не существует\n");
    std::string line;
    while (std::getline(file, line)) {

    }
}

void grph::AdjacencyMatrix::copy_matrix(const int* const* matrix, size_t size) {
    if (matrix == nullptr || size == 0) throw std::runtime_error("Matrix must not be empty");
    delete_matrix();
    matrix_size_ = size;
    size_ = size;
    matrix_ = new int*[matrix_size_];
    for (size_t i = 0; i < matrix_size_; ++i) {
        matrix_[i] = new int[matrix_size_];
        for (size_t j = 0; j < matrix_size_; ++j) {
            matrix_[i][j] = matrix[i][j];
        }
    } 
}

void grph::AdjacencyMatrix::add_vertex(const int* const vertex, size_t n) {
    if (vertex == nullptr || n == 0) throw std::runtime_error("Vertex is incompatible with this graph");
    if (n != matrix_size_) {
        if (matrix_size_ != 0) throw std::runtime_error("Vertex is incompatible with this graph");
        matrix_size_ = n;
        matrix_ = new int*[matrix_size_];
        for (size_t i = 0; i < matrix_size_; ++i) {
            matrix_[i] = new int[matrix_size_];
        }
    }
    extansion(1);
    for (size_t i = 0; i < n; ++i) {
        matrix_[size_][i] = vertex[i];
    }
    ++size_;
}

bool grph::AdjacencyMatrix::extansion(size_t count_new_vert) {
    if (size_ < matrix_size_ || matrix_ == nullptr || matrix_size_ == 0) return false;
    size_t new_matrix_size = matrix_size_ + count_new_vert;
    int** new_matrix = new int*[new_matrix_size];
    for (size_t i = 0; i < new_matrix_size; ++i) {
        new_matrix[i] = new int[new_matrix_size];
    }
    for (size_t i = 0; i < matrix_size_; ++i) {
        for (size_t j = 0; j < matrix_size_; ++j) {
            new_matrix[i][j] = matrix_[i][j];
        }
    }
    delete_matrix();
    matrix_size_ = new_matrix_size;
    matrix_ = new_matrix;
    return true;
}

void grph::AdjacencyMatrix::delete_matrix() {
    if (matrix_ == nullptr || matrix_size_ == 0) return;
    for (size_t i = 0; i < matrix_size_; ++i) {
        delete [] matrix_[i]; 
    }
    delete [] matrix_;
}