#ifndef ALGORITHMS_MST_KRUSKA_HPP_
#define ALGORITHMS_MST_KRUSKA_HPP_

#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/mst/IMst.hpp"
#include "data_structures/disjoinedSet.hpp"

#include <vector>
#include <tuple>

namespace gralph {
namespace algos {

class kruskal : public IMst {
    private:
        const gralph::graph::WeightedGraph& m_graph;
        std::map<int, std::vector<int>> m_mst {};
        int m_cost { 0 };

        std::vector<std::tuple<int, int, int>> sort_edges();

    public:
        explicit kruskal(const gralph::graph::WeightedGraph& graph);

        void solve(int source = 0) override;

        const std::map<int, std::vector<int>>& get_mst() const override { return m_mst; }

        int get_cost() const override { return m_cost; };
};

}  // namespace algos
}  // namespace gralph

#endif // ALGORITHMS_MST_KRUSKA_HPP_
