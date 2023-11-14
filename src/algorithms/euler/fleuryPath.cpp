#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/euler/fleuryPath.hpp"
#include "algorithms/search/dfs.hpp"

#include <vector>

namespace gralph {
namespace euler {

gralph::euler::fleuryPath::fleuryPath(const gralph::graph::WeightedGraph& graph) 
    : m_graph(graph)
    , m_is_semi_eulerian(check_euler_path())

    {
        if (!is_semi_eulerian()) { return; };
        int starting_point = find_starting_point();

        int curr_node = starting_point;
        while (m_graph.get_edge_num() > 0) {

            bool valid_edge_found { false };
            std::pair<int, int> edge {};
            for (int i = 0; i < m_graph.get_vertex_num(); i++) {
                if (m_graph.get_graph().at(curr_node)[i] != 0) {
                    edge.first = curr_node; edge.second = i;
                    int deleted_edge_weight = m_graph.get_edge_weight(edge);
                    m_graph.delete_edge(edge);
                    gralph::search::dfs dfs_algo{m_graph, curr_node}; 
                    if (!dfs_algo.is_disconnected()) {
                        m_eulerian_path.push_back(edge);
                        curr_node = i;
                        valid_edge_found = true;
                        m_cost += deleted_edge_weight;
                        break;
                    } else {
                        m_graph.add_edge({edge.first, edge.second, deleted_edge_weight});
                    }
                }
            }

            if (!valid_edge_found) {  // the graph has to be disconnnected
                m_cost += m_graph.get_edge_weight(edge);
                m_graph.delete_edge(edge);
                m_eulerian_path.push_back(edge);
                curr_node = edge.second;
            }
        }
    }

bool gralph::euler::fleuryPath::check_euler_path() {
    int odd_deg_vertices { 0 };
    for (auto &[vertex, neighbours] : m_graph.get_graph()) {
        if (m_graph.get_vertex_deg(vertex) % 2 != 0) {
            ++odd_deg_vertices;
        }
    }
    return (odd_deg_vertices == 2) || (odd_deg_vertices == 0);
}

int gralph::euler::fleuryPath::find_starting_point() {
    for (auto &[vertex, neighbours] : m_graph.get_graph()) {
        if (m_graph.get_vertex_deg(vertex) % 2 != 0) {
                return vertex;
            }
        }
    return 0;
}


}  // namespace euler
}  // namespace gralph
