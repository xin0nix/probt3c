#ifndef BASIC_GRAPHS_HPP
#define BASIC_GRAPHS_HPP

#include <vector>

namespace graphs {
namespace basic {
template <typename T>
using Graph = std::vector<std::vector<T>>;
bool is_cyclic(const Graph<int> &G);
}  // namespace basic
}  // namespace graphs

#endif  // BASIC_GRAPHS_HPP
