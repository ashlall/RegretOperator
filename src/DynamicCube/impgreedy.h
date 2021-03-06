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

#ifndef IMPGREEDY_H
#define IMPGREEDY_H

#include "data_utility.h"
#include "operation.h"

#include "lp.h"

// The ImpGreedy algorithm with only Step 4 of Sphere for comparison
// Parameter:
// - point_set: the set of all point p in the database
// - k: the number of item in the returning set
// return the desire set S of k point
point_set_t* ImpGreedy(int K, point_set_t *p);

#endif
