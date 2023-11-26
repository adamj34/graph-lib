#ifndef ALGORITHMS_SEARCH_DFS_HPP_
#define ALGORITHMS_SEARCH_DFS_HPP_

#include "graph_repr/WeightedGraph.hpp"
#include "graph_repr/WeightedMultiGraph.hpp"

#include <unordered_set>
#include <unordered_map>
#include <stack>

namespace gralph {
namespace search {

class dfs {
    private:
        std::unordered_set<int> m_visited {};
        std::stack<int> m_stack {};
        std::unordered_map<int, int> m_parent {};
        bool m_cycle { false };

    public:
        void solve(const gralph::graph::WeightedGraph&, int);

        void solve(const gralph::graph::WeightedMultiGraph&, int);

        const std::unordered_set<int>& get_visited() const { return m_visited; }

        bool contains_cycle() { return m_cycle; }

        bool is_disconnected(const gralph::graph::IGraph& graph);
};

}  // namespace search
}  // namespace gralph


#endif // ALGORITHMS_SEARCH_DFS_HPP_
