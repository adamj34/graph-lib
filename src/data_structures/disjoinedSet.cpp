#include "data_structures/disjoinedSet.hpp"

#include <vector>

namespace gralph {
namespace ds {

DisjoinedSet::DisjoinedSet(int size)
    : m_parents(size)
    {
        for (int i = 0; i < size; i++) {
            make_set(i);
        }
    }

void DisjoinedSet::make_set(int node) {
    m_parents[node] = node;
}

int DisjoinedSet::find_set(int node) {
    if (node == m_parents[node]) {
        return node;
    }
    return find_set(m_parents[node]);
}

void DisjoinedSet::union_sets(int node_1, int node_2) {
    node_1 = find_set(node_1);  // find the root of the tree of node_1's set    
    node_2 = find_set(node_2);  // find the root of the tree of node_2's set

    if (node_1 != node_2) {
        m_parents[node_2] = node_1;
    }
}

} // namespace ds
} // namespace gralph
