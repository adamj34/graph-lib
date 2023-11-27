#ifndef PROBLEMS_TRAVELINGSALESMAN_HPP_
#define PROBLEMS_TRAVELINGSALESMAN_HPP_

#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/euler/IEulerCycleFinder.hpp"
#include "graph_repr/WeightedMultiGraph.hpp"
#include "algorithms/mst/IMst.hpp"

#include <utility>
#include <vector>

namespace gralph {
namespace problems {

class travelingSalesman {
    private:
        const gralph::graph::WeightedGraph& m_graph;
        gralph::algos::IEulerCycleFinder& m_eulerCycleFinder;
        gralph::algos::IMst& m_mstFinder;
        std::vector<std::pair<int, int>> m_solution {};
        int m_cost {};

        std::vector<int> find_odd_vertices(const std::map<int, std::vector<int>>& mst);

        std::vector<std::tuple<int, int, int>> find_odd_vertices_edges(std::vector<int>& odd_vertices);

        std::vector<std::tuple<int, int, int>> find_min_perfect_matching(std::vector<std::tuple<int, int, int>>& edges);

        std::pair<std::vector<std::pair<int, int>>, int> shortcut(const std::vector<std::pair<int, int>>& euler_tour);
    public:
        travelingSalesman(const gralph::graph::WeightedGraph& graph, 
                          gralph::algos::IEulerCycleFinder& eulerCycleFinder,
                          gralph::algos::IMst& mstFinder);

        void solve();

        int get_cost() const { return m_cost; }

        std::vector<std::pair<int, int>> get_solution() const { return m_solution; }
};

}  // namespace problems
}  // namespace gralph

#endif  // PROBLEMS_TRAVELINGSALESMAN_HPP_
