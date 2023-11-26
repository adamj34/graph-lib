#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/mst/kruskal.hpp"
#include "data_structures/disjoinedSet.hpp"
#include "graph_repr/IGraph.hpp"

#include <vector>
#include <tuple>
#include <algorithm>

namespace gralph {
namespace algos {


void kruskal::solve(const gralph::graph::WeightedGraph& graph, int source = 0) {
    std::vector<std::tuple<int, int, int>> sorted_edges = sort_edges(graph);
    
    gralph::ds::DisjoinedSet disjoined_set(graph.get_vertex_num());

    for (const auto& edge : sorted_edges) {
        int node_1 = std::get<0>(edge);
        int node_2 = std::get<1>(edge);
        int weight = std::get<2>(edge);

        // check if the endpoints of the edge are in the same set
        if (disjoined_set.find_set(node_1) != disjoined_set.find_set(node_2)) { 
            disjoined_set.union_sets(node_1, node_2);
            m_mst[node_1].push_back(node_2);
            m_cost += weight;
        }
    }
}

void kruskal::solve(const gralph::graph::WeightedMultiGraph& graph, int source = 0) {
    // TODO
}

std::vector<std::tuple<int, int, int>> kruskal::sort_edges(const gralph::graph::IGraph& graph) {
    std::vector<std::tuple<int, int, int>> edges { graph.get_all_edges() };

    std::sort(edges.begin(), edges.end(), [](const auto& edge_1, const auto& edge_2) {
        return std::get<2>(edge_1) < std::get<2>(edge_2);
    });

    return edges;
}

}  // namespace algos
}  // namespace gralph
