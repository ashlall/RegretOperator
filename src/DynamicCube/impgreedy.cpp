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

//#include "stdafx.h"
#include "impgreedy.h"

//==============================================================================
// The ImpGreedy algorithm with only Step 4 of Sphere for comparison
//Paremeter:
//- point_set: the set of point p in the database
//- k: the number of point in the returning set S
// return: the set S that minimize the MRR
//==============================================================================
point_set_t* ImpGreedy(int k, point_set_t* point_set)
{
  int dim = point_set->points[0]->dim;
  int N = point_set->numberOfPoints;

  point_set_t* result = alloc_point_set(k);

  // Initialize to the boundary points
  double* b_value = new double[dim];
  for (int j = 0; j < dim; j++)
  {
    b_value[j] = 0;
    for (int i = 0; i < point_set->numberOfPoints; i++)
    {
      if (point_set->points[i]->coord[j] > b_value[j])
      {
        b_value[j] = point_set->points[i]->coord[j];
        result->points[j] = point_set->points[i];
      }
    }
  }

  int count = dim;
  if (count == k)
    return result;

  // compute mrr_O(p) for each p in D
  double epsilon = 0.0000001;
  double worst, w;
  point_t* max;
  int* active = new int[point_set->numberOfPoints];

  point_t* lastRound_max;
  point_set_t* directions = alloc_point_set(N);
  double *rr = new double[N];

  max = NULL;
  worst = 0;
  for (int i = 0; i< N; i++)
  {
    active[i] = 1;

    directions->points[i] = alloc_point(dim);

    rr[i] = worstDirection(count, result, point_set->points[i], directions->points[i]->coord);

    w = rr[i];
    if (worst<w)
    {
      worst = w;
      max = point_set->points[i];
    }
    if (rr[i] <= 0.0 + epsilon)
      active[i] = 0;
  }


  result->points[count++] = max;
  lastRound_max = max;

  while (count < k)
  {
    // Find a point with maximum regret
    max = NULL;
    worst = 0;

    for (int i = 0; i < N; i++)
    {
      // upper bounding
      if (worst > rr[i])
      {
        directions->points[i]->id = -2;
        continue;
      }
      // invariant checking fails or the worst utility vector is outdated
      else if (directions->points[i]->id == -2 || dot_prod(sub(point_set->points[i], lastRound_max), directions->points[i]) < rr[i])
      {
        rr[i] = worstDirection(count, result, point_set->points[i], directions->points[i]->coord);
        directions->points[i]->id = -1;
      }

      // update the current worst point
      w = rr[i];
      if (worst<w)
      {
        worst = w;
        max = point_set->points[i];
      }
      if (w <= 0.0 + epsilon)
        active[i] = 0;
    }

    // Add a point if regret > 0. Otherwise, stop.
    if (worst >= 0.0 + epsilon)
    {
      result->points[count++] = max;
      lastRound_max = max;
    }
    else
    {
      break;
    }
  }

  // fill in any remaining points with the first point
  for (int j = count; j < k; ++j)
    result->points[j] = result->points[0];

  delete[] rr;
  delete[] active;
  delete[] b_value;

  release_point_set(directions, true);
  return result;
}
