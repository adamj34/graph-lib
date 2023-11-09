#include "WeightedGraph.hpp"
#include "prim.hpp"

#include <unordered_set>
#include <map>
#include <vector>
#include <limits>
#include <utility>


namespace gralph {

std::pair<std::map<int, std::vector<int>>, int> prim(const WeightedGraph& graph) {
    int cost {};
    std::unordered_set<int> added {};
    std::map<int, std::vector<int>> mst {};
    std::map<int, std::vector<int>> graph_repr = { graph.get_graph() };
    int V_num { graph.get_verex_num() };
    for (int i = 0; i < V_num; ++i) {
        mst[i] = std::vector<int>();
    }

    added.insert(0);
    while (ssize(added) < V_num) {
        int min_val = std::numeric_limits<int>::max();
        int vertex_from = -1, vertex_to = -1;
        for (int vertex : added) {
            for (int candidate = 0; candidate < V_num; ++candidate) {
                if (!added.contains(candidate)) {
                    int weight = { graph_repr[vertex][candidate] };
                    if (0 < weight && weight <= min_val) {
                        min_val = { weight };
                        vertex_from = { vertex };
                        vertex_to = { candidate };
                    }
                }
            }
        }
        mst[vertex_from].push_back(vertex_to);
        added.insert(vertex_to);
        cost += min_val;
    }
    return {mst, cost};
}

}
