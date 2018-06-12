/* Algorithm using the cube "strips" method */

#include "cube.h"
#include <cmath>
#include <iostream>

using namespace std;

void cube(int D, int N, int K, struct point *p, int *maxIndex) //N should be the number of points in struct p
{
	int i, j, t, index, L = D - 1, inCube, distinct;
	struct point c[D]; // maximal points in each direction
	struct point answer[K + 1]; //Why is this K + 1?

	// compute the maximal points in each of the D directions
	for(i = 0; i < D; ++i)
		c[i] = p[0]; // initialize with first point
	for(i = 0; i < N; ++i) //Find maximal points in each direction
		for(j = 0; j < D; ++j)
			if (p[i].a[j] > c[j].a[j])
				c[j] = p[i];

	// initialize t as in the cube algorithm
	t = (int)pow(K - D + 1.0, 1.0/(D - 1.0));

	// keep looping until we find at least K distinct points 
	do
	{

		distinct = cubealgorithm(D, N, K, p, L, t, c, answer); //What's L?
		t++;
	}
	while(distinct < K && distinct < N);

	if (distinct > K)
		cubealgorithm(D, N, K, p, L, t - 2, c, answer); //Does this necessarily solve the issue? I bet there's an edge case in which this doesn't find the correct number of points
	// get the indices, to be in the desired format
	for(i = 0; i < N; ++i) //Ok, apparently we need the MaxIndex to evaluate the linear program, but why is that? I wanna check that one out.
		for(j = 0; j < K; ++j)
			if (equals(p[i], answer[j])) 
				maxIndex[j] = i;
}	

int cubealgorithm(int D, int N, int K, struct point *p, int L, int t, struct point *c, struct point *answer) //What's L? ANSWER: It's the (D - 1) dimension, as in, the last dimension, which is excluded.
{
	int i, j, index, inCube, distinct, cubeBestIndex, done, seenBefore;
	int boundary[D];

	index = 0;
	// first list the maximal points in the directions {1,...,D}\L
	for(i = 0; i < D; ++i)
		if (i != L)
			answer[index++] = c[i]; //This just smacks of "undefined behavior". Index++? You're not even using it in the loop. I would be careful. Check when that expression evaluates, then try and understand what the heck this is.
				
	/*** Try all 0 <= j_1, j_2, \ldots < t ***/
	
	// initialize to all zeros
	for(i = 0; i < D; ++i)
		boundary[i] = 0;
		
	//If L == 0, you can probably skip this whole next part
	
	done = 0; //Ok, so done is essentially a bool variable, but those don't exist in C, so they just used an int--Correction, bool's exist, they just require you to include stdbool.h, so I dunno if it's worth switching the code just for a bit of clarity
	while(!done && index < K)
	{
		// pick the maximal point in current cube
		cubeBestIndex = -1; //Negative indexing is not allowed, as this would be in Python, so this is currently an undefined pointer. Ish. You know what I mean, right?
		for(i = 0; i < N; ++i)
		{
			// determine if p[i] is in this cube
			inCube = 1;
			for(j = 0; j < D && inCube; ++j)
				if (j != L)  // not the excluded dimension
					inCube = (boundary[j] * c[j].a[j] <= t * p[i].a[j]) && (t * p[i].a[j] < (boundary[j] + 1) * c[j].a[j]); //Just note that 'boundary[i]' should be initialized to zero still, so that affects these terms pretty radically. So, based on this, is the 'boundary' term just literally a set of 0's that the program uses to check for something being in the Cube or not? So, basically, it's just a bit of cute syntax to assist understanding, when it could just literally say '0'. I think. Double check?
			
			if (inCube)  // check if it is maximal in the missing dimension
				if (cubeBestIndex < 0)
					cubeBestIndex = i;  // none seen yet, set to i
				else if(p[i].a[L] > p[cubeBestIndex].a[L])
						cubeBestIndex = i; // replace if larger in dimension L
		}
		
		// If there is a point in this cube and it is distinct from earlier ones, add to list
		if (cubeBestIndex >= 0)
		{
			seenBefore = 0; 
			for(i = 0; i < index && !seenBefore; ++i)
				if(equals(answer[i], p[cubeBestIndex]))
					seenBefore = 1;
				
			if (!seenBefore)
				answer[index++] = p[cubeBestIndex];
		}
		
		
		// increment t-ary counter
		if (L == 0) // if we're skipping 0th dimension, start at 1
			j = 1; 
		else 
			j = 0; 
		boundary[j]++; 
		while(boundary[j] == t && !done)
		{
			boundary[j] = 0;  // reset position 
			
			if (j == L - 1) j += 2;  // if we reach the skipped dimension, skip it
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


