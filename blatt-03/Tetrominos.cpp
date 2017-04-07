// Copyright 2017, Pascal Hebbeker


#include "../blatt-03/Tetrominos.h"
#include <ncurses.h>
#include <unistd.h>


// T tetromino
int tetrominoWidth = 3;
int tetrominoHeight = 2;

// Standard Tetris
int canvasWidth = 9;
int canvasHeight = 20;

int canvasOrgX = 4;
int canvasOrgY = 4;

int posX = canvasOrgX + canvasWidth/2;
int posY = canvasOrgY;

// _____________________________________________________________________________
int moveTetromino(int key) {
  switch (key) {
    case KEY_LEFT: posX = posX > 0? posX-1 : posX ; break;
    case KEY_RIGHT: posX = posX < canvasWidth - tetrominoWidth? posX+1 : posX;
                   break;
  }
}

void initScreen() {
  initscr();  // Initialization.
  cbreak();  // Do not wait for RETURN.
  noecho();  // Don't echo key pressed on screen.
  curs_set(false);  // Don't show the cursor.
  nodelay(stdscr, true);  // Don't wait for key pressed.
  keypad(stdscr, true);  // Special codes for KEY_LEFT, KEY_UP, ...
}

void drawTetromino(int drawX, int drawY, bool draw) {
  drawTetrominoT(drawX, drawY, draw);
}

void drawTetrominoT(int drawX, int drawY, bool draw) {
  printf("\x1b[%d;%dH\x1b[7ma", drawY, drawX);
  usleep(100);
  //printf("\x1b[%d;%dH\x1b[0m ", drawY, drawX);
  refresh();
  //printf("\x1b[%d;%dHe", drawY+1, drawX+1);
}
