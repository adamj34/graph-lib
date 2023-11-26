#ifndef ALGORITHMS_EULER_FLEURYCYCLE_HPP_
#define ALGORITHMS_EULER_FLEURYCYCLE_HPP_

#include "algorithms/euler/IEulerCycleFinder.hpp"
#include "graph_repr/IGraph.hpp"

#include <utility>
#include <vector>

namespace gralph {
namespace algos {

class fleuryCycle : public IEulerCycleFinder {
    private:
        int m_source { 0 };
        std::vector<std::pair<int, int>> m_eulerian_cycle {};
        int m_cost { 0 };

        int find_starting_point(const gralph::graph::IGraph&);

        int choose_starting_point(const gralph::graph::IGraph&);

    public:
        void solve(gralph::graph::WeightedGraph&, int) override;

        void solve(gralph::graph::WeightedMultiGraph&, int) override;

        std::vector<std::pair<int, int>> get_eulerian_cycle() const override { return m_eulerian_cycle; };

        int get_cost() const override { return m_cost; };
};

}  // namespace algos
}  // namespace gralph

#endif // ALGORITHMS_EULER_FLEURYCYCLE_HPP_
