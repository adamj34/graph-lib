#include "WeightedGraph.hpp"

#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

namespace gralph {

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
    for (auto& [k, v] : m_graph_matrix) {
        v.push_back(0);
    }
    m_graph_matrix[m_V_num] = std::vector<int>(m_V_num, 0);
}

void WeightedGraph::delete_vertex(int node) {
    int edge_cnt = std::count_if(m_graph_matrix[node].begin(),
                            m_graph_matrix[node].end(),
                            [](int i) { return i != 0; });
    m_E_num = m_E_num - edge_cnt;
    m_graph_matrix.erase(node);

    --m_V_num;

    for (auto& [k, vertex] : m_graph_matrix) {
        vertex.erase(vertex.begin() + node);
    }
}

void WeightedGraph::print_matrix() {
    cout << 'X' << " ";
    for (const auto& [k, v] : m_graph_matrix) {
        cout << k << " ";
    }
    cout << endl;
    for (const auto& [k, v] : m_graph_matrix) {
        cout << k << " ";
        for (int j = 0; j < m_V_num; ++j) {
            cout << m_graph_matrix[k][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

}