#ifndef ALGORITHMS_SHORTEST_PATH_DIJKSTRA_HPP
#define ALGORITHMS_SHORTEST_PATH_DIJKSTRA_HPP

#include "graph_repr/WeightedGraph.hpp"

#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace gralph {
namespace algos {

class Dijkstra {
    private:
        std::unordered_map<int, int> m_D {};
        std::unordered_set<int> m_V_prime {};
        int m_source { 0 };

    public:
        explicit Dijkstra(const graph::WeightedGraph& graph, int source);

        const std::unordered_map<int, int>& get_shortest_paths() const { return m_D; };

        int get_shortest_path(int vertex) const { return m_D.at(vertex); };
};

} // namespace algos
}  // namespace gralph

#endif  // ALGORITHMS_SHORTEST_PATH_DIJKSTRA_HPP
