#include "algorithms/search/bfs.hpp"

#include <queue>
#include <map>
#include <vector>

namespace gralph {
namespace search {

bfs::bfs(const gralph::graph::WeightedGraph& graph, int source)
    : m_source(source)
    , m_vertices_num(graph.get_vertex_num())
    {
        const std::map<int, std::vector<int>>& graph_repr = graph.get_graph();
        m_queue.push(m_source);
        while (!m_queue.empty()) {
            int vertex = m_queue.front();
            m_queue.pop();

            if (!m_visited.contains(vertex)) {
                m_visited.insert(vertex);

                for (auto &[node, val] : graph_repr) {
                    if (!m_visited.contains(node)) {
                        int child_weight = graph_repr.at(vertex)[node];
                        if (child_weight != 0) {
                           m_queue.push(node);
                        }
                    }
                }
            }
        }
    }

}   // namespace search
}   // namespace gralph
