
#include <utility>
#include <vector>
#include <map>

namespace gralph {
    std::pair<std::map<int, std::vector<int>>, int> prim(const WeightedGraph& graph);
}
