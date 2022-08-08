#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

#include "src/basic_strings.h"
#include "src/basic_vectors.h"

// class LongestTrueSeq : public ::testing::Test {};

template <typename T>
void show(std::string &&title, const std::vector<T> &vals) {
  std::cerr << title << ":\n";
  std::copy(vals.cbegin(), vals.cend(),
            std::ostream_iterator<T>(std::cerr, ", "));
  std::cerr << "\n";
}

template <typename T>
void show(std::string &&title, const std::set<T> &vals) {
  std::cerr << title << ":\n";
  std::copy(vals.cbegin(), vals.cend(),
            std::ostream_iterator<T>(std::cerr, ", "));
  std::cerr << "\n";
}

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

RC_GTEST_PROP(HourglassSum, BruteForceCheck, ()) {
  int level = *rc::gen::element(-500, 500);
  vectors::basic::hourglass_ty hours;
  for (int n = 0; n < 6; ++n) {
    for (int k = 0; k < 6; ++k) {
      hours[n][k] = *rc::gen::inRange(-10, 10) + level;
    }
  }
  int target = *rc::gen::inRange(0, 15);
  int counter = 0;
  int max = 0;
  vectors::basic::hourglass_visitor(hours, [&](std::array<int *, 7> hour) {
    if (counter == target) {
      for (int i = 0; i < 7; ++i) {
        int next = *rc::gen::inRange(100, 200) + level;
        max += next;
        *hour[i] = next;
      }
    }
    ++counter;
  });
  RC_ASSERT(max == vectors::basic::hourglass_sum(hours));
}

RC_GTEST_PROP(RotateLeftPrime, SplitAndConcatCheck, ()) {
  std::vector<size_t> primes{1UL, 2UL, 3UL, 5UL, 7UL, 11UL, 13UL, 17UL, 19UL};
  auto generator = rc::gen::elementOf(primes);
  size_t len = *generator;
  size_t rotations = *generator;
  size_t shift = rotations % len;
  // 1 2 3 4 5
  std::vector<int> original(len);
  // rotate: 3, len: 5
  // 1 2 3 | 4 5 <-- rotate 3 times left
  std::iota(original.begin(), original.end(), 1);
  // len(expected) = len - rotate == 2
  // pefix[0] = rotate + 1 == 4
  // expected : 4 5
  std::vector<int> expected(len - shift);
  std::iota(expected.begin(), expected.end(), shift + 1);
  // len(tail) = rotate == 3
  // tail: 1 2 3
  std::vector<int> tail(shift);
  std::iota(tail.begin(), tail.end(), 1);
  // now tail contains fully rotated vector
  std::copy(tail.begin(), tail.end(), std::back_inserter(expected));
  auto actual =
      vectors::basic::rotate_left_prime(std::move(original), rotations);
  RC_ASSERT(std::equal(expected.begin(), expected.end(), actual.begin()));
}

RC_GTEST_PROP(RotateLeft, SplitAndConcatCheck, ()) {
  auto generator = rc::gen::weightedOneOf({
      std::make_pair(1UL, rc::gen::inRange(1UL, 3UL)),
      std::make_pair(3UL, rc::gen::inRange(4UL, 9UL)),
      std::make_pair(5UL, rc::gen::inRange(10UL, 19UL)),
  });
  size_t len = *generator;
  size_t rotations = *generator;
  size_t shift = rotations % len;
  // 1 2 3 4 5
  std::vector<int> original(len);
  // rotate: 3, len: 5
  // 1 2 3 | 4 5 <-- rotate 3 times left
  std::iota(original.begin(), original.end(), 1);
  // len(expected) = len - rotate == 2
  // pefix[0] = rotate + 1 == 4
  // expected : 4 5
  std::vector<int> expected(len - shift);
  std::iota(expected.begin(), expected.end(), shift + 1);
  // len(tail) = rotate == 3
  // tail: 1 2 3
  std::vector<int> tail(shift);
  std::iota(tail.begin(), tail.end(), 1);
  // now tail contains fully rotated vector
  std::copy(tail.begin(), tail.end(), std::back_inserter(expected));
  auto actual = vectors::basic::rotate_left(std::move(original), rotations);
  RC_ASSERT(std::equal(expected.begin(), expected.end(), actual.begin()));
}

RC_GTEST_PROP(FindDuplicates, RandomInsertionCheck, ()) {
  auto push_back = rc::gen::inRange(0, 1);
  auto pick_repeats = rc::gen::inRange(1, 3);
  int max_num = *rc::gen::inRange(1, 7);
  std::list<int> sequence;
  std::set<int> repeated_numbers;
  for (int num = 0; num <= max_num; ++num) {
    auto repeats = *pick_repeats;
    if (repeats > 1) {
      repeated_numbers.emplace(num);
    }
    for (int r = 1; r <= repeats; ++r) {
      if (*push_back) {
        sequence.push_back(num);
      } else {
        sequence.push_front(num);
      }
    }
  }
  if (repeated_numbers.empty()) {
    repeated_numbers.emplace(-1);
  }
  std::vector<int> original;
  std::copy(sequence.begin(), sequence.end(), std::back_inserter(original));
  std::vector<int> expected;
  std::copy(repeated_numbers.begin(), repeated_numbers.end(),
            std::back_inserter(expected));
  std::vector<int> actual = vectors::basic::find_duplicates(original);
  RC_ASSERT(std::equal(expected.begin(), expected.end(), actual.begin()));
}

RC_GTEST_PROP(FindMissingNumber, ShuffleCheck, ()) {
  auto pick_num = rc::gen::inRange(1, 10);
  auto pick_direction = rc::gen::element('l', 'r');
  int expected = *pick_num;
  int len = std::max(*pick_num, expected + 1);
  std::list<int> nums;
  for (int num = 1; num <= len; ++num) {
    if (num != expected) {
      if (*pick_direction == 'r') {
        nums.emplace_back(num);
      } else {
        nums.emplace_front(num);
      }
    }
  }
  std::vector<int> original;
  std::copy(nums.begin(), nums.end(), std::back_inserter(original));
  int actual = vectors::basic::find_missing_number(original);
  RC_ASSERT(expected == actual);
}

RC_GTEST_PROP(FindPeak, ConstructiveCheck, ()) {
  auto len = *rc::gen::inRange(10UL, 19UL);
  auto expected = *rc::gen::inRange(0UL, len - 1UL);
  int cur = *rc::gen::element(-10, 10);
  auto pick_step = rc::gen::inRange(1, 3);
  std::vector<int> arr;
  arr.reserve(len);
  for (size_t idx = 0UL; idx < len; ++idx) {
    if (idx > expected) {
      cur -= *pick_step;
    } else {
      cur += *pick_step;
    }
    arr.push_back(cur);
  }
  auto actual = vectors::basic::find_peak(arr);
  RC_ASSERT(static_cast<int>(expected) == actual);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
