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

#ifndef REGRETOPERATOR_SRC_NAIVEGREEDY_NAIVEGREEDY_H_
#define REGRETOPERATOR_SRC_NAIVEGREEDY_NAIVEGREEDY_H_

int pointcmp(const void *a, const void *b);
double L2Distance(struct point p, struct point q);
double CenterDistance(int index, struct point *sol, struct point p);
void NaiveGreedy(int D, int N, int K, struct point *p, int *maxIndex);
#endif
