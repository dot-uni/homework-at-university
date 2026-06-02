#include <iostream>
#include <fstream>
#include <string>
#include "adj_list.h"
#include "stack.h"
#include "queue.h"


void AdjList::delete_list() {
    for (int i = 0; i < size_; ++i) {
        delete[] list_[i];
    }
    delete[] list_;
}

bool AdjList::LoadAdjList(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Файл не был открыт\n";
        return false;
    }

    int size;
    file >> size;
    if (size == 0) {
        file.close();
        std::cerr << "Длина не должна быть нулевой\n";
        return false;
    }   
    std::string rubbish;
    std::getline(file, rubbish);
    size_ = size;

    if (list_ != nullptr) {
        delete_list();
    }
    list_ = new EdgeNode*[size_];
    for (int i = 0; i < size_; ++i) { list_[i] = nullptr; }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        int colon_pos =  line.find(":");
        if (colon_pos == std::string::npos) continue;

        std::string src_str = line.substr(0, colon_pos);
        int src = std::stoi(src_str);

        int src_idx = src - 1;
        if (src_idx < 0 || src_idx >= size_) continue;

        std::string second_part = line.substr(colon_pos+1);
        while (second_part.length() != 0) {
            int open_brac_pos = second_part.find("(");
            if (open_brac_pos == std::string::npos) break;

            int close_brac_pos = second_part.find(")");
            if (close_brac_pos == std::string::npos) break;

            std::string in_brackets = second_part.substr(open_brac_pos+1, close_brac_pos-2);

            int comma_pos = in_brackets.find(",");
            if (comma_pos == std::string::npos) break;

            std::string to_str = in_brackets.substr(0, comma_pos);
            std::string weight_str = in_brackets.substr(comma_pos+1);

            int to = std::stoi(to_str);
            int weight = std::stoi(weight_str);

            if (to == std::string::npos || weight == std::string::npos) break;

            if (to > 0 && to <= size_) {
                EdgeNode* neighbour = new EdgeNode{to-1, weight, list_[src_idx]};
                list_[src_idx] = neighbour;
            }
            second_part = second_part.substr(close_brac_pos + 1);
        }
    }

    file.close();
    return true;
}

void AdjList::BreadthFirstSearch(int start) const {
    if (start <= 0 || start > size_) throw std::runtime_error("Такой вершины не существует\n");
    --start;

    bool* visited = new bool[size_];
    Queue queue;
    queue.push(start);
    while (!queue.is_empty()) {
        int current = queue.pop();
        if (visited[current]) continue;
        visited[current] = true;
        std::cout << "Visited: " << current+1 << "\n";

        EdgeNode* tmp = list_[current];
        while (tmp != nullptr) {
            int to = tmp->to;
            if (!visited[to]) queue.push(to);
            tmp = tmp->next;
        }
    }
    delete[] visited;
}

void AdjList::DepthFirstSearch(int start) const {
    if (start <= 0 || start > size_) throw std::runtime_error("Такой вершины не существует\n");
    --start;

    bool* visited = new bool[size_];
    Stack stack;
    stack.push(start);
    while (!stack.is_empty()) {
        int current = stack.pop();
        if (visited[current]) continue;
        visited[current] = true;
        std::cout << "Visited: " << current+1 << "\n";

        EdgeNode* tmp = list_[current];
        while (tmp != nullptr) {
            int to = tmp->to;
            if (!visited[to]) stack.push(to);
            tmp = tmp->next;
        }
    }
    delete[] visited;
}

void AdjList::Dijkstra(int start, int* dist, int* parent) const {
    if (start <= 0 || start > size_) throw std::runtime_error("Такой вершины не существует\n");
    --start;

    bool* visited = new bool[size_]{false};
    for (int i = 0; i < size_; ++i) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[start] = 0;

    for (int i = 0; i < size_; ++i) {
        int minv = -1;
        for (int j = 0; j < size_; ++j) {
            if (!visited[j] && (minv == -1 || dist[minv] > dist[j])) {
                minv = j;
            }
        }
        if (minv == -1) break;
        if (dist[minv] == INT_MAX) continue;
        visited[minv] = true;

        EdgeNode* tmp = list_[minv];
        while (tmp != nullptr) {
            int to = tmp->to;
            if (!visited[to]) {
                int v = dist[minv] + tmp->weight;
                if (dist[to] > v) {
                    dist[to] = v;
                    parent[to] = minv;
                }
            }
            tmp = tmp->next;
        }
    }

    for (int i = 0; i < size_; ++i) {
        if (i == start) continue;
        if (dist[i] == INT_MAX) {
            std::cout << "Пути до вершины " << i+1 << " не существует\n";
            continue;
        }
        std::cout << "Путь до вершины " << i+1 << " равен " << dist[i] << "\n";

        int* parent_buf = new int[size_];
        int current = i;
        int idx = 0;
        while (current != -1) {
            parent_buf[idx++] = current;
            current = parent[current];
        }

        for (int j = idx-1; j >= 0; --j) {
            std::cout << parent_buf[j]+1 << "";
            if (j > 0) std::cout << " -> ";
        }
        std::cout << "\n";
        delete[] parent_buf;
    }

    delete[] visited;
}

void AdjList::Print() const {
    if (list_ == nullptr) throw std::runtime_error("Список пуст");
    for (int row = 0; row < size_; ++row) {
        if (list_[row] == nullptr) continue;

        std::cout << row+1 << ": ";
        EdgeNode* tmp = list_[row];
        while(tmp != nullptr) {
            std::cout << tmp->to+1 << " ";
            tmp = tmp->next;
        }
        std::cout << "\n";
    }
}