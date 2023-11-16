#ifndef ALGORITHMS_SHORTEST_PATH_DIJKSTRA_HPP
#define ALGORITHMS_SHORTEST_PATH_DIJKSTRA_HPP

#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/shortest_path/IShortestPathFinder.hpp"

#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace gralph {
namespace algos {

class dijkstra : public IShortestPathFinder {
    private:
        const graph::WeightedGraph& m_graph;
        std::unordered_map<int, int> m_D {};
        std::unordered_set<int> m_V_prime {};
        std::unordered_map<int, int> m_predecessor {};
        int m_source { 0 };

    public:

        explicit dijkstra(const graph::WeightedGraph& graph);

        void solve(int source = 0) override;

        const std::unordered_map<int, int>& get_shortest_path_costs() const { return m_D; };

        int get_shortest_path_cost(int vertex) const override { return m_D.at(vertex); };

        std::vector<std::pair<int, int>> get_shortest_path(int destination) const override;
};

} // namespace algos
}  // namespace gralph

#endif  // ALGORITHMS_SHORTEST_PATH_DIJKSTRA_HPP
