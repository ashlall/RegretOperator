#include <iostream>
#include <stdlib.h>

// #include "readpoints.c"
#include "LIB_Util.h"
#include "point.h"
#include "cube.h"
// #include "data_utility.h"

using namespace std;


void testScaleTransform(){
  cout<< "testScaleTransform" << endl;
  struct point* p = new struct point[5];
  double a [5][5] = {{1,2,3,4,5},
                    {5,4,3,2,1},
                    {6,7,8,9,0},
                    {0,7,8,9,6},
                    {3,4,5,6,7}};

  for(int i = 0;i<5;i++)
  {
    p[i].a = a[i];
    p[i].d = 5;
  }
  p = scale(5,p,5);
  for(int i = 0;i<5;i++)
  {
    print(p[i]);
  }
  cout << "=============================================" << endl;
  p = transformforth(2, 5, p, 5);
  for(int i = 0;i<5;i++)
  {
    print(p[i]);
  }
  cout << "=============================================" << endl;
  p = transformback(2, 5, p, 5);
  for(int i = 0;i<5;i++)
  {
    print(p[i]);
  }
  cout << "=============================================" << endl;
}

int main(int argc, char* argv[])
{
  //  testScaleTransform();

  // if (argc < 3)
  //   return 0;
  char * input = argv[1];
  cout << "===================================TESTING===================================" << endl;

  point* P = read_points(input);


  int K = atoi (argv[2]);
  int* S = new int[K];
  int* SPrime = new int[K];
  int D = P[0].d;
  int N = 10000;
  int VERBOSE = 0;
  int LIB = 1;
  int BIB = 0;
  int db = D/2;
  int numUF = 1000;
  double M = 0.5;
  // cout << M << endl;
  cube(D, N,K, P, S);
  double RRM_er = evaluateRandomLIB(D, N, K, P, S, numUF,LIB, db, VERBOSE, M);
  cout << "Regret ratio from evaluateRandomLIB before transformforth:  " <<RRM_er<< endl;

  point* PPrime = new struct point[N];
  for(int i = 0;i<10000;i++)
  {
    PPrime[i].a = new double[D];
    PPrime[i].d = D;
  }

  PPrime = scale(D,P,N);
  PPrime = transformforth(db, D, PPrime, N);

  cube(D, N,K, PPrime,SPrime);
  RRM_er = evaluateRandomLIB(D, N, K, PPrime, SPrime, numUF, BIB, db, VERBOSE, M);
  cout << "Regret ratio from evaluateRandomLIB after tranformforth:  " <<RRM_er<< endl;

  return 0;
}
