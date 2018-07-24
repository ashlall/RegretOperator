// ==========================================================================================
// Copyright 2018 ©, 2018 Minh Do, Hiep phan, Quang, Nguyen, Matthew Rinker, Ashwin Lall
//
// This file is a part of the RegretOperator project.
//
// The RegretOperator project is free software: you can redistribute it and/or modify
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
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ==========================================================================================
// Uses the Cube "strips" Algorithm to compute the k-regret operator
// ==========================================================================================
#include "cube_dynamic.h"

#include <cmath>
#include <iostream>

using namespace std;

// This function deallocates M and B
void deallocateCube(bool deallocB, bool deallocM, int D)
{
	if (deallocB)
	{
		for (int i = 0; i < bNum; ++i)
		{
			delete B[i];
		}
		delete[] B;
		B = NULL;
	}

	if (deallocM)
	{
		for (int i = 0; i < D; ++i)
		{
			delete[] c[i].a;
			delete M[i];
		}
		delete c;
		delete[] M;
		M = NULL;
		c = NULL;

	}
}

// This function initializes for the cube algorithm
// Parameters:
// 		D       : number of dimensions
// 		N       : number of data points
//		K       : size of result set
//		p       : the dataset
//		maxIndex: used to store the indices of points in the result set
// Return:
// 		None
void dynamic_cube(int D, int N, int K, struct point *p, int *maxIndex)
{
	int i, j, t, index, L = D - 1, inCube, distinct;

	if (c == NULL)
	{
		c = new struct point[D]; // maximal points in each direction
		for (int i = 0; i < D; ++i)
		{
			c[i].d = D;
			c[i].a = new double[D];
		}
	}

	struct point answer[K + 1];

	if (M == NULL)
	{
		M = new MaxHeap*[D];
		for (i = 0; i < D; ++i)
		{
			M[i] = new MaxHeap(2.5*N,N,p,i);
		}
	}

	for (int i = 0; i < D; ++i)
		copypoint(c[i],M[i]->getmax());

	// initialize t as in the cube algorithm
	t = (int)pow(K - D + 1.0, 1.0/(D - 1.0));

	// keeps looping until finds at least K distinct points
	int limit = 2;
	do
	{
		--limit;
		if (B != NULL)
			deallocateCube(true,false,D);

		bNum = (int)pow(t,(D-1));
		B = new MaxHeap*[bNum];
		for (i = 0; i < bNum; ++i)
				B[i] = new MaxHeap(2.5*N,D,D-1);
		distinct = dynamic_cubealgorithm(D, N, K, p, L, t, c, answer);
		t++;
	}
	while(distinct < K && distinct < N && limit != 0);

	if (distinct > K)
	{
		if (B != NULL)
			deallocateCube(true,false,D);
		bNum = (int)pow(t-2,(D-1));
		B = new MaxHeap*[bNum];
		for (i = 0; i < bNum; ++i)
				B[i] = new MaxHeap(2.5*N,D,D-1);

		dynamic_cubealgorithm(D, N, K, p, L, t - 2, c, answer);
	}

	// get the indices, to be in the desired format
	for(i = 0; i < N; ++i)
		for(j = 0; j < K; ++j)
			if (equals(p[i], answer[j]))
				maxIndex[j] = i;
}

