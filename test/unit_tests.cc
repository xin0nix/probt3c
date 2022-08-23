#ifndef UNIT_TESTS
#define UNIT_TESTS

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>

#include "src/basic_lists.h"
#include "src/basic_vectors.h"

namespace vectors {
namespace basic {
namespace {

using ::testing::ElementsAre;

class BasicVectors : public ::testing::Test {};
class CountEvenDigitNums : public ::testing::Test {};

TEST_F(BasicVectors, Basic) {
  {
    SCOPED_TRACE("longest_true_seq");
    EXPECT_EQ(vectors::basic::longest_true_seq({}), 0);
    EXPECT_EQ(vectors::basic::longest_true_seq({false}), 0);
    EXPECT_EQ(vectors::basic::longest_true_seq({false, false, false}), 0);
    EXPECT_EQ(vectors::basic::longest_true_seq({true}), 1);
    EXPECT_EQ(vectors::basic::longest_true_seq({true, true, true}), 3);
    EXPECT_EQ(vectors::basic::longest_true_seq({true, true, false}), 2);
    EXPECT_EQ(vectors::basic::longest_true_seq({false, true, true}), 2);
    EXPECT_EQ(vectors::basic::longest_true_seq(
                  {false, true, false, true, true, false}),
              2);
  }
  {
    SCOPED_TRACE("count_valleys");
    EXPECT_THAT(vectors::basic::count_valleys({}), 0);
    EXPECT_THAT(vectors::basic::count_valleys({true, false}), 0);
    EXPECT_THAT(
        vectors::basic::count_valleys({true, true, false, true, false, false}),
        0);
    EXPECT_THAT(vectors::basic::count_valleys({false, true}), 1);
    EXPECT_THAT(
        vectors::basic::count_valleys({false, false, true, false, true, true}),
        1);
  }
  {
    SCOPED_TRACE("count_even_digit_nums");
    EXPECT_EQ(vectors::basic::count_even_digit_nums({}), 0);
    EXPECT_EQ(vectors::basic::count_even_digit_nums({1}), 0);
    EXPECT_EQ(vectors::basic::count_even_digit_nums({11}), 1);
    EXPECT_EQ(vectors::basic::count_even_digit_nums({
                  1, 333, 22,    //+1
                  55555, 4444,   //+1
                  1234, 777, 39  //+2
              }),
              4);
  }
  {
    SCOPED_TRACE("rotate_left_prime");
    EXPECT_THAT(vectors::basic::rotate_left_prime({}, 100), ElementsAre());
    EXPECT_THAT(vectors::basic::rotate_left_prime({1}, 100), ElementsAre(1));
    EXPECT_THAT(vectors::basic::rotate_left_prime({1, 2, 3, 4, 5}, 2),
                ElementsAre(3, 4, 5, 1, 2));
    EXPECT_THAT(vectors::basic::rotate_left_prime({1, 2}, 1),
                ElementsAre(2, 1));
    EXPECT_THAT(vectors::basic::rotate_left_prime({1, 2, 3, 4, 5, 6, 7}, 4),
                ElementsAre(5, 6, 7, 1, 2, 3, 4));
  }
  {
    SCOPED_TRACE("get_nth_from_end");
    std::vector nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto nodes = lists::basic::init(nums.begin(), nums.end());
    EXPECT_EQ(lists::basic::get_nth_from_end(nodes[0].get(), 2), 8);
  }
}

}  // namespace
}  // namespace basic
}  // namespace vectors

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif