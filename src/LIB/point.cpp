//==========================================================================================
//Copyright 2018 ©, 2018 Minh Do, Hiep phan, Quang Nguyen, Matthew Rinker, Ashwin Lall
//
//This file is a part of the RegretOperator project.
//
//The RegretOperator project is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    The RegretOperator project is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.
//==========================================================================================


#include "point.h"

#include <iostream>
#include <stdio.h>

using namespace std;

point* read_points(char* input)
{
    FILE * c_fp;
    char filename[MAX_FILENAME_LENG];
    sprintf(filename, "%s", input);
    if ((c_fp = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Cannot open the data file %s.\n", filename);
        exit(0);
    }
    int number_of_points, dim;
    fscanf(c_fp, "%i%i", &number_of_points, &dim);

    point* point_set = new struct point[number_of_points];
    // read points line by line
    for (int i = 0; i < number_of_points; i++)
    {
        point_set[i].a = new double[dim];
        point_set[i].d = dim;
        for (int j = 0; j < dim; j++)
        {
            fscanf(c_fp, "%lf", &point_set[i].a[j]);
        }
    }
    return point_set;

}
double dot(struct point p, double* w)
{
// This struct stores a point and its component in a d-dimensional space
// Example:
// 		struct point p;

// Returns the dot product of vector p and w.
// p is the data point
// w is the tuple representing a utilify function
	double product = 0.0;
	int i;

	for(i = 0; i < p.d; ++i)
		product += p.a[i] * w[i];

	return product;
}


struct point maxPoint(int N, struct point *p, double *v)
{
// Finds farthest in direction v.
// This method is intended to find the boundary points
	int i, maxIndex = 0;
	double max = 0.0;

	for(i = 0; i < N; ++i)
		if (dot(p[i], v) > max)
		{
			maxIndex = i;
			max = dot(p[i], v);
		}

	return p[maxIndex];
}


// Prints the components of a point
double print(point p)
{
	for(int i = 0; i < p.d; ++i)
		printf("%lf ",p.a[i]);
	printf("\n");
  return 0;
}


int pointcmp(const void *a, const void *b)
{
// Compares two points lexicographically.
// Return values:
//		-1: a < b
// 		 1: a > b
// 		 0: a = b
// Example:
// 		p1(1,2,3,4,6) and p2(1,2,3,5,5)
// 		=> p1 < p2 because p1[i] = p2[i] for 1 <= i <= 3
// 		               and p1[4] < p2[4]
	int i;

	for(i = 0; i < ((struct point*)a)->d; ++i)
	{
		if (((struct point*)a)->a[i] < ((struct point*)b)->a[i]) return -1;
		if (((struct point*)a)->a[i] > ((struct point*)b)->a[i]) return 1;
	}

	return 0;
}


int dominates(struct point p1, struct point p2)
{
// Checks if p1 dominates p2
// p1 dominates p2 when p1[i] >= p2[i] for all 1 <= i <= d
	int i;

	for(i = 0; i < p1.d; ++i)
		if (p1.a[i] < p2.a[i])
			return 0;

	return 1;
}


int equals(struct point p1, struct point p2)
{
// Checks if two points are equal.
// In other words, if pointcamp returns 0.
	return pointcmp(&p1, &p2) == 0;
}