// This function is the cube algorithm
// Parameters:
// 		D: number of dimensions
// 		N: number of data points
//		K: size of result set
// 		p: the dataset
// 		L: the "ignored" dimensions aka. the one used to determine highest point in a bucket
//		   L = D - 1
// 		t: the number determining how many slices to divide a dimension
//		   t^(d-1) = number of buckets
// 		c: array storing the boundary points
// 		answer: result set
// Return:
//		The number of points found for the result set (not necessary distinct points)
int dynamic_cubealgorithm(int D, int N, int K, struct point *p, int L, int t, struct point *c, struct point *answer)
{
	int i, j, index, inCube, distinct, cubeBestIndex, done, seenBefore;
	int boundary[D]; // this is actually the offset j_i in step 4 in the pseudo-code. Confusing name!

	index = 0; // the number of points found for the result set

	for(i = 0; i < D; ++i)  // first list the maximal points in the directions {1,...,D}\L
		if (i != L)
			answer[index++] = c[i]; // lazy coding. This is the same as using index as usual then increase it by 1

	// Try all 0 <= j_1, j_2, ... < t

	for(i = 0; i < D; ++i)
		boundary[i] = 0;

	done = 0;
	int bIndex = 0;

	while(!done && index < K)
	{
		// set up bucket boundary
		B[bIndex]->setbound(boundary);
		B[bIndex]->setT(t);

		cubeBestIndex = -1;
		for(i = 0; i < N; ++i)
		{
			// determine if p[i] is in this cube
			inCube = 1;
			for(j = 0; j < D && inCube; ++j) // an ugly break condition integrated with the for loop but fast?
				if (j != L)  // not the excluded dimension
					inCube = (boundary[j] * c[j].a[j] <= t * p[i].a[j]) && (t * p[i].a[j] < (boundary[j] + 1) * c[j].a[j]);

			if (inCube)  // check if it is maximal in the missing dimension
			{
				B[bIndex]->insert(p[i]);
				if (cubeBestIndex < 0)
					cubeBestIndex = i;  // none seen yet, set to i
				else if(p[i].a[L] > p[cubeBestIndex].a[L]) //a is attribute. See point.h for more info
						cubeBestIndex = i;  // replace if larger in dimension L
			}
		}

		if (cubeBestIndex >= 0)  //If there is a point in this cube and it is distinct from earlier ones, add to list
		{
			seenBefore = 0;
			for(i = 0; i < index && !seenBefore; ++i)
				if(equals(answer[i], p[cubeBestIndex]))
					seenBefore = 1;

			if (!seenBefore)
				answer[index++] = p[cubeBestIndex];
		}


		if (L == 0) // if L==0 skip first dimension
			j = 1;
		else
			j = 0;
		boundary[j]++;
		while(boundary[j] == t && !done)
		{
			boundary[j] = 0;  // reset position

			if (j == L - 1) j += 2;  // if have reached the skipped dimension, skip it
			else            j += 1;  // else increment by 1

			if (j < D)
				boundary[j]++; // if not at the end, do the carry
			else
				done = 1;      // else indicate that all combinations tried
		}

		++bIndex;
	}

	// fill in any remaining positions with the first point found
	for(i = index; i < K; ++i)
		answer[i] = answer[0];

	return index;
}

bool contains(struct point* S, int n, struct point p)
{
	for (int i = 0; i < n; ++i)
		if (equals(S[i],p))
			return true;

	return false;
}
// 0 <= m < 1
// Return:
//		false if cube is re-run -> result is stored in 'answerIndex'
// 		true otherwise ->result is stored in 'S'
bool cube_insert(int D, int& N, int K, double m, struct point* p, struct point p_new, struct point* S, int* answerIndex)
{
	double maxDelta = -10000;
	int ansNum = 0;

	copypoint(p[N],p_new);
	p[N].id = ID;
	++ID;
	++N;

	for (int i = 0; i < D-1; ++i)
	{
		M[i]->insert(p_new);
		double delta = ((M[i]->getmax()).a[i] - c[i].a[i]) / c[i].a[i];
		if (maxDelta < delta)
			maxDelta = delta;
	}
	M[D-1]->insert(p_new); // might as well delete this;

	if (maxDelta > m)
	{
		deallocateCube(true, false, D);
		dynamic_cube(D,N,K,p,answerIndex);
		return false;
	}
	else
	{
		// add boundary points to result set
		for (int i = 0; i < D-1; ++i)
		if (!contains(S, ansNum, M[i]->getmax()))
		{
			copypoint(S[ansNum],M[i]->getmax());
			++ansNum;
		}

		bool bucketFound = false;
		for (int i = 0; i < bNum; ++i)
		{
			if (!bucketFound && B[i]->satisfy(p_new))
			{
				B[i]->insert(p_new);
				bucketFound = true;
			}

			// if bucket is not empty and max is not yet in the result set
			if (ansNum != K && !B[i]->empty() && !contains(S, ansNum, B[i]->getmax()))
			{
				copypoint(S[ansNum],B[i]->getmax());
				++ansNum;
			}
		}
	}

	if (ansNum < K)
	{
		for (int i = 0; i < bNum; ++i)
		{
			if (B[i]->heapsize >= 2)
			{
				copypoint(S[ansNum],B[i]->p[1]);
				if (B[i]->heapsize > 2 && B[i]->p[1].a[D-1] < B[i]->p[2].a[D-1])
					copypoint(S[ansNum],B[i]->p[2]);
				++ansNum;
			}
			if (ansNum == K)
				break;
		}
	}

	return true;
}

