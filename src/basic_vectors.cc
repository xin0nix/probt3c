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

int count_pairs_with_sum(const std::vector<int> &arr, const int sum) {
  int cnt = 0;
  std::unordered_map<int, int> seen;
  for (int x : arr) {
    int other = sum - x;
    if (other > 0) {
      cnt += seen[other];
    }
    seen[x]++;
  }
  return cnt;
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

// great explanation here:
// https://stackoverflow.com/questions/23321216/rotating-an-array-using-juggling-algorithm
std::vector<int> rotate_left(std::vector<int> &&arr, const size_t rotations) {
  if (arr.empty() || rotations % arr.size() == 0UL) {
    return std::move(arr);
  }
  const size_t len = arr.size();
  const size_t shift = rotations % len;
  const size_t groups = std::gcd(len, shift);
  // arr:
  // a b c d e
  // shift 3:
  // d e a b c
  //
  // next: 3, 1(6), 4, 2(7), 5!
  //
  // a b c d e a b c d e a b c d e a b c d e
  // _ . . < . . < . . < . . < . . !
  //
  for (size_t group = 0; group < groups; ++group) {
    int first_in_group = arr[group];
    size_t idx = group;

    for (;;) {
      size_t next = idx + shift;
      if (next >= len) {
        next = next % len;
      }
      if (next == group) {
        break;
      }
      arr[idx] = arr[next];
      idx = next;
    }

    arr[idx] = first_in_group;
  }
  return std::move(arr);
}

std::vector<int> find_duplicates(const std::vector<int> &arr) {
  int len = static_cast<int>(arr.size());
  std::vector<int> res(len, 0);
  for (int i = 0; i < len; ++i) {
    res[arr[i]]++;
  }
  int head = 0;
  for (int tail = 0; tail < len; ++tail) {
    if (res[tail] > 1) {
      res[head] = tail;
      head++;
    }
  }
  if (head == 0) {
    // if we resized first, it would lead to additional allocation
    res[0] = -1;
    res.resize(1);
  } else {
    res.resize(head);
  }
  return res;
}

int find_missing_number(const std::vector<int> &arr) {
  if (arr.empty()) {
    return 0;
  }
  int n = static_cast<int>(arr.size());
  int area = ((n + 1) * (n + 2)) / 2;
  int total = std::accumulate(arr.cbegin(), arr.cend(), 0);
  return area - total;
}

int find_peak(const std::vector<int> &arr) {
  const int n = static_cast<int>(arr.size());
  int left = 0;
  int right = n - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if ((mid == 0 || arr[mid] >= arr[mid - 1]) &&
        (mid == n - 1 || arr[mid] >= arr[mid + 1])) {
      return mid;
    }
    if (mid > 0 && arr[mid] < arr[mid - 1]) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return -1;
}

}  // namespace basic
}  // namespace vectors
