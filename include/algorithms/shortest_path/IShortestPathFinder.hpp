#ifndef ALGORITHMS_SHORTEST_PATH_ISHORTEST_PATH_FINDER_HPP
#define ALGORITHMS_SHORTEST_PATH_ISHORTEST_PATH_FINDER_HPP

#include <vector>

class IShortestPathFinder {
public:
    virtual ~IShortestPathFinder() = default;
    virtual int get_shortest_path_cost(int source = 0) const = 0;
    virtual std::vector<std::pair<int, int>> get_shortest_path(int) const = 0;
    virtual void solve(int) = 0;
};


#endif // ALGORITHMS_SHORTEST_PATH_ISHORTEST_PATH_FINDER_HPP
