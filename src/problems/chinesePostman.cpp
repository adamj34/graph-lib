#include "graph_repr/WeightedGraph.hpp"
#include "problems/chinesePostman.hpp"
#include "algorithms/euler/IEulerCycleFinder.hpp"
#include "algorithms/shortest_path/IShortestPathFinder.hpp"

namespace gralph {
namespace problems {

chinesePostman::chinesePostman(const gralph::graph::WeightedGraph& graph,
                               IShortestPathFinder& pathFinder,
                               IEulerCycleFinder& eulerCycleFinder)
    : m_graph(graph)
    , m_eulerCycleFinder(eulerCycleFinder)
    , m_pathFinder(pathFinder)
    {}


void chinesePostman::solve() {
    if (m_eulerCycleFinder.is_eulerian()) {
        // euler cycle is the solution
        m_eulerCycleFinder.solve();
        m_solution = { m_eulerCycleFinder.get_eulerian_cycle() };
        m_cost = { m_eulerCycleFinder.get_cost() };
    } else if (m_eulerCycleFinder.is_semi_eulerian()) {
        // use euler cycle finder to find the eulerian path
        m_eulerCycleFinder.solve();
        std::vector<std::pair<int, int>> euler_path { m_eulerCycleFinder.get_eulerian_cycle() };
        int euler_path_cost { m_eulerCycleFinder.get_cost() };
        int euler_path_startpoint { euler_path[0].first };
        int euler_path_endpoint { euler_path.back().second };

        // use dijkstra to find the shortest paths from the start point to the end point 
        m_pathFinder.solve(euler_path_startpoint);
        std::vector<std::pair<int, int>> shortest_path { m_pathFinder.get_shortest_path(euler_path_endpoint) };
        int shortest_path_cost { m_pathFinder.get_shortest_path_cost(euler_path_endpoint) };

        // combine the two paths
        euler_path.insert(euler_path.end(), shortest_path.begin(), shortest_path.end());
        m_solution = { euler_path };
        m_cost = { euler_path_cost + shortest_path_cost };
    } else {
        std::unordered_set<int> odd_vertices { get_odd_vertices() };

    }
}

std::unordered_set<int> chinesePostman::get_odd_vertices() {    
    std::unordered_set<int> odd_vertices {};
    for (auto &[vertex, neighbours] : m_graph.get_graph()) {
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
        m_pathFinder.solve(odd_vertex);
        for (int node : odd_vertices) {
            if (node != odd_vertex) {
                edges.push_back({ odd_vertex, node, m_pathFinder.get_shortest_path_cost(node) });
            }
        }

        odd_vertices.erase(odd_vertex);
    }

    return edges;
}

} // namespace problems
} // namespace gralph

