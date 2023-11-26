#ifndef ALGORITHMS_MST_KRUSKA_HPP_
#define ALGORITHMS_MST_KRUSKA_HPP_

#include "graph_repr/WeightedGraph.hpp"
#include "graph_repr/WeightedMultiGraph.hpp"
#include "algorithms/mst/IMst.hpp"
#include "data_structures/disjoinedSet.hpp"

#include <vector>
#include <tuple>

namespace gralph {
namespace algos {

class kruskal : public IMst {
    private:
        std::map<int, std::vector<int>> m_mst {};
        int m_cost { 0 };

        std::vector<std::tuple<int, int, int>> sort_edges(const gralph::graph::IGraph& graph);

    public:
        void solve(const gralph::graph::WeightedGraph&, int) override;

        void solve(const gralph::graph::WeightedMultiGraph&, int) override;

        const std::map<int, std::vector<int>>& get_mst() const override { return m_mst; }

        int get_cost() const override { return m_cost; };
};

}  // namespace algos
}  // namespace gralph

#endif // ALGORITHMS_MST_KRUSKA_HPP_
