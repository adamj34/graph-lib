#ifndef ALGORITHMS_EULER_FLEURYCYCLE_HPP
#define ALGORITHMS_EULER_FLEURYCYCLE_HPP

#include "graph_repr/WeightedGraph.hpp"
#include <vector>

namespace gralph {
namespace euler {

class fleuryPath {
    private:
        int m_source { 0 };
        std::vector<std::pair<int, int>> m_eulerian_path {};
        int m_cost { 0 };
        gralph::graph::WeightedGraph m_graph;
        bool m_is_semi_eulerian {}; 

        bool check_euler_path(); 

        int find_starting_point();
    public:
        explicit fleuryPath(const gralph::graph::WeightedGraph& graph);

        std::vector<std::pair<int, int>> get_eulerian_path() { return m_eulerian_path; };

        bool is_semi_eulerian() { return m_is_semi_eulerian; };

        int get_cost() { return m_cost; };
};

}  // namespace euler
}  // namespace gralph

#endif // ALGORITHMS_EULER_FLEURY_HPP
