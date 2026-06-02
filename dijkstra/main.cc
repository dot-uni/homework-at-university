#include <iostream>
#include <fstream>
#include <cfloat>
#include "queue.h"
// очередь рассмотрения
// массив размера кол-ва верщин
// условие остановки 


void print(float** matrix, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

float dijkstra(float** matrix, size_t size, int src, int target) {
    if ((src <= 0 || src > size) ||
        (target <= 0 || target > size))
        throw std::runtime_error("Такой вершины не существует");

    --src;
    --target;

    float* dist = new float[size];
    bool* visited = new bool[size]{};

    for (size_t i = 0; i < size; ++i)
        dist[i] = FLT_MAX;

    dist[src] = 0;

    for (size_t i = 0; i < size; ++i) {

        int closest = -1;

        for (size_t j = 0; j < size; ++j) {
            if (!visited[j] && (closest == -1 || dist[j] < dist[closest])) {
                closest = j;
            }
        }

        if (closest == -1 || dist[closest] == FLT_MAX ||
            closest == target)
            break;

        visited[closest] = true;

        for (size_t j = 0; j < size; ++j) {

            if (matrix[closest][j] == 0)
                continue;

            float newDist =
                dist[closest] + matrix[closest][j];

            if (dist[j] > newDist) {
                dist[j] = newDist;
            }
        }
    }

    float res = dist[target];

    delete[] dist;
    delete[] visited;

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
    float** matrix = new float*[size];

    while (std::getline(file, line)) {
        matrix[idx] = new float[size];
        size_t start = 0;
        for (size_t k = 0; k < size; ++k) {
            size_t pos = line.find(' ', start);

            if (pos == std::string::npos) {
                matrix[idx][k] = std::stof(line.substr(start));
            }
            else {
                matrix[idx][k] = std::stof(line.substr(start, pos - start));
                start = pos + 1;
            }
        }
        ++idx;
    }
    if (idx != size) return 4;

    print(matrix, size);
    float res = dijkstra(matrix, size, src, target);
    std::cout << res << "\n";

    
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i]; 
    }
    delete[] matrix;
    return 0;
}
