#include "basic_graphs.h"

using namespace graphs::basic;

bool is_cyclic(const Graph<int> &G) {
  struct Node {
    int val;
    size_t parent;
    size_t size;
  };
  // given the root in [0, dset.size), dset[root].parent == root
  std::vector<Node> dset;
  dset.reserve(G.size());
  auto make = [&](int val) -> size_t /* root index */ {
    const size_t new_idx = dset.size();
    dset.push_back(Node{
        .val = val,
        .parent = new_idx,
        .size = 1,
    });
    return new_idx;
  };
  auto find = [&](size_t k) -> size_t /* root index */ {
    const size_t root = k;
    while (dset[root].parent != root) {
      const_cast<size_t>(root) = dset[root].parent;
    }
    size_t cur = k;
    while (dset[cur].parent != root) {
      size_t tmp = dset[cur].parent;
      dset[cur].parent = root;
      cur = tmp;
    }
    return root;
  };
  auto merge = [&](size_t left, size_t right) -> size_t /* root index */ {
    // replase left and right with their roots
    left = find(left);
    right = find(right);

    // already in the same tree - skip
    if (left == right) return right;

    // left-side tree should be less or equal in size to the right one
    if (dset[left].size > dset[right].size) {
      std::swap(left, right);
    }

    // merge smaller (on the left) to larger (on the right)
    dset[left].parent = right;
    dset[right].size += dset[left].size;

    // right is the new root now
    return right;
  };
}
