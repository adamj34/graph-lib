#include "graph_repr/IGraph.hpp"
#include "graph_repr/WeightedGraph.hpp"
#include "graph_repr/WeightedMultiGraph.hpp"
#include "algorithms/euler/fleuryCycle.hpp"
#include "algorithms/search/dfs.hpp"


namespace gralph {
namespace algos {

void fleuryCycle::solve(gralph::graph::WeightedGraph& graph, int source = 0) {
    m_source = source;

    // choose the staring point depending on the type of the graph
    int curr_node = choose_starting_point(graph);
    if (curr_node == -1) { return; }
    while (graph.get_edge_num() > 0) {
        bool valid_edge_found { false };
        std::pair<int, int> edge {};
        for (int i = 0; i < graph.get_vertex_num(); i++) {
            std::map<int, std::vector<int>> graph_matrix = graph.get_graph_matrix();
            if (graph_matrix.at(curr_node)[i] != 0) {
                edge.first = curr_node;
                edge.second = i;
                // int deleted_edge_weight = graph.get_edge_weight(edge);
                int deleted_edge_weight = graph.check_edge_weight(edge);
                graph.delete_edge(edge);

                gralph::search::dfs dfs_algo{};
                dfs_algo.solve(graph, curr_node);
                if (!dfs_algo.is_disconnected(graph)) {
                    m_eulerian_cycle.push_back(edge);
                    curr_node = i;
                    valid_edge_found = true;
                    m_cost += deleted_edge_weight;
                    break;
                } else {
                    graph.add_edge({edge.first, edge.second, deleted_edge_weight});
                }
            }
        }

        if (!valid_edge_found) {  // the graph has to be disconnnected
            m_cost += graph.check_edge_weight(edge);
            graph.delete_edge(edge);
            m_eulerian_cycle.push_back(edge);
            curr_node = edge.second;
        }
    }
}

void fleuryCycle::solve(gralph::graph::WeightedMultiGraph& graph, int source = 0) {
    m_source = source;

    // choose the staring point depending on the type of the graph
    int curr_node = choose_starting_point(graph);
    if (curr_node == -1) { return; }
    while (graph.get_edge_num() > 0) {
        bool valid_edge_found { false };
        std::pair<int, int> edge {};
        for (int i = 0; i < graph.get_vertex_num(); i++) {
            auto graph_matrix = std::get<std::map<int, std::vector<std::unordered_set<int>>>>(graph.get_graph());
            if (graph_matrix.at(curr_node)[i].size() != 0) {
                edge.first = curr_node;
                edge.second = i;
                // int deleted_edge_weight = graph.get_edge_weight(edge);
                int deleted_edge_weight = std::get<int>(graph.get_edge_weight(edge));
                graph.delete_edge(edge);

                gralph::search::dfs dfs_algo{graph};
                dfs_algo.solve(curr_node);
                if (!dfs_algo.is_disconnected()) {
                    m_eulerian_cycle.push_back(edge);
                    curr_node = i;
                    valid_edge_found = true;
                    m_cost += deleted_edge_weight;
                    break;
                } else {
                    graph.add_edge({edge.first, edge.second, deleted_edge_weight});
                }
            }
        }

        if (!valid_edge_found) {  // the graph has to be disconnnected
            m_cost += std::get<int>(graph.get_edge_weight(edge));
            graph.delete_edge(edge);
            m_eulerian_cycle.push_back(edge);
            curr_node = edge.second;
        }
    }

}


int fleuryCycle::find_starting_point(const gralph::graph::IGraph& graph) {
    return std::visit([&graph](auto&& arg) -> int {
        for (auto &[vertex, neighbours] : arg) {
            if (graph.get_vertex_deg(vertex) % 2 != 0) {
                return vertex;
            }
        }
        return 0;
    }, graph.get_graph());
}

int fleuryCycle::choose_starting_point(const gralph::graph::IGraph& graph) {
    int start_node {};
    if (!graph.is_eulerian() && !graph.is_semi_eulerian()) {
        return -1;
    } else if (graph.is_eulerian()) {
        start_node = { m_source };
    } else if (graph.is_semi_eulerian()) {
        start_node = { find_starting_point(graph) };
    }
    return start_node;
}

}  // namespace algos
}  // namespace gralph
