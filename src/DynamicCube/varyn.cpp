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

// Vary N test for Cube, Dynamic Cube, Sphere and ImpGreedy
// Output format:
//    First line: D K number_of_tests (call it t)
//    The following t 5-line blocks are in this format:
//        N tested
//        running_time avg_rr 0%_rr 25%_rr 50%_rr 75%_rr 100%_rr for each algorithm on each line
//    Order of algorithms are as listed above.

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
#include <sstream>
#include <ctime>
#include <cmath>

using namespace std;

// These global variables are for dynamic cube
MaxHeap** M = NULL;
MaxHeap** B = NULL;
int bNum;
struct point* c = NULL;
int ID = 0;

enum {CUBE, DYNAMIC_CUBE, SPHERE, IMPGREEDY};

// Constants
const int ALGO_NUM = 4;
const int ALGO_NUM_DEL = 2;
const int K_max = 100;
      int N_max = 10000;
const int UTIL_REPEATS = 10000; // the number of utility functions to generate
const string output_filename = "Results/varyn.log";
const string output_deletion_filename = "NewResults/varyn-del.log";

// Usage: <executable> <data-type> <K> <test insertion: 0/1> <test deletion: 0/1> <m>
// Data-type: a (anti-correlated)
//            e (equal/independent)
int main(int argc, char* argv[])
{
  int K = stoi(argv[2]);
  int D = 4;
  int N;
  string datatype;
  int start_time, stop_time;

  if (K < 1 || K > K_max)
    exit(0);



  bool testIns = stoi(argv[3]);
  if (testIns)
  {
    string prefix(argv[1]);
    int testNum = 3; // max is 5. But 4 and 5 runs slows as N is big
    int baseN = 100;
    point_set_t* data_s;

    struct point* data;
    data = new struct point[N_max];

    double* rr[ALGO_NUM];
    for (int i = 0; i < ALGO_NUM; ++i)
      rr[i] = new double[N_max];

    allocateData(N_max,D,data);
    if (prefix[0] == 'a')
      datatype = "anti-correlated";
    else
      datatype = "independent";

    cout << "\nRunning vary-n insertion\n";
    cout << "*Using " << datatype << " datasets*\n\n";

    ofstream output(output_filename);
    output << D << ' ' << K << ' ' << testNum << endl;

    for (int test = 0; test < testNum; ++test)
    {
      ID = 0;
      double exe_time[ALGO_NUM];

      string input = "Data/" + prefix;
      input += to_string(D) + "-" + to_string(baseN*(int)pow(10,test)) + ".dat";

      cout << "Reading input...\n";
      char input_c[100];
      toCStr(input_c,input);
      data_s = read_points(input_c);


      readInput(N,ID,input,data);
      cout << "========= N=" << N << " D=" << to_string(D) << " K=" << K << " =========\n";
      cout << "File: " << input << endl;
      cout << "Sorting data...\n\n";
      sortData(data, 0, N-1);

      output << N << endl;

      int N_init = N/2;
      int insNum = N - N_init;
      cout << "Number of insertion: " << insNum << endl;
      int N_it; // N iterator - for insertion purposes
      double running_time; // measured in seconds

      // --------Cube--------
      cout << "--------------Cube--------------\n";
      int cube_result[K_max];
      N_it = N_init;

      running_time = 0.0;
      start_time = clock();
      cube(D,N_init,K,data,cube_result);
      stop_time = clock();
      running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);

      for (int i = 0; i < insNum; ++i)
      {
        if (i % 1000 == 0)
          cout << "Cube " << i << '\n';
        start_time = clock();
        cube(D,N_it+i+1,K,data,cube_result);
        stop_time = clock();
        running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);

        // calculate regret ratio after each insertion
        rr[CUBE][i] = evaluateRandom(D, N_it+i+1, K, data, cube_result, UTIL_REPEATS, 0);
      }

      cout << "Runtime: " << running_time << "seconds" << endl << endl;
      exe_time[CUBE] = running_time;

      // --------Dynamic Cube--------
      cout << "----------Dynamic Cube----------\n";
      double m = stod(argv[5]);
      cout << "m = " << m << "\n";
      struct point dynamic_cube_result[K_max];
      allocateData(K_max,D,dynamic_cube_result);
      N_it = N_init;

      running_time = 0.0;
      start_time = clock();
      dynamic_cube(D,N_init,K,data,cube_result);
      stop_time = clock();
      running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);

      for (int i = 0; i < insNum; ++i)
      {
        // calculate running time
        start_time = clock();
        bool success = cube_insert(D,N_it,K,m,data,data[N_it],dynamic_cube_result,cube_result);
        stop_time = clock();
        running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);

        // calculate regret ratio after each insertion
        if (success)
          rr[DYNAMIC_CUBE][i] = evaluateRandom(D, N_it, K, data, dynamic_cube_result, UTIL_REPEATS, 0);
        else
          rr[DYNAMIC_CUBE][i] = evaluateRandom(D, N_it, K, data, cube_result, UTIL_REPEATS, 0);
      }

      cout << "Runtime: " << running_time << "seconds" << endl << endl;
      exe_time[DYNAMIC_CUBE] = running_time;

      // --------Sphere---------
      cout << "-------------Sphere-------------\n";
      cout << "Not computing skyline\n";
      point_set_t* sphere_result;
      N_it = N_init + 1;
      data_s->numberOfPoints = N_init;

      running_time = 0.0;
      start_time = clock();
      sphere_result = sphereWSImpLP(data_s, K);
      stop_time = clock();
      running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);

      release_point_set(sphere_result, false);

      for (int i = N_it; i <= N; ++i)
      {
        // calculate running time
        data_s->numberOfPoints = i;
        start_time = clock();
        sphere_result = sphereWSImpLP(data_s, K);
        stop_time = clock();
        running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);

        // calculate regret ratio after each insertion
        rr[SPHERE][i-N_it] = evaluateRandom(D, i, K, data_s, sphere_result, UTIL_REPEATS, 0);

        release_point_set(sphere_result, false);
      }

      cout << "Runtime: " << running_time << "seconds" << endl << endl;
      exe_time[SPHERE] = running_time;

      // ----------Imp Greedy----------
      cout << "---------Imp Greedy---------\n";
      point_set_t* greedy_result;
      N_it = N_init + 1;
      data_s->numberOfPoints = N_init;

      running_time = 0.0;
      start_time = clock();
      greedy_result = ImpGreedy(K, data_s);
      stop_time = clock();
      release_point_set(greedy_result, false);

      running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);
      for (int i = N_it; i <= N; ++i)
      {
        // calculate running time
        data_s->numberOfPoints = i;
        start_time = clock();
        greedy_result = ImpGreedy(K, data_s);
        stop_time = clock();
        running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);

        // calculate regret ratio after each insertion
        rr[IMPGREEDY][i-N_it] = evaluateRandom(D, i, K, data_s, greedy_result, UTIL_REPEATS, 0);
        release_point_set(greedy_result, false);
      }

      cout << "Runtime: " << running_time << "seconds" << endl << endl;
      exe_time[IMPGREEDY] = running_time;

      for (int i = 0; i < ALGO_NUM; ++i)
        output << exe_time[i] << ' ' << sort(insNum, rr[i]);

      deallocateCube(true, true, D);

      deallocateData(K_max,D,dynamic_cube_result);
      release_point_set(data_s,false);

    }

    output.close();

    deallocateData(N_max,D,data);
    for (int i = 0; i < ALGO_NUM; ++i)
      delete[] rr[i];

    delete[] data;
  }

  // Deletion test
  bool testDel = stoi(argv[4]);
  if (testDel)
  {
    string prefix(argv[1]);
    int testNum = 3; // max is 3
    int baseN = 100;
    struct point* data;
    data = new struct point[N_max];
    point_set_t* data_s;
    allocateData(N_max,D,data);

    if (prefix[0] == 'a')
      datatype = "anti-correlated";
    else
      datatype = "independent";

    cout << "\nRunning vary-n deletion\n";
    cout << "*Using " << datatype << " datasets*\n\n";

    ofstream output(output_deletion_filename);
    output << D << ' ' << K << ' ' << testNum << endl;

    double* rr[ALGO_NUM_DEL];
    for (int i = 0; i < ALGO_NUM_DEL; ++i)
      rr[i] = new double[N_max];

    for (int test = 0; test < testNum; ++test)
    {
      ID = 0;
      double exe_time[ALGO_NUM_DEL];

      string input = "Data/" + prefix;
      input += to_string(D) + "-" + to_string(baseN*(int)pow(10,test)) + ".dat";

      readInput(N, ID, input, data);
      sortData(data, 0, N-1);

      cout << "========= N=" << N << " D=" << to_string(D) << " K=" << K << " =========\n";
      cout << "File: " << input << endl;

      output << N << endl;

      int delNum = N/2;
      cout << "Number of deletion: " << delNum << endl;
      int N_it = N;
      int start_time, stop_time;
      double running_time;
      // -----------Cube-----------
      cout << "------------Cube------------\n";
      int cube_result[K_max];
      running_time = 0.0;

      start_time = clock();
      cube(D,N_it,K,data,cube_result);
      stop_time = clock();
      running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);
      for (int i = 0; i < delNum; ++i)
      {
        // calculate running time
        start_time = clock();
        cube(D,N-i-1,K,data,cube_result);
        stop_time = clock();
        running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);

        // calculate regret ratio after each deletion
        rr[CUBE][i] = evaluateRandom(D, N-i-1, K, data, cube_result, UTIL_REPEATS, 0);
      }
      cout << "Runtime: " << running_time << "seconds" << endl << endl;
      exe_time[CUBE] = running_time;

      // ---------------Dynamic Cube---------------
      cout << "----------Dynamic Cube---------\n";
      double m = stod(argv[5]);
      cout << "m = " << m << "\n";
      struct point dynamic_cube_result[K_max];
      allocateData(K_max,D,dynamic_cube_result);
      N_it = N;
      ID = N_it; // ID is reset to the initial size of the dataset we run Dynamic Cube on

      running_time = 0.0;
      start_time = clock();
      dynamic_cube(D,N_it,K,data,cube_result);
      stop_time = clock();
      running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);

      for (int i = 0; i < delNum; ++i)
      {
        // calculate running time
        start_time = clock();
        bool success = cube_delete(D, N_it, K, m, data, N_it-1, dynamic_cube_result, cube_result);
        stop_time = clock();
        running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);

        // calculate regret ratio after each insertion
        if (success)
        {
          rr[DYNAMIC_CUBE][i] = evaluateRandom(D, N_it, K, data, dynamic_cube_result, UTIL_REPEATS, 0);
        }
        else
        {
          rr[DYNAMIC_CUBE][i] = evaluateRandom(D, N_it, K, data, cube_result, UTIL_REPEATS, 0);
        }
      }

      cout << "Runtime: " << running_time << "seconds" << endl << endl;
      exe_time[DYNAMIC_CUBE] = running_time;


      for (int i = 0; i < ALGO_NUM_DEL; ++i)
        output << exe_time[i] << ' ' << sort(delNum, rr[i]);

      deallocateCube(true, true, D);

      deallocateData(K_max, D, dynamic_cube_result);
    }

    output.close();

    deallocateData(N_max, D, data);

    for (int i = 0; i < ALGO_NUM_DEL; ++i)
      delete[] rr[i];

    delete[] data;
  }

  return 0;
}
