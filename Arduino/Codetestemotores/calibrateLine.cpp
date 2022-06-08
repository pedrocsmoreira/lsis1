#include "calibrateLine.h"

int mult[150][5];


void lerValores(int L1, int L2, int L3, int L4, int L5){
  int n;
  for(n = 0; n < 150; n++){
    mult[n][0] = analogRead(L1);
    mult[n][1] = analogRead(L2);
    mult[n][2] = analogRead(L3);
    mult[n][3] = analogRead(L4);
    mult[n][4] = analogRead(L5);
  }
}

int[5] verMaior(int L1, int L2, int L3, int L4, int L5){
  lerValores(int L1, int L2, int L3, int L4, int L5);
  int i, j;
  int[5] xmax;
  for(i = 0; i < 150; i++){
    for(j = 0; j < 5; j++){
      if(mult[i][j] > xmax[j]){
        xmax[j] = mult[i][j];
      }
    }
  }
  return xmax;
}

int[5] verMenor(int L1, int L2, int L3, int L4, int L5){
  lerValores(int L1, int L2, int L3, int L4, int L5);
  int i, j;
  int[5] xmin;
  for(i = 0; i < 150; i++){
    for(j = 0; j < 5; j++){
      if(mult[i][j] < xmin[j]){
        xmin[j] = mult[i][j];
      }
    }
  }
  return xmin;
}
