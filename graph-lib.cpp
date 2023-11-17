
#include "algorithms/search/dfs.hpp"
#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/search/bfs.hpp"
#include "helpers/buildSubsets.hpp"
#include "problems/chinesePostman.hpp"
#include "algorithms/euler/fleuryCycle.hpp"

#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

int main() {

    gralph::graph::WeightedGraph graph{8, 9};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 5},
        {1, 2, 1},
        {2, 3, 3},
        {3, 4, 2},
        {2, 4, 1},
        {4, 5, 2},
        {2, 6, 1},
        {6, 4, 2},
        {1, 7, 3}
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle euler_cycle_finder{graph};
    gralph::algos::dijkstra path_finder{graph};

    gralph::problems::chinesePostman cp{graph, path_finder, euler_cycle_finder};
    cp.solve();
    std::vector<std::pair<int, int>> solution = cp.get_solution();

    int cost = cp.get_cost();
    for (auto [from_vertex, to_vertex] : solution) {
        std::cout << "(" << from_vertex << ", " << to_vertex << ") ";
    }

    cout << endl << cost << endl;

}
