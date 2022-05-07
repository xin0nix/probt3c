#include <rapidcheck.h>

#include <algorithm>
#include <vector>

#include "src/basic_vectors.h"

void basic_arrays() {
  rc::check("longest_true_seq", [](const std::vector<bool> &xs) {
    {  // reverse check
      int r1 = vectors::basic::longest_true_seq(xs);
      std::vector<bool> ys(xs.rbegin(), xs.rend());
      int r2 = vectors::basic::longest_true_seq(ys);
      RC_ASSERT(r1 == r2);
    }
  });
  rc::check("count_valleys", [](const std::vector<bool> &xs) {
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
  });
  rc::check("count_even_digit_nums", [](const std::vector<int> &xs) {
    const int r1 = vectors::basic::count_even_digit_nums(xs);
    {  // odd digited number doesn't effect the result
      std::vector<int> xxs(xs);
      xxs.push_back(111);
      int r2 = vectors::basic::count_even_digit_nums(xxs);
      RC_ASSERT(r1 == r2);
    }
    {  // even digited number increments the result
      std::vector<int> xxs(xs);
      xxs.push_back(11);
      int r2 = vectors::basic::count_even_digit_nums(xxs);
      RC_ASSERT(r1 + 1 == r2);
    }
  });
}

int main() {
  basic_arrays();
  return 0;
}
