#include "graph_repr/WeightedGraph.hpp"
#include "problems/chinesePostman.hpp"
#include "algorithms/euler/IEulerCycleFinder.hpp"
#include "algorithms/shortest_path/IShortestPathFinder.hpp"
#include "helpers/buildSubsets.hpp"

#include <limits>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>
#include <cmath>

namespace gralph {
namespace problems {

chinesePostman::chinesePostman(const gralph::graph::WeightedGraph& graph,
                               gralph::algos::IShortestPathFinder& pathFinder,
                               gralph::algos::IEulerCycleFinder& eulerCycleFinder)
    : m_graph(graph)
    , m_eulerCycleFinder(eulerCycleFinder)
    , m_pathFinder(pathFinder)
    {}


void chinesePostman::solve() {
    if (m_graph.is_eulerian()) {
        // euler cycle is the solution
        gralph::graph::WeightedGraph euler_graph_copy { m_graph };
        m_eulerCycleFinder.solve(euler_graph_copy, 0);
        m_solution = { m_eulerCycleFinder.get_eulerian_cycle() };
        m_cost = { m_eulerCycleFinder.get_cost() };
    } else if (m_graph.is_semi_eulerian()) {
        // use euler cycle finder to find the eulerian path
        gralph::graph::WeightedGraph euler_graph_copy { m_graph };
        m_eulerCycleFinder.solve(euler_graph_copy, 0);
        std::vector<std::pair<int, int>> euler_path { m_eulerCycleFinder.get_eulerian_cycle() };
        int euler_path_cost { m_eulerCycleFinder.get_cost() };
        int euler_path_startpoint { euler_path[0].first };
        int euler_path_endpoint { euler_path.back().second };

        // use dijkstra to find the shortest paths from the start point to the end point 
        m_pathFinder.solve(m_graph, euler_path_startpoint);
        std::vector<std::pair<int, int>> shortest_path { m_pathFinder.get_shortest_path(euler_path_endpoint) };
        int shortest_path_cost = m_pathFinder.get_shortest_path_cost(euler_path_endpoint);

        // combine the two paths
        std::reverse(shortest_path.begin(), shortest_path.end());
        euler_path.insert(euler_path.end(), shortest_path.begin(), shortest_path.end());
        m_solution = { euler_path };
        m_cost = { euler_path_cost + shortest_path_cost };
    } else {
        std::unordered_set<int> odd_vertices { get_odd_vertices() };
        std::vector<std::tuple<int, int, int>> full_graph { construct_full_graph(odd_vertices) };
        std::vector<std::tuple<int, int, int>> min_matching { find_min_perfect_matching(full_graph) };
        std::vector<std::tuple<int, int, int>> edges_to_add { find_edges_to_add(min_matching) };

        gralph::graph::WeightedGraph og_graph_copy { m_graph };
        for (auto [from_vertex, to_vertex, weight] : min_matching) {
            og_graph_copy.add_edge({ from_vertex, to_vertex, weight });
        }

        m_eulerCycleFinder.solve(og_graph_copy, 0);
        m_solution = { m_eulerCycleFinder.get_eulerian_cycle() };
        m_cost = { m_eulerCycleFinder.get_cost() };
    }
}

std::unordered_set<int> chinesePostman::get_odd_vertices() {    
    std::unordered_set<int> odd_vertices {};
    for (auto &[vertex, neighbours] : m_graph.get_graph_matrix()) {
        if (m_graph.get_vertex_deg(vertex) % 2 != 0) {
            odd_vertices.insert(vertex);
        }
    }
    return odd_vertices;
}

std::vector<std::tuple<int, int, int>> chinesePostman::construct_full_graph(std::unordered_set<int>& odd_vertices) {
    std::vector<std::tuple<int, int, int>> edges {};
    std::unordered_set<int> odd_vertices_copy = odd_vertices;
    for (int odd_vertex : odd_vertices_copy) {
        m_pathFinder.solve(m_graph, odd_vertex);
        for (int node : odd_vertices) {
            if (node != odd_vertex) {
                edges.push_back({ odd_vertex, node, m_pathFinder.get_shortest_path_cost(node) });
            }
        }

        odd_vertices.erase(odd_vertex);
    }

    return edges;
}

std::vector<std::tuple<int, int, int>> chinesePostman::find_min_perfect_matching(std::vector<std::tuple<int, int, int>>& full_graph) {
    std::vector<std::vector<std::tuple<int, int, int>>> subsets = gralph::helpers::build_subsets(full_graph);
    std::vector<std::tuple<int, int, int>> min_matching {};
    int num_of_full_graph_veritces = static_cast<int>((1 + std::sqrt(1 + 8 * ssize(full_graph))) / 2);
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

        if (is_valid_matching && vertices.size() == num_of_full_graph_veritces) {
            if (subset_cost < min_matching_cost) {
                min_matching = subset;
                min_matching_cost = subset_cost;
            }
        }
    }

    return min_matching;
}

std::vector<std::tuple<int, int, int>> chinesePostman::find_edges_to_add(std::vector<std::tuple<int, int, int>>& min_matching) {
    std::vector<std::tuple<int, int, int>> edges_to_add {};

    for (auto [from_node, to_node, w] : min_matching) {
        m_pathFinder.solve(m_graph, from_node);
        std::vector<std::pair<int, int>> shortest_path { m_pathFinder.get_shortest_path(to_node) };
        for (auto [from_vertex, to_vertex] : shortest_path) {
            edges_to_add.push_back({ from_vertex, to_vertex, m_graph.check_edge_weight({from_vertex, to_vertex}) });
        }
    }

    return edges_to_add;
}

} // namespace problems
} // namespace gralph

