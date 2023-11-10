
#include "include/algorithms/minimal_spanning_trees/prim.hpp"
#include "include/graph_repr/WeightedGraph.hpp"
#include <iostream>
using namespace std;



int main() {
    gralph::graph::WeightedGraph graph{5, 5};
    vector<tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
    };
    graph.build_edges(coords_tuples);
    graph.print_matrix();

    gralph::algos::prim prim_res = gralph::algos::prim(graph);
    auto res = prim_res.get_mst();
    auto cost = prim_res.get_cost();
    cout << "cost: " << cost << endl;

    // cout << "cost: " << res.second << endl;
    for (const auto& [k, v] : res) {
        cout << k << ": ";
        for (const auto& elem : v) {
            cout << elem << " ";
        }
        cout << endl;
    }

}
