#ifndef BASIC_LISTS_HPP
#define BASIC_LISTS_HPP

#include <memory>
#include <string>
#include <vector>

namespace lists {
namespace basic {

struct Node {
  int data{0};
  Node* next{nullptr};
  Node(int d) : data(d) {}
};

template <class InputIt>
std::vector<std::unique_ptr<Node>> init(InputIt first, InputIt last) {
  auto head = std::make_unique<Node>(*first);
  ++first;
  auto* cur = head.get();
  std::vector<std::unique_ptr<Node>> nodes;
  nodes.push_back(std::move(head));
  for (; first != last; ++first) {
    auto next = std::make_unique<Node>(*first);
    cur->next = next.get();
    cur = cur->next;
    nodes.push_back(std::move(next));
  }
  return nodes;
}

int get_middle(Node* head);
int get_nth_from_end(Node* head, const int idx);

}  // namespace basic
}  // namespace lists

#endif  // BASIC_LISTS_HPP