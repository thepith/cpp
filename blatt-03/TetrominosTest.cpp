// Copyright 2017, Pascal Hebbeker
// Test the Calculation of the Pentecost Date

#include <gtest/gtest.h>
#include <ncurses.h>

#include "./Tetrominos.h"

TEST(TetrominoTest, MoveTetromino) {
  posX = 0;
  posY = 0;
  // check movement
  moveTetromino(KEY_RIGHT);
  ASSERT_EQ(1, posX);
  ASSERT_EQ(0, posY);
  moveTetromino(KEY_LEFT);
  ASSERT_EQ(0, posX);
  ASSERT_EQ(0, posY);
  // check border
  posX = 6;
  posY = 0;
  moveTetromino(KEY_RIGHT);
  ASSERT_EQ(6, posX);
  ASSERT_EQ(0, posY);
  posX = 0;
  posY = 0;
  moveTetromino(KEY_LEFT);
  ASSERT_EQ(0, posX);
  ASSERT_EQ(0, posY);
}
