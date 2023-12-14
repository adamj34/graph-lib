
#include "problems/CPM.hpp"
#include "graph_repr/WeightedDirectedGraph.hpp"

#include <stdexcept>
#include <vector>
#include <iostream>
#include <algorithm>  

namespace gralph {
namespace problems {

CPM::CPM(const gralph::graph::WeightedDirectedGraph& graph, const std::vector<double>& task_weights)
    : m_graph(graph)
    , m_task_weights(task_weights)
    {}

void CPM::solve() {
    const std::map<int, std::vector<int>>& m_graph_matrix = { m_graph.get_graph_matrix() };
    const std::unordered_map<int, double> node_to_weight = { assign_weigths_to_tasks() };
    const std::vector<int> topo_order = { topo_sort() };
    for (auto el : topo_order) {
        std::cout << el << " ";
    }
} 

std::unordered_map<int, double> CPM::assign_weigths_to_tasks() {
    std::unordered_map<int, double> node_to_weight = {};
    const std::vector<int> vertex_list = { m_graph.get_all_vertices() };
    for (int i = 0; i < std::ssize(vertex_list); ++i) {
        node_to_weight.insert({vertex_list[i], m_task_weights[i]});
    }

    return node_to_weight;
}

std::vector<int> CPM::topo_sort() {
    std::vector<int> vertices = { m_graph.get_all_vertices() };
    int start_vertex = {};
    bool start_vertex_exists = false;
    for (const int node : vertices) {
        int in_deg = { m_graph.get_vertex_indeg(node) };
        if (in_deg == 0) {
            start_vertex = { node };
            start_vertex_exists = true;
            break;
        }
    }
    if (!start_vertex_exists) {
        throw std::runtime_error("No vertex with indegree equal to 0 found.");
    }

    std::vector<bool> visited(m_graph.get_all_vertices().size(), false);
    std::vector<bool> in_stack(m_graph.get_all_vertices().size(), false);
    std::vector<int> topo_order {};
    topo_sort_subroutine(start_vertex, visited, topo_order, in_stack);

    std::reverse(topo_order.begin(), topo_order.end());
    return topo_order;
}

void CPM::topo_sort_subroutine(int curr_node, std::vector<bool>& visited,
                               std::vector<int>& topo_order, std::vector<bool>& in_stack) {
    visited[curr_node] = true;
    in_stack[curr_node] = true;

    std::vector<int> curr_neighbours = { m_graph.get_graph_matrix().at(curr_node) };
    for (int to_node = 0; to_node < curr_neighbours.size(); ++to_node) {
        if (curr_neighbours[to_node] != 0) {
            if (!visited[to_node]) {
                topo_sort_subroutine(to_node, visited, topo_order, in_stack);
            } else if (in_stack[curr_node]) {   // visited and in_stack (node still being explored) = cycle
                throw std::runtime_error("Cycle detected.");
            }
        }
    }

    topo_order.push_back(curr_node);
    in_stack[curr_node] = false;
}

}
}
