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

// This struct stores a point and its component in a d-dimensional space
// Example:
// 		struct point p;

#include "point_cube.h"

#include <iostream>
#include <stdio.h>

using namespace std;

double dot(struct point p, double* w)
{
// Returns the dot product of vector p and w.
// p is the data point
// w is the tuple representing a utilify function
	double product = 0.0;
	int i;

	for(i = 0; i < p.d; ++i)
		product += p.a[i] * w[i];

	return product;
}

// Prints the components of a point
double print(struct point p)
{
	int i;
	for(i = 0; i < p.d; ++i)
		printf("%lf ", p.a[i]);
	printf("\n");

	return 0;

}


int pointcmp(struct point a, struct point b)
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

	for(i = 0; i < a.d; ++i)
	{
		if (a.a[i] < b.a[i]) return -1;
		if (a.a[i] > b.a[i]) return 1;
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
	return pointcmp(p1, p2) == 0;
}

void copypoint(struct point& p, struct point& q)
{
	p.id = q.id;
	p.d = q.d;
	for (int i = 0; i < p.d; ++i)
		p.a[i] = q.a[i];
}

void sortData(struct point* p, int first, int last)
{
  srand(time(NULL));
  int i = first;
  int j = last;
  int k = rand() % (last - first + 1) + first;
  while (i < last && pointcmp(p[i],p[k]) == -1)
    ++i;
  while (j > first && pointcmp(p[j],p[k]) == 1)
    --j;
  if (i <= j)
  {
    struct point t;
    t.d = p[0].d;
    t.a = new double[t.d];
    copypoint(t,p[i]);
    copypoint(p[i],p[j]);
    copypoint(p[j],t);
    delete[] t.a;
    ++i;
    --j;
  }
  if (first < j)
    sortData(p,first,j);
  if (i < last)
    sortData(p,i,last);
}

void allocateData(int N, int D, struct point* p)
{
  for (int i = 0; i < N; ++i)
  {
    p[i].d = D;
    for (int j = 0; j < D; ++j)
      p[i].a = new double[D];
  }
}

void deallocateData(int N, int D, struct point* p)
{
  for (int i = 0; i < N; ++i)
  {
    delete[] p[i].a;
  }
}

void readInput(int &N, int& ID, string filename, struct point* p)
{
  ifstream file(filename);
  int D;
  file >> N;
  file >> D;

  for (int i = 0; i < N; ++i)
  {
  	p[i].id = ID;
		++ID;
    for (int j = 0; j < D; ++j)
      file >> p[i].a[j];
  }

  file.close();
}

void toCStr(char* cstr, string str)
{
  for (int i = 0; i < str.length(); ++i)
    cstr[i] = str[i];
  cstr[str.length()] = 0;
}

string sort(int n, double* a)
{
  double sum = 0.0;
  for (int i = 0; i < n; ++i)
    sum += a[i];
  sum /= n;

  int min = 0;
  for (int i = 0; i < n-1; ++i)
  {
    min = i;
    for (int j = i+1; j < n; ++j)
    if (a[min] > a[j])
    {
      min = j;
    }

    if (min != i)
    {
      double t = a[i];
      a[i] = a[min];
      a[min] = t;
    }
  }

  ostringstream file;
  file << sum << ' ';
  file << a[0] << ' ';
  file << a[n/4] << ' ';
  file << a[n/2] << ' ';
  file << a[n*3/4] << ' ';
  file << a[n-1] << endl;

  return file.str();
}
