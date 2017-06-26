// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>.

#ifndef BLATT_05_STRUCTURE_H_
#define BLATT_05_STRUCTURE_H_

#include <gtest/gtest.h>

// Class for the structure.
class Structure {
 public:
  // Constructor.
  Structure();
  // explicit Structure(bool fillValue);

  // Check if tetromino is colliding with border or structure.
  bool checkCollision();

  // Add the tetromino (at its current position) to the structure.
  void addTetromino();

  // Remove full lines from the structure.
  void removeFullRows();

  // Draw the current structure (in red).
  void show();

 private:
  // The 10 x 20 cells of the structure.
  bool _cells[10][20];

  FRIEND_TEST(StructureTest, checkCollision);
  FRIEND_TEST(StructureTest, addTetromino);
  FRIEND_TEST(StructureTest, removeFullRows);
};

#endif  // BLATT_05_STRUCTURE_H_
