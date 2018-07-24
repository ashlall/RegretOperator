#ifndef LIB_UTIL
#define LIB_UTIL

#include <stdlib.h>
#include <iostream>
#include "point.h"
#include "glpk.h"
#include "data_utility.h"
using namespace std;

point_set_t* Cube2Sphere(int D, struct point* p, int N);

point* Sphere2Cube(int D, point_set_t * P, int N);

point*  scale(int D, struct point* p, int N);

point* transformforth(int db, int D, struct point *p, int N);

point* transformback(int db, int D, struct point *p, int N);

double evaluateRandomLIB(int D, int N, int K, struct point *p, int *maxIndex, int LIB, int db, int REPEATS, int VERBOSE, double M);


#endif
