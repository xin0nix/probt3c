#ifndef BASIC_VECTORS_HPP
#define BASIC_VECTORS_HPP

#include <array>
#include <functional>
#include <vector>

namespace vectors {
namespace basic {

using hourglass_ty = std::array<std::array<int, 6>, 6>;

int longest_true_seq(const std::vector<bool> &sequence);
int count_valleys(const std::vector<bool> &steps);
int count_even_digit_nums(const std::vector<int> &numbers);
void hourglass_visitor(hourglass_ty &arr,
                       std::function<void(std::array<int *, 7>)> &&callback);
int hourglass_sum(hourglass_ty &arr);
std::vector<int> rotate_left_prime(std::vector<int> &&arr,
                                   const size_t rotations);
std::vector<int> rotate_left(std::vector<int> &&arr, const size_t rotations);
std::vector<int> find_duplicates(const std::vector<int> &arr);
int find_missing_number(const std::vector<int> &arr);
}  // namespace basic
}  // namespace vectors

#endif  // BASIC_VECTORS_HPP
