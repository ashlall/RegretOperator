// This is adapted from Min's Sphere code
#include "lp_cube.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

double worstDirection(int index, struct point* s, struct point pt, double* &v)
{
	int K = index;
	int D = pt.d;

  int* ia = new int[1+(K+5)*(D+5)];  //TODO: delete
  int* ja = new int[1+(K+5)*(D+5)];  //TODO: delete
  double* ar = new double[1+(K+5)*(D+5)];   //TODO: delete
  int i, j;
  double epsilon=0.0000000000001;

  glp_prob *lp;
  lp=glp_create_prob();
  glp_set_prob_name(lp, "max_regret_ratio");
  glp_set_obj_dir(lp, GLP_MAX);


  glp_add_rows(lp, K+2);  // add K+2 rows: q_1...q_k and r_1 and r_2
  // Add rows q_1 ... q_K
  for (i=1; i<=K; i++) {
    char buf[10];
    sprintf(buf, "q%d", i);
    glp_set_row_name(lp, i, buf);
    glp_set_row_bnds(lp, i, GLP_UP, 0.0, 0.0); // -infity < qi<=0
  }
     // Add rows r_1 and r_2
  glp_set_row_name(lp, K+1, "r1");
  glp_set_row_bnds(lp, K+1, GLP_UP, 0.0, 1.0+epsilon); // r1 <= 1
  glp_set_row_name(lp, K+2, "r2");
  glp_set_row_bnds(lp, K+2, GLP_UP, 0.0, -1.0+epsilon); // r2 <=-1


  glp_add_cols(lp, D+1);    // add D+1 columns: v[1] ... v[D] and x
  // Add col v[1] ... v[D]
  for (i=1; i<=D; i++) {
    char buf[10];
    sprintf(buf, "v%d", i);

    glp_set_col_name(lp, i, buf);
    glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0); // 0 <= v[i] < infty
    glp_set_obj_coef(lp, i, 0.0);  // objective: maximize x ONLY
  }

  // Add col x
  glp_set_col_name(lp, D+1, "x");
  glp_set_col_bnds(lp, D+1, GLP_FR, 0.0, 0.0); // -infty <= x <= infty
  glp_set_obj_coef(lp, D+1, 1.0);  // objective: maximize x

  /*
          v[1]           v[2]   ...        v[D]    x
    q1 -(p-p_i)[0] -(p-p_i)[1] ... -(p-p_i)[D-1]   1
    q2  ......  same as q1  .................
    ...
    qK  ......  same as q1 .................
    r1   p[0]           p[1]    ...        p[D-1]  0
    r2  -p[0]         -p[1]    ...       -p[D-1]   0
  */

  int counter=1;
  // set value on row q1 ... qk
  for (i=1; i<=K; i++) {
    #ifdef DEBUG_LP
    fprintf(stderr, "%d: a[%d, %d]=%lf\n", counter, i, D+1, 1.0); //DEBUG
    #endif

    ia[counter]=i; ja[counter]=D+1; ar[counter++]=1.0; // a["qi", "x"] =1
    for (j=1; j<=D; j++) {
        #ifdef DEBUG_LP
        fprintf(stderr, "%d: a[%d, %d]=%lf\n", counter, i, j, -(pt.a[j-1]-s[i-1].a[j-1])); //DEBUG
        #endif
        ia[counter]=i; ja[counter]=j;
  ar[counter++] = -(pt.a[j-1]-s[i-1].a[j-1]); // a["qi", "v[j]"] = -(pt-s[i-1])[j-1]
   }
  }

  // set value on row r1 and r2
  #ifdef DEBUG_LP
  fprintf(stderr, "%d: a[%d, %d]=%lf\n", counter, K+1, D+1, 0); //DEBUG
  fprintf(stderr, "%d: a[%d, %d]=%lf\n", counter, K+2, D+1, 0); //DEBUG
  #endif
  ia[counter]=K+1; ja[counter]=D+1; ar[counter++]=0.0; // a["r1", "x"]=0
  ia[counter]=K+2; ja[counter]=D+1; ar[counter++]=0.0; // a["r2", "x"]=0

  for (i=1; i<=D; i++){
    #ifdef DEBUG_LP
    fprintf(stderr, "%d: a[%d, %d]=%lf\n", counter, K+1, i, pt.a[i-1]); //DEBUG
    fprintf(stderr, "%d: a[%d, %d]=%lf\n", counter, K+2, i, -pt.a[i-1]); //DEBUG
    #endif
	  ia[counter]=K+1; ja[counter]=i; ar[counter++]=pt.a[i-1];   // e.g. a["r1", "v[1]"]=pt[0];
	  ia[counter]=K+2; ja[counter]=i; ar[counter++]=-pt.a[i-1];   // e.g. a["r2", "v[1]"]=-pt[0];
  }


  // loading data
  glp_load_matrix(lp, counter-1, ia, ja, ar);


  // Use this to print out the LP if you're debugging
  #ifdef DEBUG_LP
  glp_write_lp(lp, NULL, "testlp.lp");  // DEBUG
  #endif


  // running simplex
  glp_smcp parm;
  glp_init_smcp(&parm);
  parm.msg_lev=GLP_MSG_OFF; // turn off all message by glp_simplex
  glp_simplex(lp, &parm);

  // write solution
  #ifdef DEBUG_LP
  glp_print_sol(lp, "testlp.sol");  // DEBUG
  #endif

  // get values
  double regret_ratio=glp_get_obj_val(lp);
  for (i=0; i<D; i++)
    v[i]=glp_get_col_prim(lp, i+1); // v[0] is at column 1, v[1] at col 2 ...


  glp_delete_prob(lp); // clean up
  delete []ia;
  delete []ja;
  delete []ar;

  return regret_ratio;
}

