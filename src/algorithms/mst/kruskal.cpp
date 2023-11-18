#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/mst/kruskal.hpp"
#include "data_structures/disjoinedSet.hpp"

#include <vector>
#include <tuple>
#include <algorithm>

namespace gralph {
namespace algos {

kruskal::kruskal(const gralph::graph::WeightedGraph& graph)
    : m_graph(graph)
    {}

void kruskal::solve(int source) {
    std::vector<std::tuple<int, int, int>> sorted_edges = sort_edges();
    
    gralph::ds::DisjoinedSet disjoined_set(m_graph.get_vertex_num());

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


std::vector<std::tuple<int, int, int>> kruskal::sort_edges() {
    std::vector<std::tuple<int, int, int>> edges { m_graph.get_all_edges() };

    std::sort(edges.begin(), edges.end(), [](const auto& edge_1, const auto& edge_2) {
        return std::get<2>(edge_1) < std::get<2>(edge_2);
    });

    return edges;
}

}  // namespace algos
}  // namespace gralph
