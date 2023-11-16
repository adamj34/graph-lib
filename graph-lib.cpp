
#include "algorithms/search/dfs.hpp"
#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/search/bfs.hpp"
#include "helpers/buildSubsets.hpp"

#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

int main() {

    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
    };

    std::vector<std::vector<std::tuple<int, int, int>>> subsets = gralph::helpers::build_subsets(coords_tuples);
    for (auto subset : subsets) {
        for (auto edge : subset) {
            std::cout << "(" << std::get<0>(edge) << ", " << std::get<1>(edge) << ", " << std::get<2>(edge) << ") ";
        }
        std::cout << std::endl;
    }

    cout << ssize(subsets) << endl;
}
