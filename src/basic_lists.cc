#include "basic_lists.h"

namespace lists {
namespace basic {

int get_middle(Node *head) {
  if (!head) {
    return -1;
  }
  Node *slow = head;
  Node *fast = head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow->data;
}

int get_nth_from_end(Node *head, const int index) {
  Node *back = head;
  Node *front = head;
  for (int count = 1; back && count < index; ++count) {
    back = back->next;
  }
  if (!back) {
    return -1;
  }
  while (back->next) {
    back = back->next;
    front = front->next;
  }
  return front->data;
}

}  // namespace basic
}  // namespace lists