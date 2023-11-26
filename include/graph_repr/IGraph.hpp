#ifndef _ALGORITHMS_GRAPHREPR_GRAPH_HPP_
#define _ALGORITHMS_GRAPHREPR_GRAPH_HPP_

#include <vector>
#include <tuple>
#include <map>
#include <utility>
#include <unordered_set>
#include <variant>

namespace gralph {
namespace graph {

using GraphMatrix = std::variant<std::map<int, std::vector<std::unordered_set<int>>>,
                                 std::map<int, std::vector<int>>>;

class IGraph {
public:
    virtual ~IGraph() = default;
    virtual const GraphMatrix get_graph() const = 0;
    virtual int get_edge_num() const = 0;
    virtual int get_vertex_num() const = 0;
    virtual void build_edges(const std::vector<std::tuple<int, int, int>>& coords_tuples) = 0;
    virtual std::vector<int> get_all_vertices() const = 0;
    virtual int get_vertex_deg(int node) const = 0;
    virtual void add_vertex() = 0;
    virtual void delete_vertex(int node) = 0;
    virtual void add_edge(const std::tuple<int, int, int>& edge) = 0;
    virtual void delete_edge(const std::pair<int, int>& edge) = 0;
    virtual std::vector<std::tuple<int, int, int>> get_all_edges() const = 0;
    virtual std::variant<std::unordered_set<int>, int> get_edge_weight(const std::pair<int, int>& edge) const = 0;
    virtual bool is_eulerian() const = 0;
    virtual bool is_semi_eulerian() const = 0;
    virtual void print_matrix() const = 0;
};

} // namespace graph
} // namespace gralph


#endif // _ALGORITHMS_GRAPHREPR_GRAPH_HPP_
