// Copyright 2017, Pascal Hebbeker


#include "../blatt-04/Tetrominos.h"
#include <ncurses.h>
#include <unistd.h>
#include <iostream>

// T tetromino
int tetrominoWidth = 3;
int tetrominoHeight = 2;

// Standard Tetris
int canvasWidth = 10;
int canvasHeight = 20;

int canvasOrgX = 2;
int canvasOrgY = 2;

int txr[4] = {0, 1, 1, 2};
int tyr[4] = {0, 0, 1, 1};

// Structure of the previous tetrominos.
bool structure[10][20];

int posX = canvasWidth/2 - tetrominoWidth/2;
int posY = 0;

// _____________________________________________________________________________
bool overlap(int x, int y) {
  for (int i = 0; i < 4; i++) {
    int posXrel = x + txr[i];
    int posYrel = y + tyr[i];
    if ( (posXrel < 0) || (posYrel < 0)
        || (posXrel >= canvasWidth) || (posYrel >= canvasHeight) ) {
      return true;
    }
    if (structure[posXrel][posYrel]) {
      return true;
    }
  }
  return false;
}

// _____________________________________________________________________________
void moveTetromino(int key) {
  switch (key) {
    case KEY_LEFT:
      if (!overlap(posX - 1, posY)) {
        drawTetromino(posX, posY, 0);
        posX = posX-1;
        drawTetromino(posX, posY, 1);
      }
      break;
    case KEY_RIGHT:
      if (!overlap(posX + 1, posY)) {
        drawTetromino(posX, posY, 0);
        posX = posX+1;
        drawTetromino(posX, posY, 1);
      }
      break;
    case KEY_DOWN:
      if (!overlap(posX, posY + 1)) {
        drawTetromino(posX, posY, 0);
        posY = posY+1;
        drawTetromino(posX, posY, 1);
      }
      break;
    case KEY_UP:
      drawTetromino(posX, posY, 0);
      rotateTetromino();
      if (overlap(posX, posY)) {
        rotateTetromino();
        rotateTetromino();
        rotateTetromino();
      }
      drawTetromino(posX, posY, 1);
      break;
  }
}

// _____________________________________________________________________________
int widthTetromino() {
  int w = 0;
  for (int i = 0; i < 4; i++) {
    w = txr[i] > w? txr[i] : w;
  }
  return w + 1;
}

// _____________________________________________________________________________
int heightTetromino() {
  int h = 0;
  for (int i = 0; i < 4; i++) {
    h = tyr[i] > h? tyr[i] : h;
  }
  return h + 1;
}

// _____________________________________________________________________________
void adjustRelativeCoordinates() {
  int h = 20;
  int w = 20;
  for (int i = 0; i < 4; i++) {
    h = tyr[i] < h? tyr[i] : h;
    w = txr[i] < w? txr[i] : w;
  }
  for (int i = 0; i < 4; i++) {
    tyr[i] = tyr[i] - h;
    txr[i] = txr[i] - w;
  }
  tetrominoWidth = widthTetromino();
  tetrominoHeight = heightTetromino();
}

// _____________________________________________________________________________
int positionTetrominosAtTop() {
  txr[0] = 0;
  txr[1] = 1;
  txr[2] = 1;
  txr[3] = 2;
  tyr[0] = 0;
  tyr[1] = 0;
  tyr[2] = 1;
  tyr[3] = 1;
  adjustRelativeCoordinates();
  posX = canvasWidth/2 - tetrominoWidth/2;
  posY = 0;
  if (atFloor()) {
    drawTetromino(posX, posY, 1);
    printf("GAME OVER");
    fflush(stdout);
    sleep(3);
    return 1;
  }
  drawTetromino(posX, posY, 1);
  fflush(stdout);
  return 0;
}

// _____________________________________________________________________________
void rotateTetromino() {
  for (int i = 0; i < 4; i++) {
    txr[i] = txr[i] + tyr[i];
    tyr[i] = txr[i] - tyr[i];
    txr[i] = txr[i] - tyr[i];
    txr[i] = -txr[i];
  }
  adjustRelativeCoordinates();
}

