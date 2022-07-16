#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "src/basic_strings.h"
#include "src/basic_vectors.h"

// class LongestTrueSeq : public ::testing::Test {};

RC_GTEST_PROP(LongestTrueSeq, ReverseCheck,
              (const std::vector<bool> &original)) {
  {  // reverse check
    int original_result = vectors::basic::longest_true_seq(original);
    std::vector<bool> reversed(original.rbegin(), original.rend());
    int reversed_result = vectors::basic::longest_true_seq(reversed);
    RC_ASSERT(original_result == reversed_result);
  }
}

RC_GTEST_PROP(CountValleys, ReverseCheck, (const std::vector<bool> &xs)) {
  {  // reverse check
    // xs - original
    // ys - original + reversed and negated (xs ++ ~sx)
    // zs - double ys (ys ++ ys)
    std::vector<bool> ys(xs);
    std::transform(xs.rbegin(), xs.rend(), std::back_inserter(ys),
                   [](bool x) -> bool { return !x; });
    int r1 = vectors::basic::count_valleys(ys);
    std::vector<bool> zs(ys);
    std::copy(ys.begin(), ys.end(), std::back_inserter(zs));
    int r2 = vectors::basic::count_valleys(zs);
    RC_ASSERT(ys.size() == xs.size() * 2);
    RC_ASSERT(zs.size() == ys.size() * 2);
    RC_ASSERT(r1 * 2 == r2);
  }
}

RC_GTEST_PROP(CountEvenDigitNumbers, OddDigitegNumberInsertionCheck,
              (const std::vector<int> &xs)) {
  // odd digited number doesn't effect the result
  const int r1 = vectors::basic::count_even_digit_nums(xs);
  std::vector<int> xxs(xs);
  xxs.push_back(111);
  int r2 = vectors::basic::count_even_digit_nums(xxs);
  RC_ASSERT(r1 == r2);
}

RC_GTEST_PROP(CountEvenDigitNumbers, EvenDigitegNumberInsertionCheck,
              (const std::vector<int> &xs)) {
  // even digited number increments the result
  const int r1 = vectors::basic::count_even_digit_nums(xs);
  std::vector<int> xxs(xs);
  xxs.push_back(11);
  int r2 = vectors::basic::count_even_digit_nums(xxs);
  RC_ASSERT(r1 + 1 == r2);
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
      long r = strings::basic::repeated_string(pattern, pos);
      RC_ASSERT(cnt_a == r);
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
