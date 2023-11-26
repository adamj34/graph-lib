
#include "algorithms/search/dfs.hpp"
#include "graph_repr/WeightedGraph.hpp"
#include "graph_repr/WeightedMultiGraph.hpp"

#include "algorithms/search/dfs.hpp"
#include "algorithms/search/bfs.hpp"
#include "helpers/buildSubsets.hpp"
#include "problems/chinesePostman.hpp"
#include "algorithms/euler/fleuryCycle.hpp"
#include "algorithms/mst/kruskal.hpp"

#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

int main() {

gralph::graph::WeightedMultiGraph graph{7, 12};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 2},
        {2, 0, 3},
        {3, 4, 4},
        {4, 5, 5},
        {4, 1, 6},
        {5, 3, 2},
        {1, 2, 8},
        {6, 4, 2},
        {4, 3, 7}
    };
    graph.build_edges(coords_tuples);

    cout << graph.is_eulerian() << endl;

    gralph::algos::fleuryCycle fleury_algo{};
    fleury_algo.solve(graph, 4);
    std::vector<std::pair<int, int>> eulerian_path = fleury_algo.get_eulerian_cycle();

    std::cout << "Eulerian cycle: ";
    for (auto &[node, val] : eulerian_path) {
        std::cout << "(" << node << ", " << val << ") ";
    }

    std::cout << fleury_algo.get_cost() << std::endl;
}
