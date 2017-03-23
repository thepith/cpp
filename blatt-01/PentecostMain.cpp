// Copyright 2017, Pascal Hebbeker

#include <stdio.h>
#include <stdlib.h>
#include "./Pentecost.cpp"

// Main function, allows for calulation of date of Pentecost
int main(int argc, char** argv) {
  // printf("Number of command line arguments: %d\n", argc);
  if (argc != 2) {
    printf("Usage: ./Pentecost <Year>\n");
    exit(1);
  }
  int year = atoi(argv[1]);

  int date = DayOfPentecost(year);
  printf("In the year %d Pentecost (Monday) will be %d days after the 30th of April.\n",
        year, date);
}
