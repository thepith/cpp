// Copyright 2017, Pascal Hebbeker


#ifndef BLATT_05_TETRIS_H_
#define BLATT_05_TETRIS_H_

class Tetris {
 public:
  // Destructor doing cleanup.
  ~Tetris();

  // Initialize terminal for ncurses.
  void initTerminal();

  // Game logic
  void play();

  // Draw a single cell with the given attributes.
  static void showCell(int x, int y, int attr);
};

/* // Initialize terminal for ncurses. */
/* void initTerminal(); */

/* // Move the tetromino according to the given key. */
/* // NOTE: with a clever choise of addinitional arguments, you can use the same */
/* // function to undo the move in case the tetromino is colliding with the border */
/* // or the structure. */
/* void moveTetromino(int key, bool reverse); */

/* // Rotate the tetromino by the given multiple of 90 degrees to the right. */
/* // NOTE: This is easy using the rotation matrix explained in the lecture. */
/* void rotateTetromino(int n); */

/* // Draw a single cell with the given attributes. */
/* void showCell(int x, int y, int attr); */

/* // Draw the Tetromino at its current position (in black). */
/* void showTetromino(); */

/* class Tetris { */
/*  public: */
/*   // Destructor doing cleanup. */
/*   ~Tetris(); */

/*   // Initialize terminal for ncurses. */
/*   void initTerminal(); */

/*   // Game logic */
/*   void play(); */

/*   // Draw a single cell with the given attributes. */
/*   static void showCell(int x, int y, int attr); */
/* }; */

#endif  // BLATT_05_TETRIS_H_
