
#include "include/algorithms/shortest_path/dijkstra.hpp"
#include "include/graph_repr/WeightedGraph.hpp"
#include <iostream>
using namespace std;



int main() {
    gralph::graph::WeightedGraph graph{9, 28};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 4},
        {0, 7, 8},
        {1, 0, 4},
        {1, 2, 8},
        {1, 7, 11},
        {2, 1, 8},
        {2, 3, 7},
        {2, 5, 4},
        {2, 8, 2},
        {3, 2, 7},
        {3, 4, 9},
        {3, 5, 14},
        {4, 3, 9},
        {4, 5, 10},
        {5, 2, 4},
        {5, 3, 14},
        {5, 4, 10},
        {5, 6, 2},
        {6, 5, 2},
        {6, 7, 1},
        {6, 8, 6},
        {7, 0, 8},
        {7, 1, 11},
        {7, 6, 1},
        {7, 8, 7},
        {8, 2, 2},
        {8, 6, 6},
        {8, 7, 7}
    };

    graph.build_edges(coords_tuples);

    for (auto& [vertex, neighbors] : graph.get_graph()) {
        cout << vertex << ": ";
        for (auto& neighbor : neighbors) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
    gralph::algos::Dijkstra dijkstra{graph, 0};
    std::unordered_map<int, int> shortest_paths = dijkstra.get_shortest_paths();

    for (auto& [vertex, distance] : shortest_paths) {
        cout << vertex << " " << distance << endl;
    }

}
