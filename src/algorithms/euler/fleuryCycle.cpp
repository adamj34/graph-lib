#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/euler/fleuryCycle.hpp"
#include "algorithms/search/dfs.hpp"


namespace gralph {
namespace algos {

fleuryCycle::fleuryCycle(const gralph::graph::WeightedGraph& graph) 
    : m_graph(graph)
    , m_is_eulerian(check_euler_cycle())
    , m_is_semi_eulerian(m_is_eulerian || check_euler_path())
    {}

void fleuryCycle::solve(int source) {
    m_source = source;

    // choose the staring point depending on the type of the graph
    int curr_node = choose_starting_point();
    if (curr_node == -1) { return; }
    while (m_graph.get_edge_num() > 0) {
        bool valid_edge_found { false };
        std::pair<int, int> edge {};
        for (int i = 0; i < m_graph.get_vertex_num(); i++) {
            if (m_graph.get_graph().at(curr_node)[i] != 0) {
                edge.first = curr_node;
                edge.second = i;
                int deleted_edge_weight = m_graph.get_edge_weight(edge);
                m_graph.delete_edge(edge);

                gralph::search::dfs dfs_algo{m_graph};
                dfs_algo.solve(curr_node);
                if (!dfs_algo.is_disconnected()) {
                    m_eulerian_cycle.push_back(edge);
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
            m_eulerian_cycle.push_back(edge);
            curr_node = edge.second;
        }
    }
}

bool fleuryCycle::check_euler_cycle() {
    for (auto &[vertex, neighbours] : m_graph.get_graph()) {
        if (m_graph.get_vertex_deg(vertex) % 2 != 0) {
            return false;
        }
    }
    return true;
}

bool fleuryCycle::check_euler_path() {
    int odd_deg_vertices { 0 };
    for (auto &[vertex, neighbours] : m_graph.get_graph()) {
        if (m_graph.get_vertex_deg(vertex) % 2 != 0) {
            ++odd_deg_vertices;
        }
    }
    return (odd_deg_vertices == 2) || (odd_deg_vertices == 0);
}

int fleuryCycle::find_starting_point() {
    for (auto &[vertex, neighbours] : m_graph.get_graph()) {
        if (m_graph.get_vertex_deg(vertex) % 2 != 0) {
                return vertex;
            }
        }
    return 0;
}

int fleuryCycle::choose_starting_point() {
    int start_node {};
    if (!m_is_eulerian && !m_is_semi_eulerian) {
        return -1;
    } else if (m_is_eulerian) {
        start_node = { m_source };
    } else if (m_is_semi_eulerian) {
        start_node = { find_starting_point() };
    }
    return start_node;
}

}  // namespace algos
}  // namespace gralph
