#ifndef LIB_UTIL
#define LIB_UTIL

#include <stdlib.h>
#include <iostream>
#include "point.h"
#include "glpk.h"
// #include "data_utility.h"
using namespace std;


point*  scale(int D, struct point* p, int N);

point* transformforth(int db, int D, struct point *p, int N);

point* transformback(int db, int D, struct point *p, int N);

// double evaluateRandomLIB(point_set_t* p, point_set_t* S,int REPEATS, int VERBOSE, double M);

double evaluateRandomLIB(int D, int N, int K, struct point *p, int *maxIndex, int LIB, int db, int REPEATS, int VERBOSE, double M);

// double evaluateLPLIB(point_set_t *p, point_set_t* S, int VERBOSE, double M);

double evaluateLPLIB(int D, int N, int K, struct point *p, int *maxIndex, int VERBOSE, double M);

double worstDirection(int K, int D, struct point* s, struct point pt, double v[MAXDIM]);


#endif
