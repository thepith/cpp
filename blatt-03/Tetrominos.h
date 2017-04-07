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

// Calculate the Pentacost date according to the gauss formula.
// see https://de.wikipedia.org/wiki/Gau%C3%9Fsche_Osterformel
// Returns the number days after the 30.th of April. Takes a year as an input.
int moveTetromino(int);

// Initializes the Screen
void initScreen();

// Draws a Tetromino at a given position
void drawTetromino(int, int, bool);

// Draws a T Tetromino at a given position
void drawTetrominoT(int, int, bool);

#endif  // BLATT_03_TETROMINOS_H_
