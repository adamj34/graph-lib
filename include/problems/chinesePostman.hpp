#ifndef PROBLEMS_CHINESE_POSTMAN_HPP
#define PROBLEMS_CHINESE_POSTMAN_HPP

#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/euler/fleuryCycle.hpp"
#include "algorithms/shortest_path/dijkstra.hpp"


namespace gralph {
namespace problems {

class chinesePostman {
    private:
        const gralph::graph::WeightedGraph& m_graph;
        gralph::algorithms::euler::fleuryCycle m_fleuryCycle;
        gralph::algorithms::shortest_path::dijkstra m_dijkstra;

    public:
        chinesePostman(const gralph::graph::WeightedGraph& graph, int source)
            : m_graph(graph), 
              m_fleuryCycle(graph, source), 
              m_dijkstra(graph, source) 
        {
            // Constructor implementation
        }

        // Other methods...
};


}  // namespace problems
}  // namespace gralph

#endif // PROBLEMS_CHINESE_POSTMAN_HPP
