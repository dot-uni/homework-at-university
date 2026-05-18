#include <iostream>
#include <fstream>
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


int dijkstra(int** matrix, size_t size, int target) {
    int* list = new int[size]{0};
    for (int vert = 0; vert < size; ++vert) {
        for (int i = 0; i < size; ++i) {
            int weight = matrix[vert][i];
            if (weight == 0) continue;
            int path = list[vert] + weight;
            
            if (list[i] == 0) {
                list[i] = path;
            }
            else {
                list[i] = std::min(list[i], path);
            }
        }
    }
    int result = list[target-1];
    delete[] list;   
    return result;
}


int main(int argc, char** argv) {
    if (argc != 2) return 1;
    std::ifstream file(argv[1], std::ios::in);
    if (!file.good()) return 2;

    size_t size = -1;
    int target;
    int** matrix;

    size_t idx = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (size == -1) {
            size_t pos = line.find(' ');
            size = std::stoi(line.substr(0, pos));
            target = std::stoi(line.substr(pos + 1));
            if (target <= 0 && target > size) return 5;
            matrix = new int*[size];
        }
        else {
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
    }
    if (idx != size) return 4;

    int res = dijkstra(matrix, size, target);
    std::cout << res << "\n";

    for (int i = 0; i < size; ++i) {
        delete[] matrix[i]; 
    }
    delete matrix;
    return 0;
}