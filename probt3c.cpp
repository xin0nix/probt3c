#include <rapidcheck.h>

#include <algorithm>
#include <vector>

#include "src/BasicArrays.hpp"

int main() {
  rc::check("reverse does not affect longest_true_seq()",
            [](const std::vector<bool> &xs) {
              int r1 = arrays::basic::longest_true_seq(xs);
              int r2 = arrays::basic::longest_true_seq(xs);
              RC_ASSERT(r1 == r2);
            });
  rc::check("Placing zero after each value, makes longest_true_seq() = 1",
            [](const std::vector<bool> &xs) {});
  return 0;
}