// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>,
//         Axel Lehmann <lehmanna@cs.uni-freiburg.de>.

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "../blatt-05/Tetris.h"
#include "../blatt-05/Tetromino.h"
#include "../blatt-05/Structure.h"

// _____________________________________________________________________________
void Tetris::initTerminal() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  start_color();
  use_default_colors();
  init_pair(1, COLOR_RED, COLOR_RED);
}

void Tetris::play() {
  Structure structure;
  tetromino tetromino;
  //set a new tetromino
  tetromino.set(0);
  while (true) {
    // Get user input and fall every 50th iteration.
    key = getch();
    if (++count % 50 == 0) { key = KEY_DOWN; }
    // Check if tetromino is touching the structure (or the bottom) by
    // temporarily moving it one down and checking for a collision.
    tetromino.move(KEY_DOWN, false);
    collided = structure.checkCollision(tetromino);
    tetromino.move(KEY_DOWN, true);
    if (collided) {
      // When bottom is reached, start again at the top.
      structure.addTetromino(tetromino);
      structure.removeFullRows();
      tetromino.set(0);
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
    tetromino.show();
    refresh();
    // Wait for 10 milliseconds.
    usleep(10 * 1000);
  }
}

// _____________________________________________________________________________
void Tetris::showCell(int x, int y, int attr) {
  attron(attr);
  for (int i = 0; i < sx; i++) {
    for (int j = 0; j < sy; j++) {
      mvprintw((20 - y) * sy + j, (5 + x) * sx + i, " ");
    }
  }
  attroff(attr);
}
