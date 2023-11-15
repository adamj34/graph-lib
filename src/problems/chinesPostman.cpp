#include "graph_repr/WeightedGraph.hpp"
#include "problems/chinesePostman.hpp"

namespace gralph {
namespace problems {

problems::chinesePostman(const gralph::graph::WeightedGraph& graph)
    : m_graph(graph)
    {
        if (!check_eulerian()) {
            std::cout << "The graph is not eulerian!\n";
            return;
        }
        std::cout << "The graph is eulerian!\n";
    }

    
} // namespace problems
}  // namespace gralph

