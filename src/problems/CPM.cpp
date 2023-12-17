
#include "problems/CPM.hpp"
#include "graph_repr/WeightedDirectedGraph.hpp"

#include <stdexcept>
#include <vector>
#include <iostream>
#include <algorithm>  
#include <limits>
#include <queue>
#include <fstream>

namespace gralph {
namespace problems {

struct Node {
    int es {}, ef {}, ls {}, lf {};
    int slack {};
    int weight {0};
    Node(int w) : weight(w) {}
};


CPM::CPM(gralph::graph::WeightedDirectedGraph& graph, const std::vector<int>& task_weights)
    : m_graph(graph)
    , m_task_weights(task_weights)
    , m_dummy_vertex(graph.get_vertex_num())
    {
        // add dummy vertex to the graph
        m_graph.add_vertex();
    }

void CPM::solve() {
    const std::map<int, std::vector<int>>& graph_matrix = { m_graph.get_graph_matrix() };
    std::unordered_map<int, Node> nodes = { assign_weigths_to_tasks() };
    const std::vector<int> topo_order = { topo_sort() };
    std::cout << "Topo order\n";
    for(int el : topo_order) {
        std::cout << el << ' ';
    }

    // forward pass - set es and ef
    for (const int topo_vertex : topo_order) {
        std::vector<int> neighbors = graph_matrix.at(topo_vertex);
        for (int i = 0; i < neighbors.size(); ++i) {
            if (neighbors[i] != 0 && i != topo_vertex) {
                Node& next_node = nodes.at(i); 
                if (next_node.es < nodes.at(topo_vertex).ef) {
                    next_node.es = nodes.at(topo_vertex).ef;
                }
                next_node.ef = next_node.es + next_node.weight;
            }
        }
    }

    // backward_pass - set ls and lf
    std::vector<int> reversed_topo_order(topo_order.size()); 
    std::reverse_copy(std::begin(topo_order), std::end(topo_order), std::begin(reversed_topo_order));
    Node& finish_node = nodes.at(reversed_topo_order[0]);
    finish_node.lf = finish_node.ef;
    finish_node.ls = finish_node.lf - finish_node.weight;
    for (int topo_vertex : reversed_topo_order) {
        for (const auto& [node, neighbors] : graph_matrix) {
            if (neighbors[topo_vertex] != 0 && node != topo_vertex) {
                Node& next_node = nodes.at(node);
                if ((next_node.lf > nodes.at(topo_vertex).ls) || next_node.lf == 0) {
                    next_node.lf = nodes.at(topo_vertex).ls;
                }
                next_node.ls = next_node.lf - next_node.weight;
            }
        }
    }

    // calculate slack
    for (auto& [vertex, node] : nodes) {
        if (node.ls - node.es != node.lf - node.ef) {
            throw std::runtime_error("Slack calculation is wrong");
        }
        node.slack = node.ls - node.es;
    }
        
    // calculate the critical path using bfs
    std::vector<int> m_critical_path {};
    std::queue<int> q {};
    q.push(m_dummy_vertex);
    while (!q.empty()) {
        int curr_node = q.front();
        q.pop();
        const auto& neighbors = graph_matrix.at(curr_node);
        for (int node = 0; node < neighbors.size(); ++node) {
            if (neighbors[node] != 0 && node != curr_node) {
                const Node& next_node = nodes.at(node);
                if (next_node.slack == 0) {
                    m_critical_path.push_back(node);
                    q.push(node);
                }
            }
        }
    }

    std::ofstream file("./src/problems/graph.txt");
    for (const auto& pair : graph_matrix) {
        int node = pair.first;
        const std::vector<int>& neighbors = pair.second;
        for (int i = 0; i < neighbors.size(); ++i) {
            if (neighbors[i] != 0) {
                file << node << " " << i << "\n";
            }
        }
    }
    file.close();

    std::ofstream file2("./src/problems/nodes.txt");
    for (const auto& pair : nodes) {
        int key = pair.first;
        const Node& node = pair.second;
        file2 << key << " " << node.es << " " << node.ef << " " << node.ls << " " << node.lf << " " << node.weight << "\n";
    }
    file2.close();
} 

std::unordered_map<int, Node> CPM::assign_weigths_to_tasks() {
    const std::vector<int> vertex_list = { m_graph.get_all_vertices() };
    if (m_task_weights.size() != vertex_list.size()-1) {
        throw std::invalid_argument("The number of weights doesn't match the number of tasks");
    } 

    std::unordered_map<int, Node> node_to_weight = {};
    for (int i = 0; i < std::ssize(vertex_list); ++i) {
        // initialize dummy vertex weight
        if (i == std::ssize(vertex_list)-1) {
            node_to_weight.emplace(vertex_list[i], Node{0});
        }
        node_to_weight.emplace(vertex_list[i], Node{m_task_weights[i]});
    }
    return node_to_weight;
}

std::vector<int> CPM::topo_sort() {
    // find vertices with indegree == 0
    std::vector<int> vertices = { m_graph.get_all_vertices() };
    std::vector<int> start_vertices {};
    for (const int vertex : vertices) {
        int in_deg = { m_graph.get_vertex_indeg(vertex) };
        if (in_deg == 0 && vertex != m_dummy_vertex) {
            start_vertices.push_back(vertex);
        }
    }
    if (start_vertices.size() == 0) {
        throw std::runtime_error("No vertex with indegree equal to 0 found.");
    }

    // link dummy vertex with valid start vertices 
    for (const int valid_start_node : start_vertices) {
        m_graph.get_graph_matrix().at(m_dummy_vertex)[valid_start_node] = 1; 
    }
    m_graph.print_matrix();

    std::vector<bool> visited(m_graph.get_all_vertices().size(), false);
    std::vector<bool> in_stack(m_graph.get_all_vertices().size(), false);
    std::vector<int> topo_order {};
    topo_sort_subroutine(m_dummy_vertex, visited, topo_order, in_stack);

    std::reverse(topo_order.begin(), topo_order.end());
    return topo_order;
}

void CPM::topo_sort_subroutine(int curr_node, std::vector<bool>& visited,
                               std::vector<int>& topo_order, std::vector<bool>& in_stack) {
    visited[curr_node] = true;
    in_stack[curr_node] = true;

    const std::vector<int> curr_neighbours { m_graph.get_graph_matrix().at(curr_node) };
    for (int to_node = 0; to_node < curr_neighbours.size(); ++to_node) {
        if (curr_neighbours[to_node] != 0) {
            if (!visited[to_node]) {
                topo_sort_subroutine(to_node, visited, topo_order, in_stack);
            } else if (in_stack[to_node]) {   // visited and in_stack (node still being explored) = cycle
                throw std::runtime_error("Cycle detected.");
            }
        }
    }

    topo_order.push_back(curr_node);
    in_stack[curr_node] = false;
}

}
}
