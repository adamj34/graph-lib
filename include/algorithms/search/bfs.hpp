#ifndef ALGORITHMS_SEARCH_BFS_HPP
#define ALGORITHMS_SEARCH_BFS_HPP

#include "graph_repr/WeightedGraph.hpp"

#include <unordered_set>

namespace gralph {
namespace search {

class bfs {
    private:
        int m_source { 0 };
        std::unordered_set<int> m_visited {};

    public:
        bfs(const gralph::graph::WeightedGraph& graph, int source);

        const std::unordered_set<int>& get_visited() const { return m_visited; };
};

}  // namespace search
}  // namespace gralph

#endif // ALGORITHMS_SEARCH_BFS_HPP
