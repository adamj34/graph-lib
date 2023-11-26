#ifndef ALGORITHMS_SHORTEST_PATH_DIJKSTRA_HPP_
#define ALGORITHMS_SHORTEST_PATH_DIJKSTRA_HPP_

#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/shortest_path/IShortestPathFinder.hpp"

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <utility>

namespace gralph {
namespace algos {

class dijkstra : public IShortestPathFinder {
    private:
        std::unordered_map<int, int> m_D {};
        std::unordered_set<int> m_V_prime {};
        std::unordered_map<int, int> m_predecessor {};
        int m_source { 0 };

    public:
        void solve(const gralph::graph::WeightedGraph& graph, int source) override;

        const std::unordered_map<int, int>& get_shortest_path_costs() const { return m_D; }

        int get_shortest_path_cost(int vertex) const override { return m_D.at(vertex); }

        std::vector<std::pair<int, int>> get_shortest_path(int destination) const override;

        void clear() {
            m_D.clear();
            m_V_prime.clear();
            m_predecessor.clear();
        }
};

} // namespace algos
}  // namespace gralph

#endif  // ALGORITHMS_SHORTEST_PATH_DIJKSTRA_HPP
