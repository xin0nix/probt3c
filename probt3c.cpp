#include <rapidcheck.h>

#include <vector>
#include <algorithm>

#include "src/BasicArrays.hpp"

int main()
{
  rc::check("reverse does not affect longest_true_seq()",
            [](const std::vector<bool> &xs)
            {
              int r1 = arrays::basic::longest_true_seq(xs);
              int r2 = arrays::basic::longest_true_seq(xs);
              RC_ASSERT(r1 == r2);
            });
  return 0;
}