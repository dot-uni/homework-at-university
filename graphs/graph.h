#ifndef GRAPH_EDGE_LIST_H
#define GRAPH_EDGE_LIST_H

#include <string>
#include <set>
/*

1) Список ребер – набор пар вершин, соединенных ребрами.
2) Матрица смежности – представляет из себя квадратную матрицу, где строки и столбцы представляют вершины.
3) Набор степеней вершин – граф представляет список степеней каждой вершины, то есть количество ребер, которые к ней прилегают.
4) Список смежностей – для каждой вершины хранится список индексов вершин, с которыми она соединена.

*/

namespace grph {

using Edge = std::pair<int, int>;

class GraphEdgeList final
{   
    size_t num_edges_;
    std::set<Edge> edges_;
    public:
        GraphEdgeList() : num_edges_(0) {}
        GraphEdgeList(const int (&edge)[2]);
        template <size_t N> GraphEdgeList(const int (&edges)[N][2]);
    public:
        void insert(const int (&edge)[2]);
        template <size_t N> void insert(const int (&edges)[N][2]);
        void remove(const int (&edge)[2]);
        template <size_t N> void remove(const int (&edges)[N][2]);
        bool contains(const int edge[2]) const;
        std::set<Edge>::iterator begin() { return edges_.begin(); }
        std::set<Edge>::const_iterator begin() const { return edges_.cbegin(); }
        std::set<Edge>::iterator end() { return edges_.end(); }
        std::set<Edge>::const_iterator end() const { return edges_.cend(); }
};

template <size_t N>
void grph::GraphEdgeList::insert(const int (&edges)[N][2]) {
    size_t num_edges = N;
    for (size_t i = 0; i < num_edges; ++i) {
        int lhs = edges[i][0], rhs = edges[i][1];
        if (lhs > rhs) std::swap(lhs, rhs);
        edges_.insert({lhs, rhs});
    }
}

template <size_t N>
void grph::GraphEdgeList::remove(const int (&edges)[N][2]) {
    size_t num_edges = N;
    for (size_t i = 0; i < num_edges; ++i) {
        int lhs = edges[i][0], rhs = edges[i][1];
        if (lhs > rhs) std::swap(lhs, rhs);
        if (edges_.count({lhs, rhs}) != 0) edges_.erase({lhs, rhs});
    }
}

template <size_t N>
grph::GraphEdgeList::GraphEdgeList(const int (&edges)[N][2]) : num_edges_(N) {
    for (size_t i = 0; i < num_edges_; ++i) {
        int lhs = edges[i][0], rhs = edges[i][1];
        if (lhs > rhs) std::swap(lhs, rhs);
        edges_.insert({lhs, rhs});
    }
}

grph::GraphEdgeList::GraphEdgeList(const int (&edge)[2]) : num_edges_(1) {
    int lhs = edge[0], rhs = edge[1];
    if (lhs > rhs) std::swap(lhs, rhs);
    edges_.insert({lhs, rhs});
}

void grph::GraphEdgeList::insert(const int (&edge)[2]) {
    int lhs = edge[0], rhs = edge[1];
    if (lhs > rhs) std::swap(lhs, rhs);
    edges_.insert({lhs, rhs}); 
}

void grph::GraphEdgeList::remove(const int (&edge)[2]) {
    int lhs = edge[0], rhs = edge[1];
    if (lhs > rhs) std::swap(lhs, rhs);
    if (edges_.count({lhs, rhs}) != 0) edges_.erase({lhs, rhs});
}

bool grph::GraphEdgeList::contains(const int edge[2]) const {
    int lhs = edge[0], rhs = edge[1];
    if (lhs > rhs) std::swap(lhs, rhs);

    if (edges_.count({lhs, rhs}) == 0) return false;
    return true;
}

} // namespace grph

#endif
