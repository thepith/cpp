// Copyright 2017, Pascal Hebbeker

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

// Include header files
#include "./Tetrominos.h"

// Main function
int main(int argc, char** argv) {
  initScreen();
  positionTetrominosAtTop();
  while (true) {
    if (timeStep(3000) == 1) {break;}
    if (atFloor()) {
      drawTetrominoAtFloor();
      int playing = positionTetrominosAtTop();
      if(playing != 0){
        return 0;
      }
    }
  }
  endwin();
}
