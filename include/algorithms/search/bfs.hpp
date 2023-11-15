#ifndef ALGORITHMS_SEARCH_BFS_HPP
#define ALGORITHMS_SEARCH_BFS_HPP

#include "graph_repr/WeightedGraph.hpp"

#include <unordered_set>
#include <queue>

namespace gralph {
namespace search {

class bfs {
    private:
        const gralph::graph::WeightedGraph& m_graph;
        std::unordered_set<int> m_visited {};
        std::queue<int> m_queue {};

    public:
        explicit bfs(const gralph::graph::WeightedGraph& graph);

        void solve(int source = 0);

        const std::unordered_set<int>& get_visited() const { return m_visited; };
};

}  // namespace search
}  // namespace gralph

#endif // ALGORITHMS_SEARCH_BFS_HPP
