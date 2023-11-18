#ifndef GRAPH_REPR_WEIGHTEDGRAPH_HPP_
#define GRAPH_REPR_WEIGHTEDGRAPH_HPP_

#include <vector>
#include <tuple>
#include <map>
#include <utility>

namespace gralph {
namespace graph {

class WeightedGraph {
    private:
        int m_V_num {};
        int m_E_num {};
        std::map<int, std::vector<int>> m_graph_matrix {};

    public:
        WeightedGraph(int, int);

        const std::map<int, std::vector<int>>& get_graph() const { return m_graph_matrix; }

        int get_edge_num() const { return m_E_num; }

        int get_vertex_num() const { return m_V_num; }

        void build_edges(const std::vector<std::tuple<int, int, int>>& coords_tuples);

        std::vector<int> get_all_vertices() const;

        void add_vertex();

        void delete_vertex(int node);

        int get_vertex_deg(int node) const;

        void add_edge(const std::tuple<int, int, int>& edge);

        void delete_edge(const std::pair<int, int>& edge);

        std::vector<std::tuple<int, int, int>> get_all_edges() const;

        int get_edge_weight(const std::pair<int, int>& edge) const;

        void print_matrix();
};

}
}

#endif // GRAPH_REPR_WEIGHTEDGRAPH_HPP_
