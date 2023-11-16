#include "graph_repr/WeightedGraph.hpp"

#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

namespace gralph {
namespace graph {

WeightedGraph::WeightedGraph(int V_num, int E_num) 
    : m_V_num(V_num)
    , m_E_num(E_num)
    {
        for (int i = 0; i < m_V_num; ++i) {
            m_graph_matrix[i] = std::vector<int>(m_V_num, 0);
        }
    }

void WeightedGraph::build_edges(const std::vector<std::tuple<int, int, int>>& coords_tuples) {
    for (const auto& [coord_0, coord_1, weight] : coords_tuples) {
        m_graph_matrix[coord_0][coord_1] = weight;
        m_graph_matrix[coord_1][coord_0] = weight;
    }
}

void WeightedGraph::add_vertex() {
    ++m_V_num;
    for (auto &[k, v] : m_graph_matrix) {
        v.push_back(0);
    }
    m_graph_matrix[m_V_num - 1] = std::vector<int>(m_V_num, 0);
}

int WeightedGraph::get_vertex_deg(int node) const {
    return std::count_if(m_graph_matrix.at(node).begin(),
                         m_graph_matrix.at(node).end(),
                         [](int i) { return i != 0; });
}

void WeightedGraph::delete_vertex(int node) {
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

void WeightedGraph::add_edge(const std::tuple<int, int, int>& edge) {
    auto [coord_0, coord_1, weight] = edge;
    m_graph_matrix[coord_0][coord_1] = weight;
    m_graph_matrix[coord_1][coord_0] = weight;
    ++m_E_num;
}

void WeightedGraph::delete_edge(const std::pair<int, int>& edge) {
    auto [coord_0, coord_1] = edge;
    m_graph_matrix[coord_0][coord_1] = 0;
    m_graph_matrix[coord_1][coord_0] = 0;
    --m_E_num;
}

int WeightedGraph::get_edge_weight(const std::pair<int, int>& edge) const {
    return m_graph_matrix.at(edge.first)[edge.second];
}

void WeightedGraph::print_matrix() {
    std::cout << 'X' << " ";
    for (const auto& [k, v] : m_graph_matrix) {
        std::cout << k << " ";
    }
    std::cout << '\n';
    for (const auto& [k, v] : m_graph_matrix) {
        std::cout << k << " ";
        for (int j = 0; j < m_V_num; ++j) {
            std::cout << m_graph_matrix[k][j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

} // namespace graph
} // namespace gralph


