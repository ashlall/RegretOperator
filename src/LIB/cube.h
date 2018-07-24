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

#ifndef REGRETOPERATOR_SRC_CUBE_CUBE_H_
#define REGRETOPERATOR_SRC_CUBE_CUBE_H_

#include "point.h"
#include <cmath>

void cube(int D, int N, int K, struct point *p, int *maxIndex);
int cubealgorithm(int D, int N, int K, struct point *p, int L, int t, struct point *c, struct point *answer);

#endif
