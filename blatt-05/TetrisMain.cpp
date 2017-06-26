// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>,
//         Axel Lehmann <lehmanna@cs.uni-freiburg.de>.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "./Tetris.h"
#include "./Structure.h"

int main(int argc, char** argv) {
  Tetris tetris;
  tetris.initTerminal;
  showTetromino();
  refresh();
  int count = 0;
  int key;
  bool collided;
  Structure structure;
  while (true) {
    // Get user input and fall every 50th iteration.
    key = getch();
    if (++count % 50 == 0) { key = KEY_DOWN; }
    // Check if tetromino is touching the structure (or the bottom) by
    // temporarily moving it one down and checking for a collision.
    moveTetromino(KEY_DOWN, false);
    collided = structure.checkCollision();
    moveTetromino(KEY_DOWN, true);
    if (collided) {
      // When bottom is reached, start again at the top.
      structure.addTetromino();
      structure.removeFullRows();
      ty = 19;
      tx = 5;
      txr[0] = -1;
      txr[1] = 0;
      txr[2] = 1;
      txr[3] = 1;
      tyr[0] = -1;
      tyr[1] = -1;
      tyr[2] = -1;
      tyr[3] = 0;
      // Check if game is lost.
      if (structure.checkCollision() == true) {
        break;
      }
    }
    // Move tetromino.
    moveTetromino(key, false);
    if (structure.checkCollision() == true) {
      moveTetromino(key, true);
    }
    // Draw current structure and tetromino.
    structure.show();
    showTetromino();
    refresh();
    // Wait for 10 milliseconds.
    usleep(10 * 1000);
  }
  endwin();
}
