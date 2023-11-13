#include "algorithms/search/dfs.hpp"

#include <stack>

namespace gralph {
namespace search {

gralph::search::dfs::dfs(const graph::WeightedGraph &graph, int source)
    : m_source(source)
    {
        const std::map<int, std::vector<int>>& graph_repr = graph.get_graph();
        m_stack.push(m_source);
        m_parent[m_source] = -1;
        while (!m_stack.empty()) {
            int vertex = m_stack.top();
            m_stack.pop();

            if (!m_visited.contains(vertex)) {
                m_visited.insert(vertex);
                
                for (int i = 0; i < graph.get_vertex_num(); i++) {
                    int child_weight = graph_repr.at(vertex)[i];
                    if (child_weight != 0) {
                        if (!m_visited.contains(i)) {
                            m_stack.push(i);
                            m_parent[i] = vertex;
                        } else if (m_parent[vertex] != i) {  // was visited and has a parent, 
                            m_cycle = true;                  // but it's not the parent of the current vertex
                        }
                    }
                }
            }
        }
    }

}   // namespace search
}   // namespace gralph
