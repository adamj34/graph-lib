#include "bfs.hpp"

#include <queue>

gralph::search::bfs::bfs(const gralph::graph::WeightedGraph& graph, int source)
    : m_source(source)
    {
        const std::map<int, std::vector<int>>& graph_repr = graph.get_graph();
        std::queue<int> queue {};
        queue.push(m_source);
        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();

            if (m_visited.find(vertex) == m_visited.end()) {
                m_visited.insert(vertex);

                for (int el : graph_repr.at(vertex)) {
                    queue.push(el);
                }
            }
        }
    }
