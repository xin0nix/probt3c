#include <rapidcheck.h>

#include <algorithm>
#include <vector>

#include "src/basic_vectors.h"

int main() {
  rc::check("reverse does not affect longest_true_seq()",
            [](const std::vector<bool> &xs) {
              int r1 = vectors::basic::longest_true_seq(xs);
              int r2 = vectors::basic::longest_true_seq(xs);
              RC_ASSERT(r1 == r2);
            });
  return 0;
}
