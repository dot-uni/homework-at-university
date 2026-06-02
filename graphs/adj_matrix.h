#ifndef ADJ_GRAPH
#define ADJ_GRAPH

#include "queue.h"
#include "stack.h"
#include <string>

class AdjGraph 
{
    size_t size_;
    int** matrix_;
    public:
        AdjGraph() : size_(0), matrix_(nullptr) {}
        AdjGraph(const std::string& file_name);
        ~AdjGraph() { delete_matrix(); }
        bool LoadAdjGraph(const std::string& file_name);
        void PrintAdjMatrix() const;
        size_t GetSize() const { return size_; }
        void BreadthFirstSearch(size_t start) const;
        void DepthFirstSearch(size_t start) const;
        void Dijkstra(size_t start, int* dist, int* parent) const;
    private:
        void delete_matrix() {
            for (size_t i = 0; i < size_; ++i) {
                delete[] matrix_[i];
            }
            delete[] matrix_;
        }
};

#endif 