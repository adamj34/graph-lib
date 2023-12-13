#ifndef PROBLEMS_CPM_HPP_
#define PROBLEMS_CPM_HPP_

#include "graph_repr/WeightedDirectedGraph.hpp"

#include <vector>
#include <unordered_map>

namespace gralph {
namespace problems {

class CPM {
    private:
        const gralph::graph::WeightedDirectedGraph& m_graph;
        const std::vector<double>& m_task_weights;

        std::unordered_map<int, double> assign_weigths_to_tasks();

        std::vector<int> topo_sort();
        void topo_sort_subroutine(int curr_node, std::vector<bool>& visited, std::vector<int>& topo_order);

    public:
        CPM(const gralph::graph::WeightedDirectedGraph& graph, const std::vector<double>& task_weights);

        void solve(); 

};

}
}

#endif // PROBLEMS_CPM_HPP_
