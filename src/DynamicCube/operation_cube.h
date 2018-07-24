// Adapted from Min's Sphere code

#ifndef OPERATION_CUBE_H
#define OPERATION_CUBE_H

#include "point_cube.h"
#include <cmath>
#include <vector>

using namespace std;

// vector operations
double dot_prod(struct point point_v1, struct point point_v2);
double dot_prod(struct point point_v1, double* v);
struct point sub(struct point point_v1, struct point point_v2);

struct point maxPoint(int N, struct point* p, double *v);

#endif
