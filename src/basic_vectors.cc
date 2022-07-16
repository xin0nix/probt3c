#include "basic_vectors.h"

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
}  // namespace basic
}  // namespace vectors
