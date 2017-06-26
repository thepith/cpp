// Copyright 2017, Pascal Hebbeker


#include <ncurses.h>
#include "../blatt-05/Tetris.h"
#include "../blatt-05/Structure.h"


// _____________________________________________________________________________
void Tetromino::move(int key, bool reverse) {
  switch (key) {
    case KEY_UP:
      if (reverse == false) rotate(1);
      if (reverse == true) rotate(3);
      break;
    case KEY_DOWN:
      if (reverse == false) y--;
      if (reverse == true) y++;
      break;
    case KEY_RIGHT:
      if (reverse == false) x++;
      if (reverse == true) x--;
      break;
    case KEY_LEFT:
      if (reverse == false) x--;
      if (reverse == true) x++;
      break;
  }
}

// _____________________________________________________________________________
void Tetromino::show() {
  Tetris tetris;
  for (int k = 0; k < 4; k++) {
    tetris.showCell(x + xr[k], y + yr[k], A_REVERSE);
  }
}

// _____________________________________________________________________________
void Tetromino::rotate(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 4; j++) {
      int xr = yr[j];
      int yr = -xr[j];
      xr[j] = xr;
      yr[j] = yr;
    }
  }
}
