#include <gtest/gtest.h>

TEST(SimpleTest, FailingTest) {
  EXPECT_EQ(1, 2) << "This is expected to fail, for demo purposes.";
}
