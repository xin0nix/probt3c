#include "basic_lists.h"

namespace lists {
namespace basic {

int get_middle(Node *head) {
  if (!head) {
    return -1;
  }
  Node *slow = head;
  Node *fast = head;
  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow->data;
}

}  // namespace basic
}  // namespace lists