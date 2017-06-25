// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>,

#ifndef VORLESUNG_05_TETRIS_H_
#define VORLESUNG_05_TETRIS_H_

// Absolute position of the tetromino.
extern int tx;
extern int ty;

// Relative position of the four cells of the tetromino.
extern int txr[4];
extern int tyr[4];

// Initialize terminal for ncurses.
void initTerminal();

// Move the tetromino according to the given key.
// NOTE: with a clever choise of addinitional arguments, you can use the same
// function to undo the move in case the tetromino is colliding with the border
// or the structure.
void moveTetromino(int key, bool reverse);

// Rotate the tetromino by the given multiple of 90 degrees to the right.
// NOTE: This is easy using the rotation matrix explained in the lecture.
void rotateTetromino(int n);

// Draw a single cell with the given attributes.
void showCell(int x, int y, int attr);

// Draw the Tetromino at its current position (in black).
void showTetromino();

#endif  // VORLESUNG_05_TETRIS_H_
