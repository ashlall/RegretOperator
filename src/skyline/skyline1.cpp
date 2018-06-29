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
//Contains two Skyline algorithms for use in conjunction with k-regret operations
//==========================================================================================

#include <stdio.h>
#include <cstdlib>
#include "point.h"

int skyline(int N, struct point *p, struct point *skyline) 
{
//==========================================================================================
//Less efficient of the two skyline algorithms
//Inputs:
//N: Number of points in database
//*p: pointer to struct of points in database
//*skyline: pointer to an empty point struct that will contain the skyline
//==========================================================================================

	int i, j, dominated, index = 0, m;
	struct point pt;

	for(i = 0; i < N; ++i)    
	{  
		dominated = 0;  
		pt = p[i]; 
		
		// check if pt is dominated by the skyline so far   
		for(j = 0; j < index && !dominated; ++j)  
			if (dominates(skyline[j], pt)) 
                dominated = 1;  
		
		if (!dominated)
		{
			// eliminate any points in current skyline that it dominates
			m = index;
			index = 0;
			for(j = 0; j < m; ++j)
				if (!dominates(pt, skyline[j]))
					skyline[index++] = skyline[j];

			// add this point as well
		   skyline[index++] = pt; 
		}
    }  
	
	return index;
}

int skyline2(int N, struct point *p, struct point *skyline)
{
//==========================================================================================
//More efficient of the two skyline algorithms
//Inputs:
//N: Number of points in database
//*p: pointer to struct of points in database
//*skyline: pointer to an empty point struct that will contain the skyline
//==========================================================================================

    int i, j, dominated, index = 0;
    struct point pt;

    for(i = 0; i < N; ++i)
    {
        dominated = 0;
        pt = p[i];

        // check if pt is dominated by the skyline so far
        for(j = 0; j < index && !dominated; ++j)
            if (dominates(skyline[j], pt))
                dominated = 1;

        // check if pt is dominated by subsequent point
        for(j = i + 1; j < N && !dominated; ++j)
            if (dominates(p[j], pt))
                dominated = 1;

		if (!dominated)
			skyline[index++] = pt;
    }

    return index;
}
