#include <iostream>
#include <fstream>
#include "adj_matrix.h"

AdjGraph::AdjGraph(const std::string& file_name) : AdjGraph() {
    if (!LoadAdjGraph(file_name)) throw std::runtime_error("Граф не был создан");
}

bool AdjGraph::LoadAdjGraph(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Файл не был открыт, возможно такого файла не существует\n";
        return false;
    }
    
    size_t size = 0;
    file >> size;
    if (size == 0) {
        file.close();
        std::cerr << "Размер файла не должен быть равен 0\n";
        return false;
    }
    if (matrix_ != nullptr) {
        delete_matrix();
    }
    size_ = size;

    matrix_ = new int*[size_];
    for (size_t row = 0; row < size_; ++row) {
        matrix_[row] = new int[size_];
        for (size_t col = 0; col < size_; ++col) {
            int num;
            file >> num;
            matrix_[row][col] = num;
        }
    }
    file.close();
    return true;
}

void AdjGraph::PrintAdjMatrix() const {
    if (size_ == 0) std::cout << "Граф пустой";
    for (size_t row = 0; row < size_; ++row) {
        for (size_t col = 0; col < size_; ++col) {
            std::cout << matrix_[row][col] << " ";
        }
        std::cout << "\n";
    }
}

/* 
Сложность: O(N+E), где
    N – число вершин,
    E – число ребер и дуг.
*/
void AdjGraph::BreadthFirstSearch(size_t start) const {
    if (start >= size_) throw std::runtime_error("Такой вершины не существует");
    bool* visited = new bool[size_]{false};

    Queue queue;
    queue.push(start);
    while(!queue.is_empty()) {
        int current = queue.pop();
        if (visited[current]) continue;
        visited[current] = true;
        
        std::cout << "Visited: " << current+1 << "\n";

        for (size_t col = 0; col < size_; ++col) {
            if (matrix_[current][col] == 0 || visited[col] == true) continue;
            queue.push(col);
        }
    }
    delete[] visited;
}


/* 
Сложность: O(N+E), где
    N – число вершин,
    E – число ребер и дуг.
*/
void AdjGraph::DepthFirstSearch(size_t start) const {
    if (start >= size_) throw std::runtime_error("Такой вершины не существует");
    bool* visited = new bool[size_]{false};
    
    Stack stack;
    stack.push(start);

    while (!stack.is_empty()) {
        int current = stack.pop();
        if (visited[current]) continue;
        visited[current] = true;
        
        std::cout << "Visited: " << current+1 << "\n";
        for (size_t col = 0; col < size_; ++col) {
            if (matrix_[current][col] == 0 || visited[col] == true) continue;
            stack.push(col);
        }
    }
    delete[] visited;
}

/* 
Сложность: O(N^2+E), где
    N – число вершин,
    E – число ребер и дуг.
*/
void AdjGraph::Dijkstra(size_t start, int* dist, int* parent) const {
    if (start >= size_) throw std::runtime_error("Такой вершины не существует");
    
    bool* visited = new bool[size_]{false};

    for (size_t i = 0; i < size_; ++i) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[start] = 0;

    for (size_t i = 0; i < size_; ++i) {
        size_t min_node = size_;
        for (size_t j = 0; j < size_; ++j) {
            if (!visited[j] && (min_node == size_ || dist[min_node] > dist[j])) {
                min_node = j;
            }
        }
        if (min_node == size_) break;
        visited[min_node] = true;

        for (size_t j = 0; j < size_; ++j) {
            if (matrix_[min_node][j] == 0 || visited[j] || dist[min_node] == INT_MAX) continue;
            int min_path = dist[min_node] + matrix_[min_node][j];
            if (dist[j] > min_path) {
                dist[j] = min_path;
                parent[j] = min_node;
            }
        }

    }
    
    delete[] visited;

    for (size_t vertex = 0; vertex < size_; ++vertex) {
        if (vertex == start) continue;
        if (dist[vertex] == INT_MAX) {
            std::cout << "Пути до вершины " << vertex+1 << " нету\n";
            continue;
        }
        std::cout << "Путь до вершины " << vertex+1 << " = " << dist[vertex] << "\n";

        int* path_buffer = new int[size_];
        size_t idx = 0;
        int current = vertex;
        while (current != -1) {
            path_buffer[idx++] = current;
            current = parent[current];
        }

        for (size_t i = idx; i > 0; --i) {
            std::cout << path_buffer[i-1]+1;
            if (i > 1) std::cout << " -> ";
        }
        std::cout << "\n";
        delete[] path_buffer;
    }
}