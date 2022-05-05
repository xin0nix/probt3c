#ifndef UNIT_TESTS
#define UNIT_TESTS

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>

#include "src/basic_vectors.h"

namespace vectors {
namespace basic {
namespace {

using ::testing::ElementsAre;

class BasicArrays : public ::testing::Test {};
class CountEvenDigitNums : public ::testing::Test {};

TEST_F(BasicArrays, Basic) {
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
}

}  // namespace
}  // namespace basic
}  // namespace vectors

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif