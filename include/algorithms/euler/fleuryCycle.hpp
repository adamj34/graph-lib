#ifndef ALGORITHMS_EULER_FLEURYCYCLE_HPP
#define ALGORITHMS_EULER_FLEURYCYCLE_HPP

#include "graph_repr/WeightedGraph.hpp"
#include <vector>

namespace gralph {
namespace euler {

class fleuryCycle {
    private:
        int m_source { 0 };
        gralph::graph::WeightedGraph m_graph;
        std::vector<std::pair<int, int>> m_eulerian_cycle {};
        bool m_is_eulerian {}; 
        bool m_is_semi_eulerian {};
        int m_cost { 0 };

        bool check_euler_cycle(); 

        bool check_euler_path();

        int find_starting_point();

        int choose_starting_point();
    public:
        explicit fleuryCycle(const gralph::graph::WeightedGraph& graph);

        void solve(int source = 0);

        std::vector<std::pair<int, int>> get_eulerian_cycle() { return m_eulerian_cycle; };

        bool is_eulerian() { return m_is_eulerian; };

        bool is_semi_eulerian() { return m_is_semi_eulerian; };

        int get_cost() { return m_cost; };
};

}  // namespace euler
}  // namespace gralph

#endif // ALGORITHMS_EULER_FLEURY_HPP
