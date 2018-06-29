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
//
//===================================================================
// This function implements the approximate algorithm for retrieving
// max-dominance representative skyline (Algorithm 1 in Lin et al. [ICDE'07])
// Coded by Danupon Nanongkai Nov. 16, 2009 
// MaxDom.cpp
//===================================================================

/***************
 Real code
 ***************/

/*
bool dominate(struct point p, struct point q) 
{
     int count=0; 
     for (int i=0; i<p.d; ++i)
        if (p.a[i]<q.a[i]) 
          return false; 
     return true; 
}
*/

#include "MaxDom.h"
#include "point.h"
#include <iostream>

using namespace std;

// This is Algorithm 1 in Lin et al. 
//  Input:  
//          D: dimension
//          N: number of points in the database
//          K: the desired representative size
//          s: points in the database
//          skylineSize: size of skyline
//          sky: skyline points
//   Output:
//          maxIndex: indices (of sky) of the representative points
void dominance_greedy(int D, int N, int K, struct point *s, int skylineSize, struct point *sky, int *maxIndex) {
    int i, j; 
    int index=0; 
    int killed[N]; // Points dominated by skyline
    
    for (i=0; i<N; i++) 
      killed[i]=0; 
    
    
    for (index=0; index<K; index++) {
      // Each iteration, add the point that dominates most points
      int max=0; 
      int imax=0; 
      for (i=0; i<skylineSize; ++i) {
          // Count the number of not-yet-dominated points that sky[i] dominates
          int count=0; 
          for (j=0; j<N; ++j) 
              if ((!killed[j])&&(dominates(sky[i], s[j])))
                 ++count;
                 
          if (count>max) {
             max=count; 
             imax=i; 
          }
      }
      
      // Add the remaining dominated points
      maxIndex[index]=imax;

      for (j=0; j<N; ++j) 
          if ((!killed[j])&&(dominates(sky[imax], s[j])))
            killed[j]=1; 
    }        
}

/*
int main()
{
    // TEST: This test should output (1, 0) and (0, 1)
    
    
    // s={ (1, 0), (0, 1), (0, 0.4), (0.5, 0.5), (0.3, 0.3), (0, 0.6), (0.2, 0.2) }
    // sky = {(1.0), (0, 1), (0.5, 0.5) 
    
    
    struct point s[7]; 
    struct point sky[3];
    
    s[0].d=2; 
    s[0].a=(double*)malloc( 3*sizeof(double) );
    s[0].a[0]=1; 
    s[0].a[1]=0; 

    s[1].d=2; 
    s[1].a=(double*)malloc( 3*sizeof(double) );
    s[1].a[0]=0; 
    s[1].a[1]=1;
    
    s[2].d=2; 
    s[2].a=(double*)malloc( 3*sizeof(double) );
    s[2].a[0]=0; 
    s[2].a[1]=0.4;     
    
    
    s[3].d=2; 
    s[3].a=(double*)malloc( 3*sizeof(double) );
    s[3].a[0]=0.5; 
    s[3].a[1]=0.5; 
    
    
    s[4].d=2; 
    s[4].a=(double*)malloc( 3*sizeof(double) );
    s[4].a[0]=0.3; 
    s[4].a[1]=0.3; 
    
    s[5].d=2; 
    s[5].a=(double*)malloc( 3*sizeof(double) );
    s[5].a[0]=0; 
    s[5].a[1]=0.6;
    
    s[6].d=2; 
    s[6].a=(double*)malloc( 3*sizeof(double) );
    s[6].a[0]=0.2; 
    s[6].a[1]=0.2; 
    
     
    
    s[0].d=2; 
    s[0].a=(double*)malloc( 3*sizeof(double) );
    s[0].a[0]=1; 
    s[0].a[1]=0; 

    s[1].d=2; 
    s[1].a=(double*)malloc( 3*sizeof(double) );
    s[1].a[0]=0; 
    s[1].a[1]=1;
    
    sky[0].d=2; 
    sky[0].a=(double*)malloc( 3*sizeof(double) );
    sky[0].a[0]=1; 
    sky[0].a[1]=0; 

    sky[1].d=2; 
    sky[1].a=(double*)malloc( 3*sizeof(double) );
    sky[1].a[0]=0; 
    sky[1].a[1]=1;
    
    sky[2].d=2; 
    sky[2].a=(double*)malloc( 3*sizeof(double) );
    sky[2].a[0]=0.5; 
    sky[2].a[1]=0.5;
    
    int maxIndex[5];
    
    
    dominance_greedy(2, 7, 1, s, 3, sky, maxIndex); // This should output (0.5, 0.5)
    printf("first point is (%lf, %lf)\n", sky[maxIndex[0]].a[0], sky[maxIndex[0]].a[1]); 
   
    
    dominance_greedy(2, 7, 2, s, 3, sky, maxIndex); // This should output (0.5, 0.5) and (0, 1) 
    printf("first point is (%lf, %lf)\n", sky[maxIndex[0]].a[0], sky[maxIndex[0]].a[1]); 
    printf("second point point is (%lf, %lf)\n", sky[maxIndex[1]].a[0], sky[maxIndex[1]].a[1]); 
    
    

    system("pause"); 
    
    return 0;
}
*/




