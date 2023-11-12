#ifndef ALGORITHMS_MST_PRIM_HPP_
#define ALGORITHMS_MST_PRIM_HPP_

#include <utility>
#include <unordered_set>
#include <vector>
#include <map>

#include "graph_repr/WeightedGraph.hpp"

namespace gralph {
namespace algos {

class prim {
    private:
        std::map<int, std::vector<int>> mst {};
        int cost { 0 };
        std::unordered_set<int> added {};

    public:
        explicit prim(const gralph::graph::WeightedGraph& graph);

        const std::map<int, std::vector<int>>& get_mst() const { return mst; }

        int get_cost() const { return cost; }
};

}
}

#endif  // ALGORITHMS_MST_PRIM_HPP_
