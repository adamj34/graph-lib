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
        const gralph::graph::WeightedGraph& m_graph;
        std::map<int, std::vector<int>> m_mst {};
        int m_cost { 0 };
        std::unordered_set<int> m_added {};

    public:
        explicit prim(const gralph::graph::WeightedGraph& graph);

        void solve(int source = 0);

        const std::map<int, std::vector<int>>& get_mst() const { return m_mst; };

        int get_cost() const { return m_cost; };
};

}
}

#endif  // ALGORITHMS_MST_PRIM_HPP_
