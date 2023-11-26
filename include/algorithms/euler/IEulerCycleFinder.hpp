#ifndef ALGORITHMS_EULER_IEULER_CYCLE_FINDER_HPP
#define ALGORITHMS_EULER_IEULER_CYCLE_FINDER_HPP

#include <vector>
#include <utility>
#include "graph_repr/WeightedGraph.hpp"
#include "graph_repr/WeightedMultiGraph.hpp"

namespace gralph {
namespace algos {

class IEulerCycleFinder {
public:
    virtual ~IEulerCycleFinder() = default;
    virtual void solve(gralph::graph::WeightedGraph&, int) = 0;
    virtual void solve(gralph::graph::WeightedMultiGraph&, int) = 0;
    virtual int get_cost() const = 0;
    virtual std::vector<std::pair<int, int>> get_eulerian_cycle() const = 0;
};

} // namespace algos
} // namespace gralph

#endif  // ALGORITHMS_EULER_IEULER_CYCLE_FINDER_HPP
