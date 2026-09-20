#include <iostream>
#include "adj_matrix.h"
#include "incidence_matrix.h"
#include "adj_list.h"

int main() {

    // "adj_matrix.h"

    std::cout << "__ADJACENCY_MATRIX__\n";
    AdjGraph graph1;
    graph1.LoadAdjGraph("adj_matrix.txt");
    graph1.PrintAdjMatrix();
    std::cout << "DFS:\n";
    graph1.DepthFirstSearch(0);
    std::cout << "BFS:\n";
    graph1.BreadthFirstSearch(0);
    int* dist1 = new int[7];
    int* parent1 = new int[7];
    std::cout << "Dijkstra:\n";
    graph1.Dijkstra(0, dist1, parent1);
    delete[] dist1; delete[] parent1;

    // "incidence_matrix.h"

    std::cout << "\n__INCIDENCE_MATRIX__\n";
    IncidenceMatrix graph2;
    graph2.LoadIncMatrix("incidence_matrix.txt");
    graph2.Print();
    std::cout << "DFS:\n";
    graph2.DepthFirstSearch(0);
    std::cout << "BFS:\n";
    graph2.BreadthFirstSearch(0);
    std::cout << "Dijkstra:\n";
    int* dist2 = new int[7];
    size_t* parent2 = new size_t[7];
    graph2.Dijkstra(0, dist2, parent2);
    delete[] dist2; delete[] parent2;

    // "adj_list.h"

    std::cout << "\n__ADJACENCY_LIST__\n";
    AdjList graph3;
    graph3.LoadAdjList("adj_list.txt");
    graph3.Print();
    std::cout << "DFS\n";
    graph3.DepthFirstSearch(1);
    std::cout << "BFS\n";
    graph3.BreadthFirstSearch(1);
    std::cout << "Dijkstra:\n";
    int* dist3 = new int[7];
    int* parent3 = new int[7];
    graph3.Dijkstra(1, dist3, parent3);
    delete[] dist3; delete[] parent3;
}