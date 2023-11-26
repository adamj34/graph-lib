#ifndef ALGORITHMS_MST_PRIM_HPP_
#define ALGORITHMS_MST_PRIM_HPP_

#include <utility>
#include <unordered_set>
#include <vector>
#include <map>

#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/mst/IMst.hpp"

namespace gralph {
namespace algos {

class prim : public IMst {
    private:
        std::map<int, std::vector<int>> m_mst {};
        int m_cost { 0 };
        std::unordered_set<int> m_added {};

    public:
        void solve(const gralph::graph::WeightedGraph&, int) override;

        void solve(const gralph::graph::WeightedMultiGraph&, int) override;

        const std::map<int, std::vector<int>>& get_mst() const override { return m_mst; }

        int get_cost() const override { return m_cost; }
};

}
}

#endif  // ALGORITHMS_MST_PRIM_HPP_