// 0 <= m < 1
// Return:
//		false if cube is re-run -> result is stored in 'answerIndex'
// 		true otherwise ->result is stored in 'S'
bool cube_delete(int D, int& N, int K, double m, struct point* p, int removIndex, struct point* S, int* answerIndex)
{
	double minDelta = 10000;
	int ansNum = 0;

	struct point p_remov;
	p_remov.d = D;
	p_remov.a = new double[D];
	copypoint(p_remov,p[removIndex]);

	for (int i = removIndex; i < N-1; ++i)
		copypoint(p[i],p[i+1]);
	--N;

	for (int i = 0; i < D-1; ++i)
	{
		M[i]->remove(p_remov);
		double delta = ((M[i]->getmax()).a[i] - c[i].a[i]) / c[i].a[i];
		if (minDelta > delta)
			minDelta = delta;
	}

	if (minDelta < -m)
	{
		deallocateCube(true, false, D);
		dynamic_cube(D,N,K,p,answerIndex);
		return false;
	}
	else
	{
			for (int i = 0; i < D-1; ++i)
			if (!contains(S, ansNum, M[i]->getmax()))
			{
				copypoint(S[ansNum], M[i]->getmax());
				++ansNum;
			}

			bool isRemoved = false;
			for (int i = 0; i < bNum; ++i)
			{
				if (!isRemoved && B[i]->satisfy(p_remov))
				{
					B[i]->remove(p_remov);
					isRemoved = true;
				}

				if (ansNum < K && !B[i]->empty() && !contains(S, ansNum, B[i]->getmax()))
				{
					copypoint(S[ansNum],B[i]->getmax());
					++ansNum;
				}
			}
	}

	if (ansNum < K)
	{
		for (int i = 0; i < bNum; ++i)
		{
			if (B[i]->heapsize >= 2)
			{
				copypoint(S[ansNum],B[i]->p[1]);
				if (B[i]->heapsize > 2 && B[i]->p[1].a[D-1] < B[i]->p[2].a[D-1])
					copypoint(S[ansNum],B[i]->p[2]);
				++ansNum;
			}
			if (ansNum == K)
				break;
		}
	}

	return true;
}

// 0 <= m < 1
// Return:
//		false if cube is re-run -> result is stored in 'answerIndex'
// 		true otherwise ->result is stored in 'S'
bool cube_delete(int D, int& N, int K, double m, struct point* p, struct point p_remove, struct point* S, int* answerIndex)
{
	double minDelta = 10000;
	int ansNum = 0;
	int removIndex = -1;

	struct point p_remov;
	p_remov.d = D;
	p_remov.a = new double[D];
	copypoint(p_remov,p_remove);

	for (int i = 0; i < N; ++i)
		if (equals(p[i],p_remove))
		{
			removIndex = i;
			break;
		}

	if (removIndex != -1)
	{
		for (int i = removIndex; i < N-1; ++i)
			copypoint(p[i],p[i+1]);
		--N;
	}

	for (int i = 0; i < D-1; ++i)
	{
		M[i]->remove(p_remov);
		double delta = ((M[i]->getmax()).a[1] - c[i].a[i]) / c[i].a[i];
		if (minDelta > delta)
			minDelta = delta;
	}

	if (minDelta < -m)
	{
		deallocateCube(true, false, D);
		dynamic_cube(D,N,K,p,answerIndex);
		return false;
	}
	else
	{
			for (int i = 0; i < bNum; ++i)
			{
				B[i]->remove(p_remov);
				if (ansNum < K && !B[i]->empty() && !contains(S, ansNum, B[i]->getmax()))
				{
					copypoint(S[ansNum],B[i]->getmax());
					++ansNum;
				}
			}

	}

	if (ansNum < K)
	{
		for (int i = 0; i < bNum; ++i)
		{
			if (B[i]->heapsize >= 2)
			{
				copypoint(S[ansNum],B[i]->p[1]);
				if (B[i]->heapsize > 2 && B[i]->p[1].a[D-1] < B[i]->p[2].a[D-1])
					copypoint(S[ansNum],B[i]->p[2]);
				++ansNum;
			}
			if (ansNum == K)
				break;
		}
	}

	return true;
}
