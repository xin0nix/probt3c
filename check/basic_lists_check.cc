#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

#include "src/basic_lists.h"

using namespace lists::basic;

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
  auto nodes = init(nums.begin(), nums.end());
  int actual = get_middle(nodes[0].get());
  RC_ASSERT(actual == expected);
}

RC_GTEST_PROP(GetNthFromEnd, ConstructiveProof, ()) {
  size_t len = *rc::gen::inRange(1UL, 20UL);
  size_t nth = *rc::gen::inRange(1UL, len);
  std::vector<int> nums(len);
  std::iota(nums.begin(), nums.end(), 1);
  int expected = -1;
  if (nth <= len) {
    expected = nums[nth - 1];
  }
  auto nodes = init(nums.rbegin(), nums.rend());
  int actual = get_nth_from_end(nodes[0].get(), nth);
  RC_ASSERT(actual == expected);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
