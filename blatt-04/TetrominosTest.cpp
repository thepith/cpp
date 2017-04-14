// Copyright 2017, Pascal Hebbeker
// Test the Calculation of the Pentecost Date

#include <gtest/gtest.h>
#include <ncurses.h>

#include "./Tetrominos.h"

TEST(TetrominoTest, MoveTetromino) {
  posX = 4;
  posY = 4;
  // check movement
  moveTetromino(KEY_RIGHT);
  ASSERT_EQ(5, posX);
  ASSERT_EQ(4, posY);
  moveTetromino(KEY_LEFT);
  ASSERT_EQ(4, posX);
  ASSERT_EQ(4, posY);
  moveTetromino(KEY_DOWN);
  ASSERT_EQ(4, posX);
  ASSERT_EQ(5, posY);
  // check border
  posX = 11;
  posY = 4;
  moveTetromino(KEY_RIGHT);
  ASSERT_EQ(11, posX);
  ASSERT_EQ(4, posY);
  posX = 4;
  posY = 4;
  moveTetromino(KEY_LEFT);
  ASSERT_EQ(4, posX);
  ASSERT_EQ(4, posY);
  posX = 4;
  posY = 23;
  moveTetromino(KEY_LEFT);
  ASSERT_EQ(4, posX);
  ASSERT_EQ(23, posY);
}

TEST(TetrominoTest, positionTetrominosAtTop) {
  posX = 0;
  posY = 0;
  positionTetrominosAtTop();
  ASSERT_EQ(posX, canvasOrgX + canvasWidth/2 - tetrominoWidth/2);
  ASSERT_EQ(posY, canvasOrgY);
}

TEST(TetrominoTest, gravityTetromino) {
  posX = 4;
  posY = 4;
  gravityTetromino();
  ASSERT_EQ(posX, 4);
  ASSERT_EQ(posY, 5);
}

TEST(TetrominoTest, atFloor) {
  posX = 4;
  posY = 23;
  int test = atFloor();
  ASSERT_EQ(0, test);
  posX = 4;
  posY = 22;
  test = atFloor();
  ASSERT_EQ(1, test);
}
