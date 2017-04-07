// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>.

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "./Graviton.h"

// Main function.
int main(int argc, char** argv) {
  initializeScreen();
  while (true) {
    showGraviton();
    int key = getch();
    moveGraviton(key);
    if (key == 'q') { break; }
  }
  endwin();
}
