#include <gtest/gtest.h>

TEST(Sanity, FrameworkRuns) {
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7 * 6, 42);
}
