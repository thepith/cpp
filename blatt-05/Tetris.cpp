// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>,
//         Axel Lehmann <lehmanna@cs.uni-freiburg.de>.

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "./Tetris.h"

int sx = 3;
int sy = 2;

// _____________________________________________________________________________
int tx = 5;
int ty = 19;

int txr[4] = { -1, 0, 1, 1 };
int tyr[4] = { -1, -1, -1, 0 };

// _____________________________________________________________________________
void initTerminal() {
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

// _____________________________________________________________________________
void moveTetromino(int key, bool reverse) {
  switch (key) {
    case KEY_UP:
      if (reverse == false) rotateTetromino(1);
      if (reverse == true) rotateTetromino(3);
      break;
    case KEY_DOWN:
      if (reverse == false) ty--;
      if (reverse == true) ty++;
      break;
    case KEY_RIGHT:
      if (reverse == false) tx++;
      if (reverse == true) tx--;
      break;
    case KEY_LEFT:
      if (reverse == false) tx--;
      if (reverse == true) tx++;
      break;
  }
}

// _____________________________________________________________________________
void rotateTetromino(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 4; j++) {
      int xr = tyr[j];
      int yr = -txr[j];
      txr[j] = xr;
      tyr[j] = yr;
    }
  }
}

// _____________________________________________________________________________
void showCell(int x, int y, int attr) {
  attron(attr);
  for (int i = 0; i < sx; i++) {
    for (int j = 0; j < sy; j++) {
      mvprintw((20 - y) * sy + j, (5 + x) * sx + i, " ");
    }
  }
  attroff(attr);
}

// _____________________________________________________________________________
void showTetromino() {
  for (int k = 0; k < 4; k++) {
    showCell(tx + txr[k], ty + tyr[k], A_REVERSE);
  }
}
