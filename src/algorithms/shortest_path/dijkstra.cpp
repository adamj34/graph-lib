#include "algorithms/shortest_path/dijkstra.hpp"

#include <limits>
#include <algorithm>

namespace gralph {
namespace algos {

dijkstra::dijkstra(const graph::WeightedGraph& graph) 
    : m_graph(graph)
    {}


void dijkstra::solve(int source) {
    m_source = source;
    const std::map<int, std::vector<int>>& graph_repr = m_graph.get_graph();
    std::vector<int> source_vec = graph_repr.at(m_source);

    for (int i = 0; i < ssize(source_vec); i++) {
        int weight = source_vec[i];
        if (m_source == i) {
            m_D[i] = 0;
        } else if (weight != 0) {
            m_D[i] = weight;
            m_predecessor[i] = m_source;
        } else {
            m_D[i] = std::numeric_limits<int>::max();
        }
    }

    for (auto &[node, neighbours] : graph_repr) {
        m_V_prime.insert(node);
    }
    m_V_prime.erase(m_source);

    while (!m_V_prime.empty()) {
        int min_distance = { std::numeric_limits<int>::max() };
        int min_vertex {};
        for (int el : m_V_prime) {
            if (m_D[el] < min_distance) {
                min_distance = m_D[el];
                min_vertex = el;
            }
        }

        m_V_prime.erase(min_vertex);
        for (int vertex : m_V_prime) {
            int weight = graph_repr.at(min_vertex)[vertex];
            if (weight != 0) {
                int new_distance = min_distance + weight;
                if (new_distance < m_D[vertex]) {
                    m_D[vertex] = new_distance;
                    m_predecessor[vertex] = min_vertex;
                }
            }
        }
    }
}


std::vector<int> dijkstra::get_shortest_path(int destination) {
    std::vector<int> path {};
    int current = destination;

    // Start from the destination and go backwards
    while (current != m_source) {
        path.push_back(current);
        current = m_predecessor.at(current);  // Follow the predecessor
    }
    path.push_back(m_source);

    // Reverse the path to get it from source to destination
    std::reverse(path.begin(), path.end());

    return path;
}

}   // namespace algos
}   // namespace gralph
