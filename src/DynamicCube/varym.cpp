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

// Vary m test for Dynamic Cube
// Output file format:
//    First line: N D K m number_of_m_values_tested (call it t)
//    The following t lines are in this format: (1) (2) (3) (4) (5) (6) (7) (8)
//        (1) m value tested
//        (2) running time
//        (3) average regret ratio after all insertions
//        (4) 0 percentile regret ratio
//        (5) 25 percentile regret ratio
//        (6) 50 percentile regret ratio
//        (7) 75 percentile regret ratio
//        (8) 100 percentile regret ratio

#include "cube.h"
#include "cube_dynamic.h"
#include "sphere.h"
#include "impgreedy.h"
#include "data_utility.h"
#include "point_cube.h"
#include "maxheap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <time.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

MaxHeap** M = NULL;
MaxHeap** B = NULL;
int bNum;
struct point* c = NULL;
int ID = 0;

const int N_max = 10000;
const int K_max = 100;

const int UTILS_REPEATS = 10000;
const int N_default = 10000;
const int D_default = 4;
const int K_default = 30;

const string output_filename = "Results/varym.log";


// Usage: <executable> <data-type> <K> <starting_m> <# of tests>
// Data-type: a (anti-correlated)
//            e (equal/independent)
int main(int argc, char* argv[])
{
  int K = stoi(argv[2]);
  int D = D_default;
  int N = N_default;
  double m = stod(argv[3]);
  string datatype;
  int start_time, stop_time;

  if (K < 1 || K > K_max)
    exit(0);

  string prefix(argv[1]);
  int testNum = stoi(argv[4]); // max is 10 with inital m = 0.0
  int baseN = 100;
  struct point data[N_max];
  point_set_t* data_s;
  allocateData(N_max,D,data);

  if (prefix[0] == 'a')
    datatype = "anti-correlated";
  else
    datatype = "independent";

  cout << "\nRunning vary-m\n";
  cout << "*Using " << datatype << " datasets*\n";
  cout << "Varying m is only for dynamic cube\n\n";

  // Initialize data with input file
  string input = "Data/";
  input += prefix + to_string(D) + "-" + to_string(N) + ".dat";

  // char input_c[100];
  // toCStr(input_c,input);
  // data_s = read_points(input_c);
  readInput(N,ID,input,data);

  // sort the data so that a boundary point(s) changes in every insertion
  sortData(data, 0, N-1);
  cout << "File: " << input << endl;

  int N_init = N/2;
  int insNum = N - N_init;
  cout << "Number of insertion: " << insNum << endl;

  ofstream output(output_filename);
  output << N << ' ' << D << ' ' << K << ' ' << testNum << endl;

  for (int test = 0; test < testNum; ++test)
  {
    int N_it; // N iterator - for insertion purposes
    double running_time = 0.0; // measured in seconds
    double avg_rr = 0.0;

    int cube_result[K_max];

    // --------Dynamic Cube--------
    cout << "---------- m=" << m <<" ----------\n";
    output << m << ' ';
    double rr[insNum];

    struct point dynamic_cube_result[K_max];
    allocateData(K_max,D,dynamic_cube_result);
    N_it = N_init;

    start_time = clock();
    dynamic_cube(D,N_init,K,data,cube_result);
    stop_time = clock();
    running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);
    for (int i = 0; i < insNum; ++i)
    {
      //cout << insNum << ' ' << i << endl;
      // insert and get running time
      start_time = clock();
      bool success = cube_insert(D,N_it,K,m,data,data[N_it],dynamic_cube_result,cube_result);
      stop_time = clock();
      running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);

      // calculate regret ratio after this insertion
      if (success) // result is stored in dynamic_cube_result
      {
        rr[i] = evaluateRandom(D, N_it, K, data, dynamic_cube_result, UTILS_REPEATS, 0);
        avg_rr += rr[i];
      }
      else
      {
        rr[i] = evaluateRandom(D, N_it, K, data, cube_result, UTILS_REPEATS, 0);
        avg_rr += rr[i];
      }

      if ((i+1) % 500 == 0)
      {
        cout << "After the " << i+1 << "th insertion: " << endl;
        cout << "     - Regret ratio: "<< rr[i] << endl;
        cout << "     - Average regret ratio so far: "<< avg_rr/(i+1) << endl;
      }
    }

    cout << "Runtime: " << running_time << "seconds" << endl << endl;
    output << running_time << ' ';

    avg_rr /= insNum;
    output << avg_rr << ' ';

    sort(insNum, rr);
    output << rr[0] << ' ';
    output << rr[insNum/4] << ' ';
    output << rr[insNum/2] << ' ';
    output << rr[insNum*3/4] << ' ';
    output << rr[insNum-1] << endl;
    m += 0.1;

    // // --------Sphere---------
    // cout << "-------------Sphere-------------\n";
    // cout << "Not computing skyline\n";
    // point_set_t* sphere_result;
    // N_it = N_init + 1;
    // data_s->numberOfPoints = N_init;
    //
    // start_time = clock();
    // sphere_result = sphereWSImpLP(data_s, K);
    // for (int i = N_it; i < N; ++i)
    // {
    //   data_s->numberOfPoints = i;
    //   sphere_result = sphereWSImpLP(data_s, K);
    // }
    // stop_time = clock();
    // running_time = (stop_time - start_time)/(double)(CLOCKS_PER_SEC);
    // cout << "Runtime: " << running_time << "seconds" << endl << endl;

    deallocateData(K_max,D,dynamic_cube_result);
    deallocateCube(true, true, D);
    // release_point_set(data_s,false);
    // release_point_set(sphere_result,false);
  }

  output.close();

  deallocateData(N_max, D, data);

  return 0;
}
