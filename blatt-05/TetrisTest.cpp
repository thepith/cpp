// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>,
//         Axel Lehmann <lehmanna@cs.uni-freiburg.de>.

#include <gtest/gtest.h>
#include <ncurses.h>
#include "./Tetris.h"

// _____________________________________________________________________________
TEST(TetrisTest, moveTetromino) {
  tx = 3;
  ty = 10;
  moveTetromino(KEY_LEFT, false);
  ASSERT_EQ(2, tx);
  ASSERT_EQ(10, ty);
  moveTetromino(KEY_RIGHT, false);
  ASSERT_EQ(3, tx);
  ASSERT_EQ(10, ty);
  moveTetromino(KEY_DOWN, false);
  ASSERT_EQ(3, tx);
  ASSERT_EQ(9, ty);
  moveTetromino(KEY_DOWN, true);
  ASSERT_EQ(3, tx);
  ASSERT_EQ(10, ty);
}

// _____________________________________________________________________________
TEST(TetrisTest, rotateTetromino) {
  txr[0] = -1;
  txr[1] = 0;
  txr[2] = 1;
  txr[3] = 1;
  tyr[0] = -1;
  tyr[1] = -1;
  tyr[2] = -1;
  tyr[3] = 0;
  rotateTetromino(1);
  ASSERT_EQ(-1, txr[0]);
  ASSERT_EQ(-1, txr[1]);
  ASSERT_EQ(-1, txr[2]);
  ASSERT_EQ(0, txr[3]);
  ASSERT_EQ(1, tyr[0]);
  ASSERT_EQ(0, tyr[1]);
  ASSERT_EQ(-1, tyr[2]);
  ASSERT_EQ(-1, tyr[3]);
  rotateTetromino(3);
  ASSERT_EQ(-1, txr[0]);
  ASSERT_EQ(0, txr[1]);
  ASSERT_EQ(1, txr[2]);
  ASSERT_EQ(1, txr[3]);
  ASSERT_EQ(-1, tyr[0]);
  ASSERT_EQ(-1, tyr[1]);
  ASSERT_EQ(-1, tyr[2]);
  ASSERT_EQ(0, tyr[3]);
}
