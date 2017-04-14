// Copyright 2017, Pascal Hebbeker

#ifndef BLATT_03_TETROMINOS_H_
#define BLATT_03_TETROMINOS_H_

// position of tetrominon
extern int posX;
extern int posY;

// Tetromino Dimensions
extern int tetrominoWidth;
extern int tetrominoHeight;

// Canvas Dimensions
extern int canvasWidth;
extern int canvasHeight;
extern int canvasOrgX;
extern int canvasOrgY;

// How far to move down
extern int downStep;

// Move a Tetromino accoding to key
void moveTetromino(int);

// position Tetromino at the Top
int positionTetrominosAtTop();

// rotate Tetrominos
void rotateTetromino();

// Move a Tetromino due to gravity
void gravityTetromino();

// check if Tetromino is at floor
bool atFloor();

// Perform one step
int timeStep(int);

// Handle the Floor
int handleFloor();

// Initializes the Screen
void initScreen();

// Draws a Tetromino at a given position
void drawTetromino(int, int, int);

// Draws a floored Tetromino at a given position
void drawTetrominoAtFloor();

// Draws a T Tetromino at a given position
void drawTetrominoT(int, int, int);

#endif  // BLATT_03_TETROMINOS_H_
