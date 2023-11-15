#include "algorithms/shortest_path/dijkstra.hpp"

#include <limits>
#include <algorithm>

namespace gralph {
namespace algos {

Dijkstra::Dijkstra(const graph::WeightedGraph &graph, int source) 
    : m_source(source)
    {
        const std::map<int, std::vector<int>>& graph_repr = graph.get_graph();
        std::vector<int> source_vec = graph_repr.at(m_source);

        for (int i = 0; i < ssize(source_vec); i++) {
            int weight = source_vec[i];
            if (m_source == i) {
                m_D[i] = 0;
            } else if (weight != 0) {
                m_D[i] = weight;
            } else {
                m_D[i] = std::numeric_limits<int>::max();
            }
        }

        for (int i = 0; i < graph.get_vertex_num(); i++) {
            m_V_prime.insert(i);
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
            int min_dist = m_D[min_vertex];
            for (int vertex : m_V_prime) {
                int weight = graph_repr.at(min_vertex)[vertex];
                if (weight != 0) {
                    m_D[vertex] = std::min(m_D[vertex], min_dist + weight);
                }
            }
        }
    }

}   // namespace algos
}   // namespace gralph
