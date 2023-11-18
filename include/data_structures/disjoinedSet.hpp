#ifndef ALGORITHMS_DATA_STRUCTURES_DISJOINEDSET_HPP_
#define ALGORITHMS_DATA_STRUCTURES_DISJOINEDSET_HPP_

#include <unordered_map>

namespace gralph {
namespace ds {

class DisjoinedSet {
    private:
        std::unordered_map<int, int> m_parents {};

    public:
        explicit DisjoinedSet(int size);

        void make_set(int node);

        int find_set(int node);

        void union_sets(int node_1, int node_2);
};

}  // namespace ds
}  // namespace gralph

#endif  // ALGORITHMS_DATA_STRUCTURES_DISJOINEDSET_HPP_
