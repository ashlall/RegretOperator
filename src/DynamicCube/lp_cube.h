#ifndef LP_CUBE_H
#define LP_CUBE_H

#include <glpk.h>
#include <stdio.h>
#include <stdlib.h>
#include "point_cube.h"

#include "operation.h"

/*
 * The linear programs for computing MRR
 */
double worstDirection(int index, struct point *s, struct point pt, double* &v);
//double determinant(int n, double** a);


/*
 * Compute the MRR of a given set of points
 */
double evaluateRandom(int D, int N, int K, struct point *p, struct point* S, int REPEATS, int VERBOSE);
double evaluateRandom(int D, int N, int K, struct point *p, int *maxIndex, int REPEATS, int VERBOSE);


#endif
