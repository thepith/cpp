// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>.

#include <ncurses.h>
#include "./Tetris.h"
#include "./Structure.h"

// _____________________________________________________________________________
Structure::Structure() {
// Structure::Structure(bool fillValue) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {
      _cells[i][j] = 0;
      // _cells[i][j] = fillValue;
    }
  }
}

// _____________________________________________________________________________
bool Structure::checkCollision() {
  for (int i = 0; i < 4; i++) {
    int x = tx + txr[i];
    int y = ty + tyr[i];
    if (x < 0 || x > 9) return true;
    if (y < 0 || y > 19) return true;
    if (_cells[x][y] == true) return true;
  }
  return false;
}

// _____________________________________________________________________________
void Structure::addTetromino() {
  for (int i = 0; i < 4; i++) {
    int x = tx + txr[i];
    int y = ty + tyr[i];
    _cells[x][y] = true;
  }
}

// _____________________________________________________________________________
void Structure::removeFullRows() {
  for (int y = 0; y < 20; y++) {
    // Check if row y is full.
    bool fullRow = true;
    for (int x = 0; x < 10; x++) {
      if (_cells[x][y] != true) {
        fullRow = false;
      }
    }
    // If yes, move all rows above one level down.
    if (fullRow != true) continue;
    for (int z = y+1; z < 20; z++) {
      for (int x = 0; x < 10; x++) {
        _cells[x][z-1] = _cells[x][z];
      }
    }
    // Fill top row with empty space.
    for (int x = 0; x < 10; x++) {
      _cells[x][19] = false;
    }
    // The structure moved one down, so check this row again.
    y--;
  }
}

// _____________________________________________________________________________
void Structure::show() {
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 20; y++) {
      showCell(x, y, _cells[x][y] ? COLOR_PAIR(1) : A_NORMAL);
    }
  }
}

