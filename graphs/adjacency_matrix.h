#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX

#include <string>

namespace grph 
{

class AdjacencyMatrix final
{   
    size_t matrix_size_;
    size_t size_;
    int** matrix_;
    public:
        AdjacencyMatrix() : matrix_size_(0), size_(0), matrix_(nullptr) {}
        AdjacencyMatrix(char* file_name);
        template <size_t N> AdjacencyMatrix(const int (&matrix)[N][N]);
        AdjacencyMatrix(const AdjacencyMatrix& matrix);
        AdjacencyMatrix(AdjacencyMatrix&& matrix);
        AdjacencyMatrix& operator=(const AdjacencyMatrix& matrix);
        AdjacencyMatrix& operator=(AdjacencyMatrix&& matrix);
        ~AdjacencyMatrix() { delete_matrix(); }
    public:
        void copy_matrix(const int* const* matrix, size_t size); 
        template <size_t N> void copy_matrix(const int (&matrix)[N][N]);
        const int* const* get_matrix() const { return matrix_; }
        size_t get_size() const { return size_; }
        size_t get_matrix_size() const { return matrix_size_; }
        void add_vertex(const int* const vertex, size_t n);
        template <size_t N> void add_vertex(const int (&vertex)[N]);
    private:
        int** get_matrix() { return matrix_; }
        bool extansion(size_t count_new_vert);
        void delete_matrix();
};

template <size_t N> 
grph::AdjacencyMatrix::AdjacencyMatrix(const int (&matrix)[N][N]) : matrix_(nullptr), size_(0), matrix_size_(0) {
    if (N == 0) throw std::runtime_error("Matrix must not be empty");
    copy_matrix(matrix);
}

template <size_t N> 
void grph::AdjacencyMatrix::copy_matrix(const int (&matrix)[N][N]) {
    delete_matrix();
    matrix_size_ = N;
    size_ = N;
    matrix_ = new int*[matrix_size_];
    for (size_t i = 0; i < matrix_size_; ++i) {
        matrix_[i] = new int[matrix_size_];
        for (size_t j = 0; j < matrix_size_; ++j) {
            matrix_[i][j] = matrix[i][j];
        }
    } 
}

template <size_t N> 
void grph::AdjacencyMatrix::add_vertex(const int (&vertex)[N]) {
    if (N == 0) throw std::runtime_error("Vertex is incompatible with this graph");
    if (N != matrix_size_) {
        if (matrix_size_ != 0) throw std::runtime_error("Vertex is incompatible with this graph");
        matrix_size_ = N;
        matrix_ = new int*[matrix_size_];
        for (size_t i = 0; i < matrix_size_; ++i) {
            matrix_[i] = new int[matrix_size_];
        }
    }
    extansion(1);
    for (size_t i = 0; i < N; ++i) {
        matrix_[size_][i] = vertex[i];
    }
    ++size_;
}


} // namespace grph

#endif