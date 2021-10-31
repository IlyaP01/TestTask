#include "gtest/gtest.h"
#include "../src/Figure/figure.h"
#include <QString>

TEST(TestTest, TestTEst) {
  EXPECT_EQ(1, 1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
