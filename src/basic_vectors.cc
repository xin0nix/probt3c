#include "basic_vectors.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <numeric>

namespace vectors {
namespace basic {

int longest_true_seq(const std::vector<bool> &sequence) {
  int max = 0;
  int cur = 0;
  for (auto val : sequence) {
    if (!val) {
      cur = 0;
    } else {
      cur += 1;
      if (cur > max) {
        max = cur;
      }
    }
  }
  return max;
}

int count_valleys(const std::vector<bool> &steps) {
  int level = 0;
  int valleys = 0;
  for (auto step : steps) {
    if (step) {
      if (level++ == -1) {
        valleys++;
      }
    } else {
      level--;
    }
  }

  return valleys;
}

int count_even_digit_nums(const std::vector<int> &numbers) {
  int sum{0};
  const int base = 10;
  for (int num : numbers) {
    int cnt{0};
    while (num > 0) {
      num /= base;
      cnt++;
    }
    if (cnt % 2 == 0) {
      sum++;
    }
  }
  return sum;
}

void hourglass_visitor(hourglass_ty &arr,
                       std::function<void(std::array<int *, 7>)> &&callback) {
  // we assume vector has the right shape
  for (int n = 0; n < 4; ++n) {
    auto &top = arr[n];
    auto &middle = arr[n + 1];
    auto &bottom = arr[n + 2];
    for (int k = 0; k < 4; ++k) {
      callback({// top
                &top[k], &top[k + 1], &top[k + 2],
                // middle
                &middle[k + 1],
                // bottom
                &bottom[k], &bottom[k + 1], &bottom[k + 2]});
    }
  }
}

int hourglass_sum(hourglass_ty &arr) {
  int sum = std::numeric_limits<int>::min();
  hourglass_visitor(arr, [&](std::array<int *, 7> hours) {
    int cur = 0;
    for (auto *h : hours) {
      cur += *h;
    }
    sum = std::max(sum, cur);
  });
  return sum;
}

std::vector<int> rotate_left_prime(std::vector<int> &&arr,
                                   const size_t rotations) {
  if (arr.empty() || rotations % arr.size() == 0UL) {
    return std::move(arr);
  }
  size_t shift = rotations % arr.size();
  // we can rotate in O(n) if both "arr" and "shift" are prime numbers
  int tmp = arr[0UL];
  arr[0UL] = arr[shift];
  size_t step = arr.size() - shift;
  size_t next = step % arr.size();
  for (size_t i = 1UL; i < arr.size(); ++i) {
    std::swap(tmp, arr[next]);
    next = (next + step) % arr.size();
  }
  return std::move(arr);
}

}  // namespace basic
}  // namespace vectors
