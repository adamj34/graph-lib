
#include "algorithms/search/dfs.hpp"
#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/search/bfs.hpp"

#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

int main() {

    gralph::graph::WeightedGraph graph{5, 5};
        std::vector<std::tuple<int, int, int>> coords_tuples = {
            {0, 1, 1},
            {1, 2, 1},
            {2, 3, 1},
            {3, 4, 1},
            {4, 0, 1},
        };
        graph.build_edges(coords_tuples);

        gralph::search::bfs bfs_algo{graph, 4};
        std::unordered_set<int> visited_vertices = bfs_algo.get_visited();
}
