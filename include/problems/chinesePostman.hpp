#ifndef PROBLEMS_CHINESE_POSTMAN_HPP
#define PROBLEMS_CHINESE_POSTMAN_HPP

#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/euler/fleuryCycle.hpp"
#include "algorithms/shortest_path/dijkstra.hpp"
#include "algorithms/shortest_path/IShortestPathFinder.hpp"

#include <vector>
#include <unordered_set>

namespace gralph {
namespace problems {

class chinesePostman {
    private:
        const gralph::graph::WeightedGraph& m_graph;
        IShortestPathFinder& m_pathFinder;
        IEulerCycleFinder& m_eulerCycleFinder;
        int m_cost {};
        std::vector<std::pair<int, int>> m_solution {};

        std::unordered_set<int> get_odd_vertices();

        std::vector<std::tuple<int, int, int>> construct_full_graph(std::unordered_set<int>& odd_vertices);

        std::vector<std::tuple<int, int, int>> find_min_perfect_matching(std::vector<std::tuple<int, int, int>>& full_graph);

        std::vector<std::tuple<int, int, int>> find_edges_to_add(std::vector<std::tuple<int, int, int>>& min_matching);

    public:
        chinesePostman(const gralph::graph::WeightedGraph& graph, 
                       IShortestPathFinder& pathFinder,
                       IEulerCycleFinder& eulerCycleFinder);

        void solve();

        int get_cost() const { return m_cost; };

        std::vector<std::pair<int, int>> get_solution() { return m_solution; };

};


}  // namespace problems
}  // namespace gralph

#endif // PROBLEMS_CHINESE_POSTMAN_HPP
