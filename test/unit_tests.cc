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

class LongestTrueSequence : public ::testing::Test {};

TEST_F(LongestTrueSequence, Basic) {
  EXPECT_EQ(vectors::basic::longest_true_seq({}), 0);
  EXPECT_EQ(vectors::basic::longest_true_seq({false}), 0);
  EXPECT_EQ(vectors::basic::longest_true_seq({false, false, false}), 0);
  EXPECT_EQ(vectors::basic::longest_true_seq({true}), 1);
  EXPECT_EQ(vectors::basic::longest_true_seq({true, true, true}), 3);
  EXPECT_EQ(vectors::basic::longest_true_seq({true, true, false}), 2);
  EXPECT_EQ(vectors::basic::longest_true_seq({false, true, true}), 2);
  EXPECT_EQ(
      vectors::basic::longest_true_seq({false, true, false, true, true, false}),
      2);
}

}  // namespace
}  // namespace basic
}  // namespace vectors

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif