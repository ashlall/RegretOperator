//==========================================================================================
//Copyright 2018 ©, 2018 Minh Do, Hiep phan, Quang, Nguyen, Matthew Rinker, Ashwin Lall
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

//#include "stdafx.h"

#include "operation_cube.h"

/*
 *    Calculate the dot product between two points
 */
double dot_prod(struct point point_v1, struct point point_v2)
{
    int dim = point_v1.d;
    double result = 0;

    int i;
    for(i = 0; i < dim; i++)
    {
        result += point_v1.a[i]*point_v2.a[i];
    }
    return result;
}

double dot_prod(struct point point_v1, double* v)
{
    int dim = point_v1.d;
    double result = 0;

    int i;
    for(i = 0; i < dim; i++)
    {
        result += point_v1.a[i]*v[i];
    }
    return result;
}

/*
 *    Calculate the subtraction between two points.
 */
struct point sub(struct point point_v1, struct point point_v2)
{
    struct point result;
    result.d = point_v1.d;
    result.a = new double[result.d];

    int i;
    for(i = 0; i < point_v1.d; i++)
    {
        result.a[i] = point_v1.a[i] - point_v2.a[i];
    }
    return result;
}

/*
 *  Find the point in p farthest in the direction v
 */
struct point maxPoint(int N, struct point* p, double *v)
{
    int i, maxIndex = 0;
    double max = 0.0;

    for(i = 0; i < N; ++i)
        if (dot_prod(p[i], v) > max)
        {
            maxIndex = i;
            max = dot_prod(p[i], v);
        }

    return p[maxIndex];
}
