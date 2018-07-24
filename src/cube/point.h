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


#ifndef REGRETOPERATOR_SRC_POINT_H_
#define REGRETOPERATOR_SRC_POINT_H_

#define MAXDIM 20
#define MAX_FILENAME_LENG     256

struct point
{
    int d;
    double* a;
};

double dot(struct point, double*);
struct point maxPoint(int, struct point*, double*);
double print(point);
void sort(struct point*, int);
int equals(struct point, struct point);
int dominates(struct point, struct point);
point* read_points(char * input);
point* readPoints(char filename[]);
int pointcmp(const void *a, const void *b);

// point* read_points(char* input);
#endif
