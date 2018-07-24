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

#ifndef DYNAMIC_CUBE_H_
#define DYNAMIC_CUBE_H_

#include "lp_cube.h"
#include "operation_cube.h"
#include "point_cube.h"
#include "maxheap.h"

extern MaxHeap** M;
extern MaxHeap** B;
extern int bNum;
extern struct point* c;
extern int ID; // This is a unique id for a point to speed up the removing process

void deallocateCube(bool deallocB, bool deallocM, int D);
bool contains(struct point* S, int n, struct point p);

void dynamic_cube(int D, int N, int K, struct point *p, int *maxIndex);
int dynamic_cubealgorithm(int D, int N, int K, struct point *p, int L, int t, struct point *c, struct point *answer);

bool cube_insert(int D, int& N, int K, double m, struct point* p, struct point p_new, struct point* S, int* answerIndex);
bool cube_delete(int D, int& N, int K, double m, struct point* p, int removIndex, struct point* S, int* answerIndex);
bool cube_delete(int D, int& N, int K, double m, struct point* p, struct point p_remove, struct point* S, int* answerIndex);

#endif
