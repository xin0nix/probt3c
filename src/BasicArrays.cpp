#include "BasicArrays.hpp"

namespace arrays {
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
}  // namespace basic
}  // namespace arrays