// _____________________________________________________________________________
void gravityTetromino() {
  if (!overlap(posX, posY + 1)) {
    drawTetromino(posX, posY, 0);
    posY++;
    drawTetromino(posX, posY, 1);
  }
}

// _____________________________________________________________________________
bool atFloor() {
  int posXrel = posX;
  int posYrel = posY;
  bool floored = false;
  if (posYrel >= canvasHeight - tetrominoHeight) {
    floored = true;
  } else {
    for (int i = 0; i < 4; i++) {
      if (structure[posXrel+txr[i]][posYrel + tyr[i] + 1]) {
        floored = true;
        break;
      }
    }
  }
  if (floored) {
    for (int i = 0; i < 4; i++) {
      structure[posXrel+txr[i]][posYrel + tyr[i]] = true;
    }
  }
  return floored;
}

// _____________________________________________________________________________
void checkLines(int iline) {
  int nblock = 0;
  for (int x = 0; x < canvasWidth; x++) {
    if (structure[x][iline]) {
      nblock++;
    }
  }
  // line is full
  if (nblock == canvasWidth) {
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_RED);
    init_pair(4, COLOR_BLACK, COLOR_RED);
    // shift structure
    for (int x = 0; x < canvasWidth; x++) {
      for (int jline = iline; jline >= 0; jline--) {
        switch (jline) {
          case 0:
            structure[x][jline] = false; break;
          default:
            structure[x][jline] = structure[x][jline-1];
        }
        if (structure[x][jline]) {
          attron(COLOR_PAIR(3));
        } else {
          attron(COLOR_PAIR(1));
        }
        mvprintw(canvasOrgY + jline, canvasOrgX + x, " ");
      }
    }
  }
  fflush(stdout);
}

// _____________________________________________________________________________
int timeStep(int duration) {
  drawTetromino(posX, posY, 1);
  int tSleep = 5;
  // allow for moves in one timestep
  for (int i = 0; i < duration/tSleep; i++) {
    int key = getch();
    moveTetromino(key);
    if (key == 'q') { return 1; }
    usleep(tSleep);
  }
  if (atFloor()) {
    drawTetrominoAtFloor();
    for (int relativeLine = 0;
        relativeLine <= tetrominoHeight;
        relativeLine++) {
      checkLines(relativeLine + posY);
    }
    int playing = positionTetrominosAtTop();
    if (playing != 0) {
      return 1;
    }
  } else {
    gravityTetromino();
  }
  return 0;
}

// _____________________________________________________________________________
void initScreen() {
  initscr();  // Initialization.
  start_color();
  cbreak();  // Do not wait for RETURN.
  noecho();  // Don't echo key pressed on screen.
  curs_set(false);  // Don't show the cursor.
  nodelay(stdscr, true);  // Don't wait for key pressed.
  keypad(stdscr, true);  // Special codes for KEY_LEFT, KEY_UP, ...
  int start = getch();
  // draw border
  for (int ix = 0; ix <= canvasWidth + 1; ix++) {
    for (int iy = 0; iy <= canvasHeight + 1; iy++) {
      if ( (ix == 0) ||
          (iy == 0) ||
          (ix == canvasWidth + 1) ||
          (iy == canvasHeight + 1)) {
        mvprintw(canvasOrgY+iy - 1, canvasOrgX + ix - 1, "#");
      }
    }
  }
  fflush(stdout);
  for (int x = 0; x < canvasWidth; x++) {
    for (int y = 0; y < canvasHeight; y++) {
      structure[x][y] = false;
    }
  }
}

// _____________________________________________________________________________
void drawTetromino(int drawX, int drawY, int draw) {
  drawTetrominoT(drawX, drawY, draw);
}

// _____________________________________________________________________________
void drawTetrominoT(int drawX, int drawY, int mode) {
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);
  init_pair(3, COLOR_BLACK, COLOR_RED);
  attron(COLOR_PAIR(mode + 1));
  for (int i = 0; i < 4; i++) {
    mvprintw(canvasOrgY + drawY + tyr[i],
        canvasOrgX + drawX + txr[i], " ", mode);
  }
  // refresh() seems not to work with cygwin under windows?
  fflush(stdout);
}

// _____________________________________________________________________________
void drawTetrominoAtFloor() {
  drawTetromino(posX, posY, 2);
  fflush(stdout);
}

