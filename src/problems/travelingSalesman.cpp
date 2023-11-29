#include "problems/travelingSalesman.hpp"
#include "helpers/buildSubsets.hpp"
#include "graph_repr/WeightedMultiGraph.hpp"

#include <limits>
#include <cmath>


namespace gralph {
namespace problems {

travelingSalesman::travelingSalesman(const gralph::graph::WeightedGraph& graph, 
                                     gralph::algos::IEulerCycleFinder& eulerCycleFinder,
                                     gralph::algos::IMst& mstFinder)
                                     : m_graph(graph)
                                     , m_eulerCycleFinder(eulerCycleFinder)
                                     , m_mstFinder(mstFinder) 
                                     {}

void travelingSalesman::solve() {
    //find MST 
    m_mstFinder.solve(m_graph, 0);
    const std::map<int, std::vector<int>>& mst = m_mstFinder.get_mst();

    //find odd vertices in MST
    std::vector<int> odd_vertices_mst = find_odd_vertices(mst);

    //find edges between odd vertices
    std::vector<std::tuple<int, int, int>> odd_vertices_edges = find_odd_vertices_edges(odd_vertices_mst);

    //find min perfect matching
    std::vector<std::tuple<int, int, int>> min_matching = find_min_perfect_matching(odd_vertices_edges);

    //create union graph
    gralph::graph::WeightedMultiGraph union_graph{m_graph.get_vertex_num(), 0};
    for (auto& [vertex, adj_nodes] : mst) {
        for (auto& adj_node : adj_nodes) {
            union_graph.add_edge({vertex, adj_node, m_graph.check_edge_weight({vertex, adj_node})});
        }
    }

    for (auto& [from_vertex, to_vertex, weight] : min_matching) {
        union_graph.add_edge({from_vertex, to_vertex, weight});
    }

    //find euler cycle in the union graph
    m_eulerCycleFinder.solve(union_graph, 0);
    std::vector<std::pair<int, int>> euler_tour = { m_eulerCycleFinder.get_eulerian_cycle() };
    int euler_tour_cost = { m_eulerCycleFinder.get_cost() };

    //shortcut the euler tour
    std::vector<std::pair<int, int>> res = { shortcut(euler_tour) };
    m_solution = res;
    for (auto& [from_vertex, to_vertex] : m_solution) {
        m_cost += m_graph.check_edge_weight({from_vertex, to_vertex});
    }

}

std::vector<int> travelingSalesman::find_odd_vertices(const std::map<int, std::vector<int>>& mst) {
    //build symmetric mst adjacency list
    std::map<int, std::vector<int>> mst_copy_sym { mst };
    for (auto& [key, nodes] : mst) {
        for (auto& node : nodes) {
            mst_copy_sym[node].push_back(key);
        }
    }

    std::vector<int> odd_vertices {};
    for (auto& [key, value] : mst_copy_sym) {
        if (value.size() % 2 == 1) {
            odd_vertices.push_back(key);
        }
    }
    return odd_vertices;
}

std::vector<std::tuple<int, int, int>> travelingSalesman::find_odd_vertices_edges(std::vector<int>& odd_vertices) {
    std::vector<std::tuple<int, int, int>> odd_vertices_edges {};
    for (int odd_vertex : odd_vertices) {
        for (int node: odd_vertices) {
            if (node != odd_vertex) {
                odd_vertices_edges.push_back({ odd_vertex, node, m_graph.check_edge_weight({odd_vertex, node}) });
            }
        }
    }

    return odd_vertices_edges;
}

std::vector<std::tuple<int, int, int>> travelingSalesman::find_min_perfect_matching(std::vector<std::tuple<int, int, int>>& edges) {
    std::vector<std::vector<std::tuple<int, int, int>>> subsets = gralph::helpers::build_subsets(edges);

    std::unordered_set<int> unique_input_vertices {};
    for (auto& [from_vertex, to_vertex, weight] : edges) {
        unique_input_vertices.insert(from_vertex);
        unique_input_vertices.insert(to_vertex);
    }

    std::vector<std::tuple<int, int, int>> min_matching {};
    int min_matching_cost = std::numeric_limits<int>::max();
    for (auto& subset : subsets) {
        int subset_cost { 0 };
        std::unordered_set<int> vertices {};
        bool is_valid_matching { true };
        for (auto& edge : subset) {
            if (vertices.contains(std::get<0>(edge)) || vertices.contains(std::get<1>(edge))) {
                is_valid_matching = false;
                break;
            } else {
                vertices.insert(std::get<0>(edge));
                vertices.insert(std::get<1>(edge));
                subset_cost += std::get<2>(edge);
            }
        }

        //check if the matching is valid and if it is a perfect matching
        if (is_valid_matching && vertices.size() == unique_input_vertices.size()) {
            if (subset_cost < min_matching_cost) {
                min_matching = subset;
                min_matching_cost = subset_cost;
            }
        }
    }

    return min_matching;
}

std::vector<std::pair<int, int>> travelingSalesman::shortcut(const std::vector<std::pair<int, int>>& euler_tour) {
    std::vector<std::pair<int, int>> hamiltonian_path {};
    std::unordered_set<int> visited { euler_tour[0].first };
    int last_vertex { euler_tour[0].first };
    for (auto& [from_vertex, to_vertex] : euler_tour) {
        if (!visited.contains(to_vertex)) {
            visited.insert(to_vertex);
            hamiltonian_path.push_back({last_vertex, to_vertex});
            last_vertex = to_vertex;
        }
    }

    hamiltonian_path.push_back({last_vertex, euler_tour[0].first});
    return hamiltonian_path;
}

}  // namespace problems
}  // namespace gralph

