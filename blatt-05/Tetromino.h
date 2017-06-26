// Copyright 2017, Pascal Hebbeker


// Class for the tetromino.
class Tetromino {
  friend class Structure;
 public:
  // Initialise a new tetromino for given type.
  // NOTE: just call using (lrand48() % 7).
  void set(int n);

  // Move the tetromino according to the given key.
  void move(int key, bool reverse);

  // Draw the current tetromino (not in red).
  void show();


 private:
  // Rotate the tetromino by the given multiple of 90 degrees to the right.
  void rotate(int n);

  // Absolute position of the Tetromino.
  int x;
  int y;

  // Relative positions of the four parts of the Tetromino.
  int xr[4];
  int yr[4];


  // All 7 Tetrominos in default rotation.
  static int _tetrominoStructures[7][4][2];
};
