#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

#include "src/basic_strings.h"

using namespace strings::basic;

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

RC_GTEST_PROP(RepeatedString, BruteForceCheck, ()) {
  const auto pattern_len = *rc::gen::inRange(1L, 5L);
  const auto letter_gen = rc::gen::element('a', 'b', 'c');
  std::string pattern;
  for (int i = 0; i < pattern_len; ++i) {
    pattern.push_back(*letter_gen);
  }
  const auto full_repeat = *rc::gen::inRange(1L, 3L);
  long cnt_a{0};
  for (long f = 0; f < full_repeat; ++f) {
    for (long p = 0; p < pattern_len; ++p) {
      if (pattern[p] == 'a') {
        ++cnt_a;
      }
      long pos = f * pattern_len + p + 1;
      long r = repeated_string(pattern, pos);
      RC_ASSERT(cnt_a == r);
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
