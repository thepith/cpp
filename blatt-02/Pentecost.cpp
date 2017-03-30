// Copyright 2017, Pascal Hebbeker


#include "../blatt-02/Pentecost.h"

// _____________________________________________________________________________
int DayOfPentecost(int year) {
  int K = year/100;
  int M = 15 + (3*K + 3)/4 - (8*K +12)/25;
  int S = 2 - (3*K + 3)/4;
  int A = year % 19;
  int D = (19*A + M) %30;
  int R = (D + A/11)/29;
  int OG = 21 + D - R;
  int SZ = 7 - (year + year/4 + S)%7;
  int OE = 7 - (OG - SZ) % 7;
  int OS = OG + OE;  // easter in days in march
  int Pentecost = OS + 50;  // Pentacost (Monday) is 50 days after easter
  int Pentecost_May = Pentecost - 61;  // convert days in march to days in may
  return Pentecost_May;
}

