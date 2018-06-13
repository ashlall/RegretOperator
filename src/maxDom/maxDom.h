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
//
//===================================================================
// This function implements the approximate algorithm for retrieving
// max-dominance representative skyline (Algorithm 1 in Lin et al. [ICDE'07])
// Coded by Danupon Nanongkai Nov. 16, 2009 
// MaxDom.h
//===================================================================

#ifndef MAXDOM
#define MAXDOM

void dominance_greedy(int D, int N, int K, struct point *s, int skylineSize, struct point *sky, int *maxIndex);

#endif
