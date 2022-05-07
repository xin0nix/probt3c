#include "basic_vectors.h"

namespace vectors {
namespace basic {
using namespace std;
int longest_true_seq(const vector<bool> &xs) {
  int max = 0;
  int cur = 0;
  for (auto x : xs) {
    if (!x) {
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

int count_valleys(const vector<bool> &xs) {
  int level = 0;
  int valleys = 0;
  for (int x : xs) {
    switch (x) {
      case true:  // up
        if (level++ == -1) valleys++;
        break;
      case false:  // down
        level--;
        break;
    }
  }
  return valleys;
}

int count_even_digit_nums(const vector<int> &xs) {
  int sum{0};
  for (int x : xs) {
    int c{0};
    while (x > 0) {
      x /= 10;
      c++;
    }
    if (c % 2 == 0) {
      sum++;
    }
  }
  return sum;
}
}  // namespace basic
}  // namespace vectors
