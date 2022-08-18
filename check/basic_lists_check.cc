#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

#include "src/basic_lists.h"

template <class RandomIt>
void rc_shuffle(RandomIt first, RandomIt last) {
  typename std::iterator_traits<RandomIt>::difference_type i, n;
  n = last - first;
  for (i = n - 1; i > 0; --i) {
    std::swap(
        first[i],
        first[*rc::gen::inRange(0, std::numeric_limits<int>::max()) % (i + 1)]);
  }
}

template <typename T>
void show(const char *msg, T val) {
  std::cout << msg << ": " << val << "\n";
}

template <class InputIt>
void show(const char *msg, InputIt first, InputIt last) {
  bool started = false;
  std::cout << msg << ": [";
  for (; first != last; ++first) {
    if (!started) {
      std::cout << *first;
      started = true;
      continue;
    }
    std::cout << ", " << *first;
  }
  std::cout << "]\n";
}

RC_GTEST_PROP(GetMiddle, ConstructiveProof, ()) {
  size_t len = *rc::gen::inRange(1UL, 20UL);
  std::vector<int> nums(len);
  std::iota(nums.begin(), nums.end(), 1);
  int expected = nums[len / 2];
  auto it = nums.begin();
  std::cout << "---------------------------\n";
  show("nums", nums.begin(), nums.end());
  auto head = std::make_unique<lists::basic::Node>(*it);
  ++it;
  auto *cur = head.get();
  std::vector<std::unique_ptr<lists::basic::Node>> nodes;
  nodes.push_back(std::move(head));
  while (it != nums.end()) {
    auto next = std::make_unique<lists::basic::Node>(*it);
    cur->next = next.get();
    cur = cur->next;
    nodes.push_back(std::move(next));
    ++it;
  }
  int actual = lists::basic::get_middle(nodes[0].get());
  show("expected", expected);
  show("actual", actual);
  RC_ASSERT(actual == expected);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
