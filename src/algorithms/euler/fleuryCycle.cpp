#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/euler/fleuryCycle.hpp"
#include "algorithms/search/dfs.hpp"


namespace gralph {
namespace euler {

gralph::euler::fleuryCycle::fleuryCycle(const gralph::graph::WeightedGraph& graph, int source) 
    : m_source(source)
    , m_graph(graph)
    , m_is_eulerian(check_euler_cycle())
    {
        if (!is_eulerian()) { return; };

        int curr_node = m_source;
        while (m_graph.get_edge_num() > 0) {

            bool valid_edge_found { false };
            std::pair<int, int> edge {};
            for (int i = 0; i < m_graph.get_vertex_num(); i++) {
                if (m_graph.get_graph().at(curr_node)[i] != 0) {
                    edge.first = curr_node; edge.second = i;
                    int deleted_edge_weight = m_graph.get_edge_weight(edge);
                    m_graph.delete_edge(edge);
                    gralph::search::dfs dfs_algo{m_graph, curr_node}; 
                    if (!dfs_algo.is_disconnected()) {
                        m_eulerian_cycle.push_back(edge);
                        curr_node = i;
                        valid_edge_found = true;
                        m_cost += deleted_edge_weight;
                        break;
                    } else {
                        m_graph.add_edge({edge.first, edge.second, deleted_edge_weight});
                    }
                }
            }

            if (!valid_edge_found) {  // the graph has to be disconnnected
                m_cost += m_graph.get_edge_weight(edge);
                m_graph.delete_edge(edge);
                m_eulerian_cycle.push_back(edge);
                curr_node = edge.second;
            }
        }
    }


bool gralph::euler::fleuryCycle::check_euler_cycle() {
    for (auto &[vertex, neighbours] : m_graph.get_graph()) {
        if (m_graph.get_vertex_deg(vertex) % 2 != 0) {
            return false;
        }
    }
    return true;
}

}  // namespace euler
}  // namespace gralph
