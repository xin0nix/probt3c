#include "basic_strings.h"

#include <algorithm>

namespace strings {
namespace basic {

long repeated_string(const std::string &pattern, const long position) {
  auto count_a = [](const std::string &str) {
    return static_cast<long>(std::count(str.cbegin(), str.cend(), 'a'));
  };
  long pattern_len = static_cast<long>(pattern.length());
  return (position / pattern_len) * count_a(pattern) +
         count_a(pattern.substr(0, position % pattern_len));
}

}  // namespace basic
}  // namespace strings