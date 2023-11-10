#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/minimal_spanning_trees/prim.hpp"

#include <unordered_set>
#include <map>
#include <vector>
#include <limits>
#include <utility>


namespace gralph {
namespace algos {

prim::prim(const gralph::graph::WeightedGraph& graph) {
    int V_num { graph.get_verex_num() };
    for (int i = 0; i < V_num; ++i) {
        mst[i] = std::vector<int>();
    }

    std::map<int, std::vector<int>> graph_repr = { graph.get_graph() };
    added.insert(0);
    while (ssize(added) < V_num) {
        int min_val = std::numeric_limits<int>::max();
        int vertex_from = -1, vertex_to = -1;
        for (int vertex : added) {
            for (int candidate = 0; candidate < V_num; ++candidate) {
                if (!added.contains(candidate)) {
                    int weight = { graph_repr[vertex][candidate] };
                    if (0 < weight && weight <= min_val) {
                        min_val = { weight };
                        vertex_from = { vertex };
                        vertex_to = { candidate };
                    }
                }
            }
        }

        mst[vertex_from].push_back(vertex_to);
        added.insert(vertex_to);
        cost += min_val;
    }
}

} // namespace algos
}  // namespace gralph

