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

  while (true) {
    drawTetromino(posX, posY, true);
    int key = getch();
    //int posoldX = posX;
    //int posoldY = posY;
    moveTetromino(key);
    if (key == 'q') { break; }
    //if(posoldX != posX | posoldY != posY){
      //drawtetromino(posoldx, posoldy, false);
      //drawTetromino(posX, posY, true);
      //usleep(1000);
      //refresh();
    //}
  }
  endwin();
}
