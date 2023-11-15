#include "algorithms/search/dfs.hpp"

#include <stack>

namespace gralph {
namespace search {

dfs::dfs(const gralph::graph::WeightedGraph& graph)
    : m_graph(graph)
    {}

void dfs::solve(int source) {
    const std::map<int, std::vector<int>>& graph_repr = m_graph.get_graph();
        m_stack.push(source);
        m_parent[source] = -1;
        while (!m_stack.empty()) {
            int vertex = m_stack.top();
            m_stack.pop();

            if (!m_visited.contains(vertex)) {
                m_visited.insert(vertex);
                
                for (auto &[node, val] : graph_repr) {
                    int child_weight = graph_repr.at(vertex)[node];
                    if (child_weight != 0) {
                        if (!m_visited.contains(node)) {
                            m_stack.push(node);
                            m_parent[node] = vertex;
                        } else if (m_parent[vertex] != node) {  // was visited and has a parent, 
                            m_cycle = true;                  // but it's not the parent of the current vertex
                        }
                    }
                }
            }
        }
}

}   // namespace search
}   // namespace gralph
