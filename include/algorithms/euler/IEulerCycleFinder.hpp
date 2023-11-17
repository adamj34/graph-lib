#ifndef ALGORITHMS_EULER_IEULER_CYCLE_FINDER_HPP
#define ALGORITHMS_EULER_IEULER_CYCLE_FINDER_HPP

#include <vector>
#include <utility>

class IEulerCycleFinder {
public:
    virtual ~IEulerCycleFinder() = default;
    virtual void solve(int source = 0) = 0;
    virtual bool is_eulerian() = 0;
    virtual bool is_semi_eulerian() = 0;
    virtual int get_cost() = 0;
    virtual std::vector<std::pair<int, int>> get_eulerian_cycle() = 0;
};

#endif  // ALGORITHMS_EULER_IEULER_CYCLE_FINDER_HPP
