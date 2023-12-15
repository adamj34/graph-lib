#ifndef PROBLEMS_CPM_HPP_
#define PROBLEMS_CPM_HPP_

#include "graph_repr/WeightedDirectedGraph.hpp"

#include <vector>
#include <unordered_map>

namespace gralph {
namespace problems {

struct Node;

class CPM {
    private:
        gralph::graph::WeightedDirectedGraph& m_graph;
        const std::vector<int>& m_task_weights;
        int m_dummy_vertex {};

        std::unordered_map<int, Node> assign_weigths_to_tasks();

        std::vector<int> topo_sort();
        void topo_sort_subroutine(int curr_node, std::vector<bool>& visited,
                                  std::vector<int>& topo_order, std::vector<bool>& in_stack);

        void forward_pass(std::unordered_map<int, Node>& tasks);

        void backward_pass(std::unordered_map<int, Node>& tasks);

    public:
        CPM(gralph::graph::WeightedDirectedGraph& graph, const std::vector<int>& task_weights);

        void solve(); 

};

}
}

#endif // PROBLEMS_CPM_HPP_
