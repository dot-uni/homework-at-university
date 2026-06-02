#include <iostream>
#include <fstream>
#include "stack.h"
#include "queue.h"
#include "incidence_matrix.h"

void IncidenceMatrix::delete_matrix() {
    for (size_t i = 0; i < vcount_; ++i) {
        delete[] matrix_[i];
    }
    delete[] matrix_;
}

bool IncidenceMatrix::LoadIncMatrix(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Файл не был открыт\n";
        return false;
    }

    file >> vcount_ >> ecount_;

    if (vcount_ == 0 || ecount_ == 0) {
        file.close();
        std::cerr << "Количество вершин и ребер не должно быть равно 0\n";
        return false;
    }

    if (matrix_ != nullptr) {
        delete_matrix();
    }
    matrix_ = new int*[vcount_];

    for (size_t row = 0; row < vcount_; ++row) {
        matrix_[row] = new int[ecount_];
        for (size_t col = 0; col < ecount_; ++col) {
            file >> matrix_[row][col];
        }
    }

    file.close();
    return true;
}

void IncidenceMatrix::Print() const {
    for (size_t row = 0; row < vcount_; ++row) {
        for (size_t col = 0; col < ecount_; ++col) {
            std::cout << matrix_[row][col] << " ";
        }
        std::cout << "\n";
    }
}

void IncidenceMatrix::BreadthFirstSearch(size_t start) const {
    if (start >= vcount_) throw std::runtime_error("Такой вершины нет");
    bool* visited = new bool[vcount_]{false};
    Queue queue;
    queue.push(start);
    while(!queue.is_empty()) {
        size_t current = queue.pop();
        if (visited[current]) continue;
        visited[current] = true;
        std::cout << "Visited: " << current+1 << "\n";

        for (size_t col = 0; col < ecount_; ++col) {
            if (matrix_[current][col] == 0) continue;
            for (size_t row = 0; row < vcount_; ++row) {
                if (current != row && matrix_[row][col] != 0 && !visited[row]) {
                    queue.push(row);
                    break;
                }
            }
        }
    }

    delete[] visited;
}

void IncidenceMatrix::DepthFirstSearch(size_t start) const {
    if (start >= vcount_) throw std::runtime_error("Такой вершины нет");

    bool* visited = new bool[vcount_]{false};
    Stack stack;
    stack.push(start);
    while(!stack.is_empty()) {
        size_t current = stack.pop();
        if (visited[current]) continue;
        visited[current] = true;
        std::cout << "Visited: " << current+1 << "\n";

        for (size_t col = 0; col < ecount_; ++col) {
            if (matrix_[current][col] == 0) continue;
            for (size_t row = 0; row < vcount_; ++row) {
                if (current != row && matrix_[row][col] != 0 && !visited[row]) {
                    stack.push(row);
                    break;
                }
            }
        }
    }

    delete[] visited;
}

void IncidenceMatrix::Dijkstra(size_t start, int* dist, size_t* parent) const {
    if (start >= vcount_) throw std::runtime_error("Такой вершины нет");

    bool* visited = new bool[vcount_]{false};

    for (size_t i = 0; i < vcount_; ++i) {
        dist[i] = INT_MAX;
        parent[i] = vcount_;
    }
    dist[start] = 0;

    for (size_t i = 0; i < vcount_; ++i) {
        size_t minv = vcount_;
        for (size_t j = 0; j < vcount_; ++j) {
            if (!visited[j] && (minv == vcount_ || dist[minv] > dist[j])) {
                minv = j;
            }
        }

        if (minv == vcount_) break;
        visited[minv] = true;
        if (dist[minv] == INT_MAX) continue;

        for (size_t col = 0; col < ecount_; ++col) {
            if (matrix_[minv][col] == 0) continue;
            for (size_t row = 0; row < vcount_; ++row) {
                if (minv != row && matrix_[row][col] != 0) {
                    if (visited[row]) continue;
                    int w = dist[minv] + matrix_[row][col];
                    if (dist[row] > w) {
                        dist[row] = w;
                        parent[row] = minv;
                    }
                    break;
                }
            }
        }
    }

    delete[] visited;

    for (size_t v = 0; v < vcount_; ++v) {
        if (v == start) continue;
        else if (dist[v] == INT_MAX) {
            std::cout << "Пути до вершины " << v+1 << " нету\n";
            continue;
        }
        std::cout << "Путь до вершины " << v+1 << " = " << dist[v] << "\n";

        size_t* parent_buf = new size_t[vcount_];
        size_t current = v;
        size_t idx = 0;
        while (current != vcount_) {
            parent_buf[idx++] = current;
            current = parent[current];
        }

        for (size_t i = idx; i > 0; --i) {
            std::cout << parent_buf[i-1]+1;
            if (i > 1) std::cout << " -> ";
        }
        std::cout << "\n";
        delete[] parent_buf;
    }
}