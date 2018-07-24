#include "sphere.h"
#include "data_utility.h"
#include "LIB_Util.h"
#include "point.h"
#include "operation.h"
#include "lp.h"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char * argv[]){
  // char * input_A = argv[1];
  // char * input_C = argv[2];
  // char * input_E = argv[3];

  char filename_A[1024];
  char filename_C[1024];
  char filename_E[1024];

  struct point * pA;
  struct point * pC;
  struct point * pE;

  sprintf(filename_A, "%s", argv[1]);
  sprintf(filename_C, "%s", argv[2]);
  sprintf(filename_E, "%s", argv[3]);

  pA = readPoints(filename_A);
  pC = readPoints(filename_C);
  pE = readPoints(filename_E);

  int D = 4;
  int N = 10000;
  int db = 2;
  pA = scale(D,pA,N);
  pC = scale(D,pC,N);
  pE = scale(D,pE,N);

  pA = transformforth(db,D,pA,N);
  pC = transformforth(db,D,pC,N);
  pE = transformforth(db,D,pE,N);

  point_set_t * PA = Cube2Sphere(D,pA,N);
  point_set_t * PC = Cube2Sphere(D,pC,N);
  point_set_t * PE = Cube2Sphere(D,pE,N);

  point_set_t* skylineA = skyline_point(PA);
  point_set_t* skylineC = skyline_point(PC);
  point_set_t* skylineE = skyline_point(PE);



  cout <<"A:" <<skylineA->numberOfPoints << endl;
  cout << "C:"<< skylineC->numberOfPoints << endl;
  cout << "E:" << skylineE->numberOfPoints << endl;
  return 0;

}
