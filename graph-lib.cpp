
#include "algorithms/search/dfs.hpp"
#include "graph_repr/WeightedGraph.hpp"

#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

int main() {
    gralph::graph::WeightedGraph graph{6, 6}; 

    std::vector<std::tuple<int, int, int>> edges = {
        {0, 1, 1},
        {0, 3, 1},
        {1, 2, 1},
        {1, 4, 1},
        {3, 5, 1},
        {2, 4, 5}
    };
    graph.build_edges(edges);

    gralph::search::dfs dfs_algo{graph, 0};
    bool has_cycle = dfs_algo.contains_cycle();

    cout << "Has cycle: " << has_cycle << endl;
    auto visited = dfs_algo.get_visited();
    cout << "Visited vertices: ";
    for (int el : visited) {
        cout << el << " ";
    }
}
