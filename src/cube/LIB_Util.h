#ifndef LIB_UTIL
#define LIB_UTIL

#include <stdlib.h>
#include <iostream>
#include "point.h"

using namespace std;

point*  scale(int D, struct point* p, int N);

point* transformforth(int db, int D, struct point *p, int N);

point* transformback(int db, int D, struct point *p, int N);

//double regret(int D, struct point *p, int N);
#endif
