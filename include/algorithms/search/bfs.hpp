#ifndef ALGORITHMS_SEARCH_BFS_HPP
#define ALGORITHMS_SEARCH_BFS_HPP

#include "graph_repr/WeightedGraph.hpp"

#include <unordered_set>
#include <queue>

namespace gralph {
namespace search {

class bfs {
    private:
        int m_source { 0 };
        int m_vertices_num { 0 };
        std::unordered_set<int> m_visited {};
        std::queue<int> m_queue {};

    public:
        bfs(const gralph::graph::WeightedGraph& graph, int source);

        const std::unordered_set<int>& get_visited() const { return m_visited; };
};

}  // namespace search
}  // namespace gralph

#endif // ALGORITHMS_SEARCH_BFS_HPP
