// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>.

#include <gtest/gtest.h>
#include "./Tetris.h"
#include "./Structure.h"

// _____________________________________________________________________________
TEST(StructureTest, checkCollision) {
  Structure structure;
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 20; y++) {
      structure._cells[x][y] = 0;
    }
  }
  tx = 5;
  ty = 10;
  txr[0] = -1;
  txr[1] = 0;
  txr[2] = 1;
  txr[3] = 1;
  tyr[0] = -1;
  tyr[1] = -1;
  tyr[2] = -1;
  tyr[3] = 0;
  ASSERT_FALSE(structure.checkCollision());
  // left border
  tx = 0;
  ASSERT_TRUE(structure.checkCollision());
  // right border
  tx = 9;
  ASSERT_TRUE(structure.checkCollision());
  // top border
  tx = 5;
  ty = 20;
  ASSERT_TRUE(structure.checkCollision());
  // bottom border
  ty = 0;
  ASSERT_TRUE(structure.checkCollision());
}

// _____________________________________________________________________________
TEST(StructureTest, addTetromino) {
  Structure structure;
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 20; y++) {
      structure._cells[x][y] = 0;
    }
  }
  tx = 5;
  ty = 10;
  txr[0] = -1;
  txr[1] = 0;
  txr[2] = 1;
  txr[3] = 1;
  tyr[0] = -1;
  tyr[1] = -1;
  tyr[2] = -1;
  tyr[3] = 0;
  structure.addTetromino();
  ASSERT_TRUE(structure._cells[4][9]);
  ASSERT_TRUE(structure._cells[5][9]);
  ASSERT_TRUE(structure._cells[6][9]);
  ASSERT_TRUE(structure._cells[6][10]);
}

// _____________________________________________________________________________
TEST(StructureTest, removeFullRows) {
  Structure structure;
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 20; y++) {
      structure._cells[x][y] = true;
    }
  }
  structure.removeFullRows();
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 20; y++) {
      ASSERT_FALSE(structure._cells[x][y]);
    }
  }
}
