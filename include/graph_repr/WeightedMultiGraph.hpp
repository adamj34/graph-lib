#ifndef GRAPH_REPR_WEIGHTEDMULTIGRAPH_HPP_
#define GRAPH_REPR_WEIGHTEDMULTIGRAPH_HPP_

#include "graph_repr/IGraph.hpp"

#include <vector>
#include <tuple>
#include <map>
#include <utility>
#include <unordered_set>

namespace gralph {
namespace graph {

class WeightedMultiGraph : public IGraph {
    private:
        int m_V_num {};
        int m_E_num {};
        std::map<int, std::vector<std::unordered_set<int>>> m_graph_matrix {};

    public:
        WeightedMultiGraph(int, int);

        const std::variant<std::map<int, std::vector<std::unordered_set<int>>>,
                           std::map<int, std::vector<int>>>
        get_graph() const {
            return m_graph_matrix;
        }

        int get_edge_num() const { return m_E_num; }

        int get_vertex_num() const { return m_V_num; }

        void build_edges(const std::vector<std::tuple<int, int, int>>& coords_tuples);

        std::vector<int> get_all_vertices() const;

        int get_vertex_deg(int node) const;

        void add_vertex();

        void delete_vertex(int node);

        void add_edge(const std::tuple<int, int, int>& edge);

        void delete_edge(const std::pair<int, int>& edge);

        std::vector<std::tuple<int, int, int>> get_all_edges() const;

        std::variant<std::unordered_set<int>, int> get_edge_weight(const std::pair<int, int>& edge) const;

        void print_matrix();
};

}
}

#endif // GRAPH_REPR_WEIGHTEDMULTIGRAPH_HPP_
