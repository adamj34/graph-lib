#ifndef HELPERS_BUILDSUBSETS_HPP
#define HELPERS_BUILDSUBSETS_HPP

#include <vector>

namespace gralph {
namespace helpers {

template <typename T>
std::vector<std::vector<T>> build_subsets(const std::vector<T>& set) {
    std::vector<std::vector<T>> subsets;

    for (auto& elem : set) {
        std::vector<std::vector<T>> new_subsets = subsets;

        for (auto& subset : new_subsets) {
            subset.push_back(elem);
        }

        new_subsets.push_back(std::vector<T>{elem});
        subsets.insert(subsets.end(), new_subsets.begin(), new_subsets.end());
    }

    return subsets;
}

} // namespace helpers
} // namespace gralph

#endif  // HELPERS_BUILDSUBSETS_HPP
