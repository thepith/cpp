// Copyright 2017, Pascal Hebbeker
// Test the Calculation of the Pentecost Date

#include <gtest/gtest.h>

#include "./Pentecost.h"

TEST(Pentecost, DayOfPentecost) {
  ASSERT_EQ(16, DayOfPentecost(2016));
  ASSERT_EQ(36, DayOfPentecost(2017));
  ASSERT_EQ(21, DayOfPentecost(2018));
  ASSERT_EQ(41, DayOfPentecost(2019));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
