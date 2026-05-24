#include <iostream>
#include <fstream>
#include "queue.h"
// очередь рассмотрения
// массив размера кол-ва верщин
// условие остановки 


void print(int** matrix, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}


int dijkstra(int** matrix, size_t size, int src, int target) {
    if ((src <= 0 || src > size) || (target <= 0 || target > size)) throw std::runtime_error("Такой вершины не существует");
    int* dist = new int[size];
    for (size_t i = 0; i < size; ++i) dist[i] = INT_MAX;
    --src;
    dist[src] = 0;
    Queue<std::pair<int, int>> pq {{0, src}};
    while(!pq.empty()) {
        auto top = pq.pop();
        for (size_t i = 0; i < size; ++i) {
            int weight = matrix[top.second][i];
            if (weight == 0) continue;
            if (dist[i] > dist[top.second] + weight) {
                dist[i] = dist[top.second] + weight;
                pq.push({dist[i], i});
            }
        }
    }

    int res = dist[target-1];
    delete[] dist;
    return res;
}


int main(int argc, char** argv) {
    if (argc != 2) return 1;
    std::ifstream file(argv[1], std::ios::in);
    if (!file.good()) return 2;

    size_t idx = 0;
    std::string line;

    std::getline(file, line);
    size_t pos = line.find(' ');

    int src = std::stoi(line.substr(0, pos));
    int target = std::stoi(line.substr(pos + 1));

    std::getline(file, line);
    size_t size = std::stoi(line);
    int** matrix = new int*[size];

    while (std::getline(file, line)) {
        matrix[idx] = new int[size];
        size_t start = 0;
        for (size_t k = 0; k < size; ++k) {
            size_t pos = line.find(' ', start);

            if (pos == std::string::npos) {
                matrix[idx][k] = std::stoi(line.substr(start));
            }
            else {
                matrix[idx][k] = std::stoi(line.substr(start, pos - start));
                start = pos + 1;
            }
        }
        ++idx;
    }
    if (idx != size) return 4;

    // print(matrix, size);
    int res = dijkstra(matrix, size, src, target);
    std::cout << res << "\n";

    for (int i = 0; i < size; ++i) {
        delete[] matrix[i]; 
    }
    delete[] matrix;
    return 0;
}