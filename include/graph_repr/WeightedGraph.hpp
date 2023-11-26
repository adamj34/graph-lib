#ifndef GRAPH_REPR_WEIGHTEDGRAPH_HPP_
#define GRAPH_REPR_WEIGHTEDGRAPH_HPP_

#include "graph_repr/IGraph.hpp"

#include <vector>
#include <tuple>
#include <map>
#include <utility>

namespace gralph {
namespace graph {

class WeightedGraph : public IGraph {
    private:
        int m_V_num {};
        int m_E_num {};
        std::map<int, std::vector<int>> m_graph_matrix {};

    public:
        WeightedGraph(int, int);

        const GraphMatrix get_graph() const override {
            return m_graph_matrix;
        }

        const std::map<int, std::vector<int>>& get_graph_matrix() const {
            return m_graph_matrix;
        }

        int get_edge_num() const override { return m_E_num; }

        int get_vertex_num() const override { return m_V_num; }

        void build_edges(const std::vector<std::tuple<int, int, int>>& coords_tuples) override;

        std::vector<int> get_all_vertices() const override;

        void add_vertex() override;

        void delete_vertex(int node) override;

        int get_vertex_deg(int node) const override;

        void add_edge(const std::tuple<int, int, int>& edge) override;

        void delete_edge(const std::pair<int, int>& edge) override;

        std::vector<std::tuple<int, int, int>> get_all_edges() const override;

        std::variant<std::unordered_set<int>, int> get_edge_weight(const std::pair<int, int>& edge) const override;

        int check_edge_weight(const std::pair<int, int>& edge) const;

        bool is_eulerian() const override;

        bool is_semi_eulerian() const override;

        void print_matrix() const override;
};

}
}

#endif // GRAPH_REPR_WEIGHTEDGRAPH_HPP_
