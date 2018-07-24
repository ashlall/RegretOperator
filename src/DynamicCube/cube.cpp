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
//Uses the Cube "strips" Algorithm to compute the k-regret operator
//==========================================================================================
#include "cube.h"

#include <cmath>

#include <iostream>

using namespace std;

//==========================================================================================
//Constructor for the cube object
//D = # of dimensions
//N = # of points in P
//K = # of points to return
//==========================================================================================
void cube(int D, int N, int K, struct point *p, int *maxIndex)
{
	int i, j, t, index, L = D - 1, inCube, distinct;
	struct point c[D]; // maximal points in each direction
	struct point answer[K + 1];

	// compute the maximal points in each of the D directions
	for(i = 0; i < D; ++i)
		c[i] = p[0]; // initialize with first point
	for(i = 0; i < N; ++i) //Find maximal points in each direction
		for(j = 0; j < D; ++j)
			if (p[i].a[j] > c[j].a[j])
				c[j] = p[i];

	//initialize t as in the cube algorithm
	t = (int)pow(K - D + 1.0, 1.0/(D - 1.0));

	//keeps looping until finds at least K distinct points 
	do
	{
		distinct = cubealgorithm(D, N, K, p, L, t, c, answer);
		t++;
	}
	while(distinct < K && distinct < N);

	if (distinct > K)
		cubealgorithm(D, N, K, p, L, t - 2, c, answer);
	//get the indices, to be in the desired format
	for(i = 0; i < N; ++i) 
		for(j = 0; j < K; ++j)
			if (equals(p[i], answer[j])) 
				maxIndex[j] = i;
}	

//==========================================================================================
//Executes the cube algorithm using a cube object
//D = # of dimensions
//N = # of points in P
//K = # of point to return
//L = D-1st dimension (Last Dimension)
//==========================================================================================
int cubealgorithm(int D, int N, int K, struct point *p, int L, int t, struct point *c, struct point *answer)
{
	int i, j, index, inCube, distinct, cubeBestIndex, done, seenBefore;
	int boundary[D]; //this is actually the offset j_i in step 4 in the pseudo-code. Confusing name!

	index = 0;
	
	for(i = 0; i < D; ++i)  //first list the maximal points in the directions {1,...,D}\L
		if (i != L)
			answer[index++] = c[i]; 
				
	//Try all 0 <= j_1, j_2, \ldots < t 
	
	for(i = 0; i < D; ++i)  //initialize to all zeros
		boundary[i] = 0;
		
	done = 0;
	
	while(!done && index < K)
	{
		//pick the maximal point in current cube
		cubeBestIndex = -1;
		for(i = 0; i < N; ++i)
		{
			//determine if p[i] is in this cube
			inCube = 1;
			for(j = 0; j < D && inCube; ++j) //an ugly break condition integrated with the for loop but fast?
				if (j != L)  //not the excluded dimension
					inCube = (boundary[j] * c[j].a[j] <= t * p[i].a[j]) && (t * p[i].a[j] < (boundary[j] + 1) * c[j].a[j]); 
			
			if (inCube)  //check if it is maximal in the missing dimension
				if (cubeBestIndex < 0)
					cubeBestIndex = i;  //none seen yet, set to i
				else if(p[i].a[L] > p[cubeBestIndex].a[L]) //a is attribute. See point.h for more info
						cubeBestIndex = i;  //replace if larger in dimension L
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
		

		if (L == 0) //If L==0 skip first dimension
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
	}

	// fill in any remaining positions with the first point found
	for(i = index; i < K; ++i)
		answer[i] = answer[0];

	return index;
}


