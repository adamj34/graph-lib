#ifndef ALGORITHMS_SEARCH_DFS_HPP
#define ALGORITHMS_SEARCH_DFS_HPP

#include "graph_repr/WeightedGraph.hpp"

#include <unordered_set>
#include <unordered_map>
#include <stack>

namespace gralph {
namespace search {

class dfs {
    private:
        const gralph::graph::WeightedGraph& m_graph;
        std::unordered_set<int> m_visited {};
        std::stack<int> m_stack {};
        std::unordered_map<int, int> m_parent {};
        bool m_cycle { false };

    public:
        explicit dfs(const gralph::graph::WeightedGraph& graph);

        void solve(int source);

        const std::unordered_set<int>& get_visited() const { return m_visited; };

        bool contains_cycle() { return m_cycle; };

        bool is_disconnected() { return ssize(m_visited) != m_graph.get_vertex_num(); };
};

}  // namespace search
}  // namespace gralph


#endif // ALGORITHMS_SEARCH_DFS_HPP
