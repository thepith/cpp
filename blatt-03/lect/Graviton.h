// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>.

#ifndef VORLESUNG_03_GRAVITON_H_
#define VORLESUNG_03_GRAVITON_H_

// Position of graviton.
extern int rowIndex;
extern int colIndex;

// Initialize screen for ncurses.
void initializeScreen();

// Show graviton.
void showGraviton();

// Move graviton.
void moveGraviton(int key);

#endif  // VORLESUNG_03_GRAVITON_H_
