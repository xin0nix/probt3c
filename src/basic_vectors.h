#ifndef BASIC_VECTORS_HPP
#define BASIC_VECTORS_HPP

#include <array>
#include <functional>
#include <vector>

namespace vectors {
namespace basic {
using namespace std;

using hourglass_ty = array<array<int, 6>, 6>;

int longest_true_seq(const vector<bool> &sequence);
int count_valleys(const vector<bool> &steps);
int count_even_digit_nums(const vector<int> &numbers);
void hourglass_visitor(hourglass_ty &arr,
                       function<void(array<int *, 7>)> &&callback);
int hourglass_sum(hourglass_ty &arr);
vector<int> rotate_left_prime(vector<int> &&arr, const size_t rotations);
}  // namespace basic
}  // namespace vectors

#endif  // BASIC_VECTORS_HPP
