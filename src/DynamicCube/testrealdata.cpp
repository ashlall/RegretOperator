#include "cube.h"
#include "cube_dynamic.h"
#include "point_cube.h"
#include "maxheap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cmath>

using namespace std;

enum {DYNAMIC_CUBE, CUBE};

const int ALGO_NUM = 1;
const int UTIL_REPEATS = 10000;
const int D_max = 9;
const int K_max = 100;

// These global variables are for dynamic cube
MaxHeap** M = NULL;
MaxHeap** B = NULL;
int bNum;
struct point* c = NULL;
int ID = 0;

// Usage: <executable> <input> <K> <m>
// 		  input includes: nba, stock, house, color
int main(int argc, char* argv[])
{
  string inputname = argv[1];
  inputname = "Data/" + inputname + ".dat";
  string outputname = argv[1];
  outputname = "Results/" + outputname + ".log";
  ofstream output(outputname);

  cout << "\nTesting " << inputname << endl;
  int datasize = 1000000;
  int N;
  int D;
  int K = stoi(argv[2]);
  double m = stod(argv[3]);
  struct point* data;

  // Read input
  ifstream file(inputname);
  file >> N;
  file >> D;

  output << N << ' ' << D << endl;

  data = new struct point[N];

  for (int i = 0; i < N; ++i)
  {
  	data[i].id = ID;
    data[i].d = D;
    data[i].a = new double[D];
		++ID;
    for (int j = 0; j < D; ++j)
      file >> data[i].a[j];
  }

  file.close();

  int N_init = N/2;
  int cube_answer[K_max];
  struct point dynamic_cube_answer[K_max];
  allocateData(K_max, D, dynamic_cube_answer);

  //void dynamic_cube(int D, int N, int K, struct point *p, int *maxIndex);
  int start_time, stop_time;
  double running_time = 0.0;

  int insNum = N - N_init;
  cout << "Number of insertion: " << insNum << endl;

  double exe_time[ALGO_NUM];
  double* rr[ALGO_NUM];
  for (int i = 0; i < ALGO_NUM; ++i)
    rr[i] = new double[insNum];

  // // --------Cube--------
  // cout << "--------------Cube--------------\n";
  //
  // running_time = 0.0;
  // start_time = clock();
  // cube(D,N_init,K,data,cube_answer);
  // stop_time = clock();
  // running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);
  //
  // for (int i = 0; i < insNum; ++i)
  // {
  //   if (i % 1000 == 0)
  //     cout << "Cube " << i << '\n';
  //   start_time = clock();
  //   //cube(D,N_init+i+1,K,data,cube_answer);
  //   stop_time = clock();
  //   running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);
  //
  //   // calculate regret ratio after each insertion
  //   rr[CUBE][i] = evaluateRandom(D, N_init+i+1, K, data, cube_answer, UTIL_REPEATS, 0);
  // }
  //
  // cout << "Runtime: " << running_time << "seconds" << endl << endl;
  // exe_time[CUBE] = running_time;
  // cout << running_time << " seconds.\n";

  int count = 0;

  // ----Dynamic Cube------
  cout << "-------------Dynamic Cube-------------\n";
  running_time = 0.0;
  start_time = clock();
  dynamic_cube(D, N_init, K, data, cube_answer);
  stop_time = clock();
  running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);

  for (int i = 0; i < insNum; ++i)
  {
    if (i % 1000 == 0)
    {
      cout << "Insertion no." << i << endl;
      cout << "     Total running time so far: " << running_time << endl;
    }
    start_time = clock();
    bool success = cube_insert(D, N_init, K, m, data, data[N_init], dynamic_cube_answer, cube_answer);
    stop_time = clock();
    running_time += (stop_time - start_time)/(double)(CLOCKS_PER_SEC);

    if (i % 1000 == 0 || i == insNum-1)
    {
      if (success)
        rr[DYNAMIC_CUBE][count] = evaluateRandom(D, N_init, K, data, dynamic_cube_answer, UTIL_REPEATS, 0);
      else
        rr[DYNAMIC_CUBE][count] = evaluateRandom(D, N_init, K, data, cube_answer, UTIL_REPEATS, 0);
      ++count;
    }
  }

  cout << "Total running time: " << running_time << " seconds.\n";
  exe_time[DYNAMIC_CUBE] = running_time;

  for (int i = 0; i < ALGO_NUM; ++i)
    output << exe_time[i] << ' ' << sort(count,rr[i]);

  output.close();

  deallocateCube(true, true, D);
  deallocateData(K_max, D, dynamic_cube_answer);
  deallocateData(N, D, data);

  for (int i = 0; i < ALGO_NUM; ++i)
    delete[] rr[i];
  delete[] data;

  return 0;
}
