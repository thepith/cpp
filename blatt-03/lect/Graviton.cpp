// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>.

#include <ncurses.h>
#include <unistd.h>
#include "./Graviton.h"

// _____________________________________________________________________________
int rowIndex = 20;
int colIndex = 60;

// _____________________________________________________________________________
void initializeScreen() {
  initscr();  // Initialization.
  cbreak();  // Don't wait for RETURN.
  noecho();  // Don't echo key pressed on screen.
  curs_set(false);  // Don't show the cursor.
  nodelay(stdscr, true);  // Don't wait for key pressed.
  keypad(stdscr, true);  // Special codes for KEY_LEFT, KEY_UP, ...
}

// _____________________________________________________________________________
void showGraviton() {
  printf("\x1b[%d;%dHg", rowIndex, colIndex);
  // printf("\x1b[%d;%dH\x1b[7m ", rowIndex, colIndex);
  usleep(0);  // Sleep for 100 milliseconds.
  refresh();  // Flush to screen.
  //printf("\x1b[%d;%dH ", rowIndex, colIndex);
  // printf("\x1b[%d;%dH\x1b[0m ", rowIndex, colIndex);
  usleep(0);  // Sleep for 500 milliseconds.
  refresh();  // Flush to screen.
}

// _____________________________________________________________________________
void moveGraviton(int key) {
  switch (key) {
    case KEY_UP: rowIndex--; break;
    case KEY_DOWN: rowIndex++; break;
    case KEY_LEFT: colIndex--; break;
    case KEY_RIGHT: colIndex++; break;
  }
}
