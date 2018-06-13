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
//Algorithm for picking representative skylines using Yufei Tao's naive-greedy algorithm
//   Implemented by Danupon Nanongkai, Nov. 15, 2009

#include "naive-greedy.h"

#include <iostream>

using namespace std;

struct point {
int d;       // number of dimensions
double* a;   // array of attributes
};

int pointcmp(const void *a, const void *b) 
//Compares the values of two points together. Returnes an Integer with value 1,0,-1
//-1 if a<b
//1 if a>b
//0 if they are the same
{
	int i;

	for(i = 0; i < ((struct point*)a)->d; ++i)
	{ 
		if (((struct point*)a)->a[i] < ((struct point*)b)->a[i]) return -1;
		if (((struct point*)a)->a[i] > ((struct point*)b)->a[i]) return 1;
	}

	return 0;
}



double L2Distance(struct point p, struct point q) 
//Calculates the L_2 distance between two points
{
  double sum=0; 
  int i; 
  for (i=0; i<p.d; ++i)
      sum+=(p.a[i]-q.a[i])*(p.a[i]-q.a[i]); 
  return sum;  // no need for sqrt
}




double CenterDistance(int index, struct point *sol, struct point p) 
//Calculates the distance from a point p to the closest center in sol
{
       double mindist=10000; 
       int i;
       for (i=0; i<index; i++) 
         if (L2Distance(sol[i], p) <mindist) 
           mindist=L2Distance(sol[i], p); 
       return mindist;
}


// Note: We assume that the inpun is a skyline. Otherwise, one should compute skyline first

void NaiveGreedy(int D, int N, int K, struct point *p, int *maxIndex)
{
//Conducts a k-Regret query using the Naive-Greedy Algoirthm
//Inputs:
//D = # of dimensions
//N = # of points in Database
//K = # of points to return

    int i, j;
//    double v[D]; 
    struct point sol[K]; 
	double epsilon = 0.0000001;
	double dist, d;
	struct point max;
    int numpoint=1; // Number of points collected so far.

	if (K < 1)
	{
		cout<< "naive-greedy requires K to be greater than 0." << endl;
		return; 
	}
    
    // Start with an arbitrary point
	sol[0]=p[0]; 
    int index = 1;
    
    
    // Add more points
    while (index < K) 
	{
          // Find a point with maximum distance from the centers in sol
          max = p[0]; 
          dist = CenterDistance(index, sol, max); 
          for (i = 1; i < N; i++) 
		  {
              d = CenterDistance(index, sol, p[i]);
              if (dist<d) 
			  {
				  dist = d;
				  max = p[i]; 
              }
          }

          // Add a point if max distance > 0. Otherwise, stop.
          if (dist >= 0.0 + epsilon) 
			  sol[index++]=max; 
          else 
			  break;  
    }
    
    // get the indices, to be in the desired format
	for(i = 0; i < N; ++i)
		for(j = 0; j < index; ++j)
			if (pointcmp(&(p[i]), &(sol[j])) == 0)
				maxIndex[j] = i;
	
	// fill in any remaining points with the first point
	for(j = index; j < K; ++j)
		maxIndex[j] = maxIndex[0];
}



int main()
{
    // TEST: This test should output (1, 0) and (0, 1)
    
    
    // Define 3 points: (1, 0), (0.6, 0.6), and (0, 1)
    struct point s[3]; 
    s[0].d=2; 
    s[0].a=new double;
    s[0].a[0]=1; 
    s[0].a[1]=0; 

    s[1].d=2; 
    s[1].a=new double;
    s[1].a[0]=0.6; 
    s[1].a[1]=0.6;
    
    s[2].d=2; 
    s[2].a=new double;
    s[2].a[0]=0; 
    s[2].a[1]=1;     
    
    int maxIndex[3];
    
    
    // Find 2 representative points
    NaiveGreedy(2, 3, 2, s, maxIndex);
    
    // Output
    
    cout<< ("first point is (%lf, %lf)\n", s[maxIndex[0]].a[0], s[maxIndex[0]].a[0]); 
    cout<< ("first point is (%lf, %lf)\n", s[maxIndex[1]].a[0], s[maxIndex[1]].a[0]); 
    
    return 0;
}

