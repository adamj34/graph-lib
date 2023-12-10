
#include "algorithms/search/dfs.hpp"
#include "graph_repr/WeightedGraph.hpp"
#include "graph_repr/WeightedMultiGraph.hpp"

#include "algorithms/search/dfs.hpp"
#include "algorithms/search/bfs.hpp"
#include "helpers/buildSubsets.hpp"
#include "problems/chinesePostman.hpp"
#include "algorithms/euler/fleuryCycle.hpp"
#include "algorithms/mst/kruskal.hpp"
#include "algorithms/mst/prim.hpp"
#include "problems/travelingSalesman.hpp"
#include "graph_repr/WeightedDirectedGraph.hpp"

#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

int main() {

    gralph::graph::WeightedDirectedGraph graph{5, 10};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 2, 1},
        {0, 3, 3},
        {0, 4, 1},
        {1, 2, 1},
        {1, 3, 2},
        {1, 4, 2},
        {2, 3, 1},
        {2, 4, 2},
        {3, 4, 1}
    };

    graph.build_edges(coords_tuples);
    graph.print_matrix();

}
