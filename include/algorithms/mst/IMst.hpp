#ifndef ALGORITHMS_MST_IMST_HPP_
#define ALGORITHMS_MST_IMST_HPP_

#include "graph_repr/WeightedGraph.hpp"
#include "graph_repr/WeightedMultiGraph.hpp"

#include <vector>
#include <map>

namespace gralph {
namespace algos {

class IMst {
public:
    virtual ~IMst() = default;
    virtual void solve(const gralph::graph::WeightedGraph&, int) = 0;
    virtual void solve(const gralph::graph::WeightedMultiGraph&, int) = 0;
    virtual int get_cost() const = 0;
    virtual const std::map<int, std::vector<int>>& get_mst() const = 0;
};

}  // namespace algos
}  // namespace gralph

#endif // ALGORITHMS_MST_IMST_HPP_
