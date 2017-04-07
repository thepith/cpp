// Copyright 2017, Pascal Hebbeker


#include "../blatt-03/Tetrominos.h"
#include <ncurses.h>
#include <unistd.h>
#include <iostream>

// T tetromino
int tetrominoWidth = 3;
int tetrominoHeight = 2;

// Standard Tetris
int canvasWidth = 10;
int canvasHeight = 20;

int canvasOrgX = 4;
int canvasOrgY = 4;

int posX = canvasOrgX + canvasWidth/2 - tetrominoWidth/2;
int posY = canvasOrgY;

int downStep = 1;

// _____________________________________________________________________________
void moveTetromino(int key) {
  switch (key) {
    case KEY_LEFT: posX = posX > canvasOrgX? posX-1 : posX ; break;
    case KEY_RIGHT: posX = posX < canvasOrgX + canvasWidth - tetrominoWidth ?
                   posX+1 : posX; break;
    case KEY_DOWN: posY = posY + downStep <= canvasOrgY + canvasHeight -
                  tetrominoHeight ? posY+downStep : canvasOrgY + canvasHeight -
                    tetrominoHeight; break;
  }
}

// _____________________________________________________________________________
void positionTetrominosAtTop() {
  posX = canvasOrgX + canvasWidth/2 - tetrominoWidth/2;
  posY = canvasOrgY;
}


// _____________________________________________________________________________
void gravityTetromino() {
  posY = posY + 1 <= canvasOrgY + canvasHeight - tetrominoHeight ?
    posY+1 : posY;
}

// _____________________________________________________________________________
bool atFloor() {
  if (posY == canvasOrgY + canvasHeight - tetrominoHeight) {
    return true;
  } else {
    return false;
  }
}

// _____________________________________________________________________________
int timeStep(int duration) {
  drawTetromino(posX, posY, true);
  // allow for moves in one timestep
  int posoldX = posX;
  int posoldY = posY;
  for (int i = 0; i < duration/10; i++) {
    int key = getch();
    moveTetromino(key);
    if (key == 'q') { return 1; }
    if (posoldX != posX | posoldY != posY) {
      drawTetromino(posoldX, posoldY, false);
      drawTetromino(posX, posY, true);
      posoldX = posX;
      posoldY = posY;
    }
    if (atFloor()) {return 0;}
    usleep(10);
  }
  gravityTetromino();
  drawTetromino(posoldX, posoldY, false);
  drawTetromino(posX, posY, true);
  return 0;
}

// _____________________________________________________________________________
void initScreen() {
  initscr();  // Initialization.
  cbreak();  // Do not wait for RETURN.
  noecho();  // Don't echo key pressed on screen.
  curs_set(false);  // Don't show the cursor.
  nodelay(stdscr, true);  // Don't wait for key pressed.
  keypad(stdscr, true);  // Special codes for KEY_LEFT, KEY_UP, ...
  int start = getch();
  // draw top left corner
  printf("\x1b[%d;%dH\x1b(0\x6c\x1b(B", canvasOrgY-1, canvasOrgX - 1);
  // draw left border
  for (int i = 0; i < canvasHeight; i++) {
    printf("\x1b[%d;%dH\x1b(0\x78\x1b(B", canvasOrgY+i,
        canvasOrgX - 1);
  }
  // draw bottom left corner
  printf("\x1b[%d;%dH\x1b(0\x6d\x1b(B", canvasOrgY+canvasHeight,
      canvasOrgX - 1);
  // draw bottom border
  for (int i = 0; i < canvasWidth; i++) {
    printf("\x1b[%d;%dH\x1b(0\x71\x1b(B", canvasOrgY+canvasHeight,
        canvasOrgX + i);
  }
  // draw bottom right corner
  printf("\x1b[%d;%dH\x1b(0\x6a\x1b(B", canvasOrgY+canvasHeight,
      canvasOrgX + canvasWidth);
  // draw right border
  for (int i = 0; i < canvasHeight; i++) {
    printf("\x1b[%d;%dH\x1b(0\x78\x1b(B", canvasOrgY+i,
        canvasOrgX + canvasWidth);
  }
  // draw top right corner
  printf("\x1b[%d;%dH\x1b(0\x6b\x1b(B", canvasOrgY-1,
      canvasOrgX + canvasWidth);
  // draw top border
  for (int i = 0; i < canvasWidth; i++) {
    printf("\x1b[%d;%dH\x1b(0\x71\x1b(B", canvasOrgY-1,
        canvasOrgX + i);
  }
  std::cout << std::flush;
}

// _____________________________________________________________________________
void drawTetromino(int drawX, int drawY, bool draw) {
  drawTetrominoT(drawX, drawY, draw);
}

// _____________________________________________________________________________
void drawTetrominoT(int drawX, int drawY, bool draw) {
  printf("\x1b[%d;%dH\x1b[%dm   ", drawY, drawX, draw ? 7 : 0);
  printf("\x1b[%d;%dH\x1b[%dm ", drawY+1, drawX+1, draw ? 7 : 0);
  // refresh() seems not to work with cygwin under windows
  std::cout << std::flush;
}

// _____________________________________________________________________________
void drawTetrominoAtFloor() {
  printf("\x1b[31m");
  drawTetromino(posX, posY, true);
  printf("\x1b[39;49m");
}

