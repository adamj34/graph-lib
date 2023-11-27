
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

#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

int main() {

    gralph::graph::WeightedGraph graph{7, 21};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 2, 1},
        {0, 3, 3},
        {0, 4, 1},
        {0, 5, 8},
        {0, 6, 2},
        {1, 2, 1},
        {1, 3, 2},
        {1, 4, 2},
        {1, 5, 5},
        {1, 6, 1},
        {2, 3, 1},
        {2, 4, 2},
        {2, 5, 1},
        {2, 6, 2},
        {3, 4, 1},
        {3, 5, 2},
        {3, 6, 1},
        {4, 5, 1},
        {4, 6, 2},
        {5, 6, 1}
    };
    graph.build_edges(coords_tuples);
    graph.print_matrix();
    cout << graph.is_semi_eulerian() << endl;
    gralph::algos::fleuryCycle eulerCycleFinder;
    gralph::algos::prim mstFinder;
    gralph::problems::travelingSalesman tsp(graph, eulerCycleFinder, mstFinder);
    tsp.solve();

    cout << tsp.get_cost() << endl;
    std::vector<std::pair<int, int>> solution = tsp.get_solution();
    for (auto& [from_vertex, to_vertex] : solution) {
        cout << from_vertex << " " << to_vertex << endl;
    }
}
