// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>.

#include <gtest/gtest.h>
#include <ncurses.h>
#include "./Graviton.h"

// _____________________________________________________________________________
TEST(GravitonTest, moveGraviton) {
  rowIndex = 0;
  colIndex = 0;
  moveGraviton(KEY_DOWN);
  ASSERT_EQ(1, rowIndex);
  ASSERT_EQ(0, colIndex);
  moveGraviton(KEY_RIGHT);
  ASSERT_EQ(1, rowIndex);
  ASSERT_EQ(1, colIndex);
}

// Run all tests.
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
