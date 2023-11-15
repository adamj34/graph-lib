#include "algorithms/mst/prim.hpp"
#include "graph_repr/WeightedGraph.hpp"

#include <unordered_set>
#include <map>
#include <vector>
#include <limits>
#include <utility>


namespace gralph {
namespace algos {

prim::prim(const gralph::graph::WeightedGraph& graph) 
    : m_graph(graph)
    {}


void prim::solve(int source) {
    int V_num { m_graph.get_vertex_num() };
    for (int i = 0; i < V_num; ++i) {
        m_mst[i] = std::vector<int>();
    }

    const std::map<int, std::vector<int>>& graph_repr = m_graph.get_graph();
    m_added.insert(source);
    while (ssize(m_added) < V_num) {
        int min_val = std::numeric_limits<int>::max();
        int vertex_from = -1, vertex_to = -1;
        for (int vertex : m_added) {
            for (int candidate = 0; candidate < V_num; ++candidate) {
                if (!m_added.contains(candidate)) {
                    int weight = { graph_repr.at(vertex)[candidate] };
                    if (0 < weight && weight <= min_val) {
                        min_val = { weight };
                        vertex_from = { vertex };
                        vertex_to = { candidate };
                    }
                }
            }
        }

        if (vertex_from == -1 && vertex_to == -1) {  // no m_mst in the graph
            m_cost = 0;
            for (auto& [key, value] : m_mst) {
                value.clear();
            }
            return;
        }

        m_mst[vertex_from].push_back(vertex_to);
        m_added.insert(vertex_to);
        m_cost += min_val;
    }
}

} // namespace algos
}  // namespace gralph

