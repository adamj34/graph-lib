#ifndef ALGORITHMS_SHORTEST_PATH_ISHORTEST_PATH_FINDER_HPP_
#define ALGORITHMS_SHORTEST_PATH_ISHORTEST_PATH_FINDER_HPP_

#include <vector>
#include <utility>

namespace gralph {
namespace algos {

class IShortestPathFinder {
public:
    virtual ~IShortestPathFinder() = default;
    virtual void solve(const gralph::graph::WeightedGraph& graph, int) = 0;
    virtual int get_shortest_path_cost(int) const = 0;
    virtual std::vector<std::pair<int, int>> get_shortest_path(int) const = 0;
};

} // namespace algos
} // namespace gralph

#endif // ALGORITHMS_SHORTEST_PATH_ISHORTEST_PATH_FINDER_HPP_
