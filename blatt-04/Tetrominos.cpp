// Copyright 2017, Pascal Hebbeker


#include "../blatt-04/Tetrominos.h"
#include <ncurses.h>
#include <unistd.h>
#include <iostream>

// T tetromino
int tetrominoWidth = 2;
int tetrominoHeight = 3;

// Standard Tetris
int canvasWidth = 10;
int canvasHeight = 20;

int canvasOrgX = 4;
int canvasOrgY = 4;

int txr[4] = {0, 1, 1, 2};
int tyr[4] = {0, 0, 1, 1};

// Structure of the previous tetrominos.
bool structure[10][20];

int posX = canvasOrgX + canvasWidth/2 - tetrominoWidth/2;
int posY = canvasOrgY;

// _____________________________________________________________________________
bool overlap(int x, int y){
  int posXrel = x - canvasOrgX + 1;
  int posYrel = y - canvasOrgY;
  if((x < 0)||(y<0)||(x>=canvasWidth)||(y>=canvasHeight)){
    return true;
  }
  if((x < 0)||(y<0)||(x>=canvasWidth)||(y>=canvasHeight)){
    return true;
  }
  for (int i = 0; i < 4; i++) {
    if(structure[posXrel+txr[i]][posYrel + tyr[i]]){
      return true;
    }
  }
  return false;
}

// _____________________________________________________________________________
void moveTetromino(int key) {
  switch (key) {
    case KEY_LEFT:
      if(! overlap(posX - 1, posY)){
        drawTetromino(posX, posY, 0);
        posX = posX-1;
        drawTetromino(posX, posY, 1);
      }
      break;
    case KEY_RIGHT:
      if(! overlap(posX + 1, posY)){
        drawTetromino(posX, posY, 0);
        posX = posX+1;
        drawTetromino(posX, posY, 1);
      }
      break;
    case KEY_DOWN:
      if(! overlap(posX, posY + 1)){
        drawTetromino(posX, posY, 0);
        posY = posY+1;
        drawTetromino(posX, posY, 1);
      }
      break;
    case KEY_UP:
      drawTetromino(posX, posY, 0);
      rotateTetromino();
      if(overlap(posX, posY)){
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
  posX = canvasOrgX + canvasWidth/2 - tetrominoWidth/2;
  posY = canvasOrgY;
  txr[0] = 0;
  txr[1] = 1;
  txr[2] = 1;
  txr[3] = 2;
  tyr[0] = 0;
  tyr[1] = 0;
  tyr[2] = 1;
  tyr[3] = 1;
  adjustRelativeCoordinates();
  if(atFloor()){
    return 1;
  }
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
  drawTetromino(posX, posY, 0);
  posY = posY + 1 <= canvasOrgY + canvasHeight - tetrominoHeight ?
    posY+1 : posY;
  drawTetromino(posX, posY, 1);
}

// _____________________________________________________________________________
bool atFloor() {
  int posXrel = posX - canvasOrgX + 1;
  int posYrel = posY - canvasOrgY;
  bool floored = false;
  if (posYrel == canvasHeight - tetrominoHeight - 1) {
    floored = true;
  } else {
    for (int i = 0; i < 4; i++) {
      if(structure[posXrel+txr[i]][posYrel + tyr[i] + 1]){
        floored = true;
        break;
      }
    }
  }
  if(floored){
    for (int i = 0; i < 4; i++) {
      structure[posXrel+txr[i]][posYrel + tyr[i]] = true;
    }
  }
  return floored;

}

// _____________________________________________________________________________
int timeStep(int duration) {
  drawTetromino(posX, posY, 1);
  // allow for moves in one timestep
  for (int i = 0; i < duration/10; i++) {
    int key = getch();
    moveTetromino(key);
    if (key == 'q') { return 1; }
    if (atFloor()) {return 0;}
    usleep(10);
  }
  gravityTetromino();
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
  fflush(stdout);
  for(int x = 0; x<canvasWidth; x++)
  {
    for(int y = 0; y<canvasHeight; y++)
    {
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
  //printf("\x1b[7m");
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);
  init_pair(3, COLOR_BLACK, COLOR_RED);
  //init_pair(2, COLOR_BLACK, COLOR_RED);
  attron(COLOR_PAIR(mode + 1));
  for (int i = 0; i < 4; i++) {
    mvprintw(drawY + tyr[i], drawX + txr[i], " ", mode);
  }
  // refresh() seems not to work with cygwin under windows?
  fflush(stdout);
}

// _____________________________________________________________________________
void drawTetrominoAtFloor() {
  //mvprintw("\x1b[31m");
  drawTetromino(posX, posY, 2);
  //mvprintw("\x1b[39;49m");
  fflush(stdout);
}

