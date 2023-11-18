
#include "algorithms/search/dfs.hpp"
#include "graph_repr/WeightedGraph.hpp"
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

    gralph::graph::WeightedGraph graph{6, 7};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 2},
        {2, 0, 3},
        {3, 4, 4},
        {4, 5, 5},
        {4, 1, 6},
        {5, 3, 2}
    };
    graph.build_edges(coords_tuples);

    gralph::algos::kruskal kruskal_algo{graph};
    kruskal_algo.solve();
    std::map<int, std::vector<int>> mst = kruskal_algo.get_mst();
    int cost = kruskal_algo.get_cost();
    for (auto& [node, neighbours] : mst) {
        cout << node << ": ";
        for (auto& neighbour : neighbours) {
            cout << neighbour << " ";
        }
        cout << endl;
    }
}
