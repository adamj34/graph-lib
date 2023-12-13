#include "graph_repr/WeightedDirectedGraph.hpp"

#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

namespace gralph {
namespace graph {

WeightedDirectedGraph::WeightedDirectedGraph(int V_num, int E_num) 
    : m_V_num(V_num)
    , m_E_num(E_num)
    {
        for (int i = 0; i < m_V_num; ++i) {
            m_graph_matrix[i] = std::vector<int>(m_V_num, 0);
        }
    }

void WeightedDirectedGraph::build_edges(const std::vector<std::tuple<int, int, int>>& coords_tuples) {
    for (const auto& [coord_0, coord_1, weight] : coords_tuples) {
        m_graph_matrix[coord_0][coord_1] = weight;
    }
}

std::vector<int> WeightedDirectedGraph::get_all_vertices() const {
    std::vector<int> vertices {};
    for (const auto& [k, v] : m_graph_matrix) {
        vertices.push_back(k);
    }

    return vertices;
}

int WeightedDirectedGraph::get_vertex_deg(int node) const {
    int out_deg = std::count_if(m_graph_matrix.at(node).begin(),
                         m_graph_matrix.at(node).end(),
                         [](int i) { return i != 0; });

    int in_deg = 0;
    for (const auto& [k, v] : m_graph_matrix) {
        if (v[node] != 0) {
            ++in_deg;
        }
    }

    return out_deg + in_deg;
}

void WeightedDirectedGraph::add_vertex() {
    ++m_V_num;
    for (auto &[k, v] : m_graph_matrix) {
        v.push_back(0);
    }
    m_graph_matrix[m_V_num - 1] = std::vector<int>(m_V_num, 0);
}

void WeightedDirectedGraph::delete_vertex(int node) {
    int edge_cnt = get_vertex_deg(node);
    m_E_num = m_E_num - edge_cnt;
    // get the true position of the node in the matrix
    int node_position = std::distance(m_graph_matrix.begin(), m_graph_matrix.find(node));

    m_graph_matrix.erase(node);
    --m_V_num;

    for (auto &[k, vertex] : m_graph_matrix) {
        vertex.erase(vertex.begin() + node_position);
    }
}

void WeightedDirectedGraph::add_edge(const std::tuple<int, int, int>& edge) {
    auto [coord_0, coord_1, weight] = edge;
    m_graph_matrix[coord_0][coord_1] = weight;
    ++m_E_num;
}

void WeightedDirectedGraph::delete_edge(const std::pair<int, int>& edge) {
    auto [coord_0, coord_1] = edge;
    m_graph_matrix[coord_0][coord_1] = 0;
    --m_E_num;
}

int WeightedDirectedGraph::check_edge_weight(const std::pair<int, int>& edge) const {
    auto [coord_0, coord_1] = edge;
    return m_graph_matrix.at(coord_0)[coord_1];
}

std::vector<std::tuple<int, int, int>> WeightedDirectedGraph::get_all_edges() const {
    std::vector<std::tuple<int, int, int>> edges {};
    for (const auto& [k, v] : m_graph_matrix) {
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] != 0) {
                edges.push_back({k, i, v[i]});
            }
        }
    }

    return edges;
}

std::variant<std::unordered_set<int>, int> WeightedDirectedGraph::get_edge_weight(const std::pair<int, int>& edge) const {
    auto [coord_0, coord_1] = edge;
    return m_graph_matrix.at(coord_0)[coord_1];
}

bool WeightedDirectedGraph::is_eulerian() const {
    for (const auto& [k, v] : m_graph_matrix) {
        if (get_vertex_deg(k) % 2 != 0) {
            return false;
        }
    }

    return true;
}

bool WeightedDirectedGraph::is_semi_eulerian() const {
    int odd_deg_cnt = 0;
    for (const auto& [k, v] : m_graph_matrix) {
        if (get_vertex_deg(k) % 2 != 0) {
            ++odd_deg_cnt;
        }
    }

    return (odd_deg_cnt == 2) || (odd_deg_cnt == 0);
}

void WeightedDirectedGraph::print_matrix() const {
    std::cout << 'X' << " ";
    for (const auto& [k, v] : m_graph_matrix) {
        std::cout << k << " ";
    }
    std::cout << '\n';

    for (const auto& [k, v] : m_graph_matrix) {
        std::cout << k << " ";
        for (const auto& i : v) {
            std::cout << i << " ";
        }
        std::cout << '\n';
    }
}

int WeightedDirectedGraph::get_vertex_indeg(int node) {
    int in_degree {};
    for (const auto &[v, k] : m_graph_matrix) {
        if (k[node] != 0) {
            ++in_degree;
        }
    }
    return in_degree;
}

} // namespace graph
} // namespace gralph
