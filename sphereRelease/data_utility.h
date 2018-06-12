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

#ifndef DATA_UTILITY_H
#define DATA_UTILITY_H

#include<math.h>
#include<float.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include <vector>
#include <iostream>
#include <iterator>

#define COORD_TYPE            double
#define DIST_TYPE             double
#define PI                    3.1415926
#define INF                   100000000
#define MAX_FILENAME_LENG     256
#define EQN_EPS               1e-9


// data structure for storing points.
typedef struct point
{
    int            dim;      //dimension of the point
    COORD_TYPE*    coord;
    int            id;

}point_t;

// data structure for storing point set.
typedef struct point_set
{
    int numberOfPoints;
    point_t **points;    //iterator?
} point_set_t;

// data structure for computing catersian product
typedef std::vector<double> Vi;
typedef std::vector<Vi> Vvi;

// point & point_set manipulation ?
point_t* alloc_point(int dim);
point_t* alloc_point(int dim, int id);
void release_point( point_t* &point_v);
point_set_t* alloc_point_set(int numberOfPoints);
void release_point_set(point_set_t* &point_set_v, bool clear);
void print_point(point_t* point_v);
void print_point_set(point_set_t* point_set_v);

#endif
