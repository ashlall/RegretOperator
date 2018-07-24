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


#ifndef REGRETOPERATOR_SRC_POINT_H_
#define REGRETOPERATOR_SRC_POINT_H_

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct point
{
	int id;
    int d;
    double* a;
};

void allocateData(int N, int D, struct point* p);
void deallocateData(int N, int D, struct point* p);
void readInput(int &N, int& ID, string filename, struct point* p);
void toCStr(char* cstr, string str);
void sortData(struct point* p, int first, int last);
string sort(int n, double* a);

double dot(struct point, double*);
double print(struct point);

void copypoint(struct point& p, struct point& q);
int equals(struct point, struct point);
int dominates(struct point, struct point);
int pointcmp(struct point a, struct point b);

#endif
