#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/chinese_postman/chinesePostman.hpp"

namespace gralph {
namespace chinese_postman {

chinesePostman::chinesePostman(const gralph::graph::WeightedGraph& graph)
    : m_graph(graph)
    {
        if (!check_eulerian()) {
            std::cout << "The graph is not eulerian!\n";
            return;
        }
        std::cout << "The graph is eulerian!\n";
    }

    
} // namespace chinese_postman
}  // namespace gralph

