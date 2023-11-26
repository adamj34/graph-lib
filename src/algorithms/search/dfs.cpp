#include "algorithms/search/dfs.hpp"
#include "graph_repr/WeightedGraph.hpp"
#include "graph_repr/WeightedMultiGraph.hpp"

#include <stack>
#include <unordered_set>
#include <algorithm>
#include <iostream>

namespace gralph {
namespace search {


void dfs::solve(const gralph::graph::WeightedGraph& graph, int source = 0) {
    const std::map<int, std::vector<int>>& graph_repr = graph.get_graph_matrix();
    m_stack.push(source);
    m_parent[source] = -1;
    while (!m_stack.empty()) {
        int vertex = m_stack.top();
        m_stack.pop();

        if (!m_visited.contains(vertex)) {
            m_visited.insert(vertex);
            
            for (auto &[node, val] : graph_repr) {
                int child_weight = graph_repr.at(vertex)[node];
                if (child_weight != 0) {
                    if (!m_visited.contains(node)) {
                        m_stack.push(node);
                        m_parent[node] = vertex;
                    } else if (m_parent[vertex] != node) {  // was visited and has a parent,
                        m_cycle = true;                     // but it's not the parent of the current vertex
                    }
                }
            }
        }
    }
}


void dfs::solve(const gralph::graph::WeightedMultiGraph& graph, int source = 0) {
    const std::map<int, std::vector<std::unordered_set<int>>>& graph_repr = { graph.get_graph_matrix() };
    m_stack.push(source);
    m_parent[source] = -1;
    while (!m_stack.empty()) {
        int vertex = m_stack.top();
        m_stack.pop();

        if (!m_visited.contains(vertex)) {
            m_visited.insert(vertex);
            
            for (auto &[node, val] : graph_repr) {
                int child_weights = graph_repr.at(vertex)[node].size();
                if (child_weights != 0) {
                    if (!m_visited.contains(node)) {
                        m_stack.push(node);
                        m_parent[node] = vertex;
                    } else if (m_parent[vertex] != node) {  // was visited and has a parent,
                        m_cycle = true;                     // but it's not the parent of the current vertex
                    }
                }
            }
        }
    }
}

// check if there are two disconnected graphs (disconnected vertices allowed)
bool dfs::is_disconnected(const gralph::graph::IGraph& graph) {
    int vertex_cnt {};
    for (int vertex : graph.get_all_vertices()) {
        if (graph.get_vertex_deg(vertex) != 0) {
            ++vertex_cnt;
        }
    }
    return vertex_cnt != m_visited.size();
}

}   // namespace search
}   // namespace gralph