// // determinant code from http://www.c.happycodings.com/Beginners_Lab_Assignments/code62.html
// double determinant(int n, double** a)
// {
//     int i, j, k;
//     double mult;
//     double det = 1.0;
//
//     for(i = 0; i < n; i++)
//     {
//         for(j = 0; j < n; j++)
//         {
//             mult = a[j][i]/a[i][i];
//             for(k = 0; k < n; k++)
//             {
//                 if (i==j) break;
//                 a[j][k] = a[j][k] - a[i][k] * mult;
//             }
//         }
//     }
//
//     for(i = 0; i < n; i++)
//     {
//         det = det * a[i][i];
//     }
//
//     return det;
// }

double evaluateRandom(int D, int N, int K, struct point *p, struct point* S, int REPEATS, int VERBOSE)
{
	int i, j;
	double sum, maxK, maxN, avgSum = 0.0, maxRegret = 0.0;
	double sample[D];

	srand(time(NULL));

   // Evaluate regret using lots of random utility functions
	for(i = 0; i < REPEATS; ++i)
	{
		sum = 0.0;
		for(j = 0; j < D; ++j)
			sample[j] = rand();
		for(j = 0; j < D; ++j)
			sum += sample[j];
		for(j = 0; j < D; ++j)
			sample[j] /= sum;

		maxK = 0.0;
		for(j = 0; j < K; ++j)
			if (dot(S[j], sample) > maxK)
				maxK = dot(S[j], sample);


		maxN = 0.0;
        for(j = 0; j < N; ++j)
			if (dot(p[j], sample) > maxN)
				maxN = dot(p[j], sample);

/*
  for(j = 0; j < D; ++j)
  printf("%lf ", sample[j]);
  printf("| %lf %lf | %lf\n", maxK, maxN, 1.0 - (maxK/maxN));
*/

		avgSum += 1.0 - maxK/maxN;

		if (1.0 - maxK/maxN > maxRegret)
			maxRegret = 1.0 - maxK/maxN;
	}

	if (VERBOSE)
		printf("Average/max regret ratio over %d random trials: %lf / %lf\n", REPEATS, (avgSum/REPEATS), maxRegret);

	return maxRegret;
}

double evaluateRandom(int D, int N, int K, struct point *p, int *maxIndex, int REPEATS, int VERBOSE)
{
	int i, j;
	double sum, maxK, maxN, avgSum = 0.0, maxRegret = 0.0;
	double sample[D];

	//srand(time(NULL));

   // Evaluate regret using lots of random utility functions
	for(i = 0; i < REPEATS; ++i)
	{
		sum = 0.0;
		for(j = 0; j < D; ++j)
			sample[j] = rand();
		for(j = 0; j < D; ++j)
			sum += sample[j];
		for(j = 0; j < D; ++j)
			sample[j] /= sum;

		maxK = 0.0;
		for(j = 0; j < K; ++j)
			if (dot(p[maxIndex[j]], sample) > maxK)
				maxK = dot(p[maxIndex[j]], sample);

		maxN = 0.0;
        for(j = 0; j < N; ++j)
			if (dot(p[j], sample) > maxN)
				maxN = dot(p[j], sample);

/*
  for(j = 0; j < D; ++j)
  printf("%lf ", sample[j]);
  printf("| %lf %lf | %lf\n", maxK, maxN, 1.0 - (maxK/maxN));
*/

		avgSum += 1.0 - maxK/maxN;

		if (1.0 - maxK/maxN > maxRegret)
			maxRegret = 1.0 - maxK/maxN;
	}

	if (VERBOSE)
		printf("Average/max regret ratio over %d random trials: %lf / %lf\n", REPEATS, (avgSum/REPEATS), maxRegret);

	return maxRegret;
}
