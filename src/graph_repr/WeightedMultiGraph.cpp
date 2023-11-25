#include "graph_repr/WeightedMultiGraph.hpp"

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

namespace gralph {
namespace graph {

WeightedMultiGraph::WeightedMultiGraph(int V_num, int E_num) 
    : m_V_num(V_num)
    , m_E_num(E_num)
    {
        for (int i = 0; i < m_V_num; ++i) {
            m_graph_matrix[i] = std::vector<std::unordered_set<int>>(m_V_num);
        }
    }

void WeightedMultiGraph::build_edges(const std::vector<std::tuple<int, int, int>>& coords_tuples) {
    for (const auto& [coord_0, coord_1, weight] : coords_tuples) {
        m_graph_matrix[coord_0][coord_1].insert(weight);
        m_graph_matrix[coord_1][coord_0].insert(weight);
    }
}

std::vector<int> WeightedMultiGraph::get_all_vertices() const {
    std::vector<int> vertices {};
    for (const auto& [k, v] : m_graph_matrix) {
        vertices.push_back(k);
    }
    return vertices;
}

int WeightedMultiGraph::get_vertex_deg(int node) const {
    int deg = 0;
    for (const auto& [k, v] : m_graph_matrix) {
        deg += v[node].size();
    }
    return deg;
}

void WeightedMultiGraph::add_vertex() {
    ++m_V_num;
    for (auto &[k, v] : m_graph_matrix) {
        v.push_back(std::unordered_set<int>());
    }
    m_graph_matrix[m_V_num - 1] = std::vector<std::unordered_set<int>>(m_V_num);
}

void WeightedMultiGraph::delete_vertex(int node) {
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

void WeightedMultiGraph::add_edge(const std::tuple<int, int, int>& edge) {
    const auto& [coord_0, coord_1, weight] = edge;
    m_graph_matrix[coord_0][coord_1].insert(weight);
    m_graph_matrix[coord_1][coord_0].insert(weight);
    ++m_E_num;
}

void WeightedMultiGraph::delete_edge(const std::pair<int, int>& edge) {
    const auto& [coord_0, coord_1] = edge;
    m_graph_matrix[coord_0][coord_1].clear();
    m_graph_matrix[coord_1][coord_0].clear();
    --m_E_num;
}

std::vector<std::tuple<int, int, int>> WeightedMultiGraph::get_all_edges() const {
    std::vector<std::tuple<int, int, int>> edges {};
    for (const auto &[k, v] : m_graph_matrix) {
        for (int i = 0; i < v.size(); ++i) {
            auto &weights_set = v[i];
            for (const auto &weight : weights_set) {
                edges.push_back(std::tuple(k, i, weight));
            }
        }
    }
    return edges;
}

std::variant<std::unordered_set<int>, int> WeightedMultiGraph::get_edge_weight(const std::pair<int, int>& edge) const {
    return m_graph_matrix.at(edge.first)[edge.second];
}

void WeightedMultiGraph::print_matrix() {
    for (const auto& [k, v] : m_graph_matrix) {
        std::cout << k << ": ";
        for (const auto& i : v) {
            std::cout << '(';
            for (const auto& j : i) {
                std::cout << j << ' ';
            }
            std::cout << ") ";
        }
        std::cout << '\n';
    }
}


}   // namespace graph
}   // namespace gralph
