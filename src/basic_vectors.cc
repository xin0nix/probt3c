#include "basic_vectors.h"

#include <algorithm>
#include <array>
#include <cassert>

namespace vectors {
namespace basic {
using namespace std;
int longest_true_seq(const vector<bool> &sequence) {
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

int count_valleys(const vector<bool> &steps) {
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

int count_even_digit_nums(const vector<int> &numbers) {
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
                       function<void(array<int *, 7>)> &&callback) {
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
  int sum = numeric_limits<int>::min();
  hourglass_visitor(arr, [&](array<int *, 7> hours) {
    int cur = 0;
    for (auto *h : hours) {
      cur += *h;
    }
    sum = max(sum, cur);
  });
  return sum;
}

}  // namespace basic
}  // namespace vectors
