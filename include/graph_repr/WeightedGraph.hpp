#ifndef WEIGHTED_GRAPH_HPP
#define WEIGHTED_GRAPH_HPP

#include <vector>
#include <tuple>
#include <map>

namespace gralph {

class WeightedGraph {
    private:
        int m_V_num {};
        int m_E_num {};
        std::map<int, std::vector<int>> m_graph_matrix {};

    public:
        WeightedGraph(int, int);

        const std::map<int, std::vector<int>>& get_graph() const { return m_graph_matrix; }

        int get_edge_num() const { return m_E_num; }

        int get_verex_num() const { return m_V_num; }

        void build_edges(const std::vector<std::tuple<int, int, int>>& coords_tuples);

        void add_vertex();

        void delete_vertex(int node);

        void print_matrix();
};

}
#endif
