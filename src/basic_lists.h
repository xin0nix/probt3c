#ifndef BASIC_LISTS_HPP
#define BASIC_LISTS_HPP

#include <string>

namespace lists {
namespace basic {

struct Node {
  int data{0};
  Node* next{nullptr};
  Node(int d) : data(d) {}
};

int get_middle(Node* head);

}  // namespace basic
}  // namespace lists

#endif  // BASIC_LISTS_HPP