#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#include "point.h"
#include "cube.h"
#include "LIB_Util.h"
#include "sphere.h"
#include "data_utility.h"
#include "operation.h"

int main(int argc, char** argv)
{
	int i, j, N, D, K, db, LIB;

	int REPEATS = 10000; // number of trials to evaluate funcit  on
	int DATAREPEATS = 10;  // number of data sets used
  int VERBOSE = 0;
  //Cube , Cube LIB, Sphere , Sphere LIB
	int NUM_METHODS = 6;
  double times[NUM_METHODS];
  struct timeval start, end;
  double M;

  int* maxIndex;
  struct point* p;
  struct point* pPrime;
  point_set_t* P;
  point_set_t* skyline;
  point_set_t *S;
	FILE* fp;
	FILE* log;


	double rr[NUM_METHODS];
	char filename[1024];
	char *methods[] = {"Cube        ", "Cube LIB       ","Sphere      ", "Sphere LIB     ", "ImpGreedy      ", "ImpGreedy LIB       ",
                      };
	if (argc <= 4)
	{
		printf ("usage: ./vary-n file-prefix K M db\n");
		return 0;
	}

	if (argc > 4)
  {
		K = atoi(argv[2]);
    M = atof(argv[3]);
    db = atoi(argv[4]);
  }
	sprintf(filename, "plot/varyn-%s-k%d-db%d", argv[1], K, db);
	fp = fopen(filename, "w");

	sprintf(filename, "plot/varyn-%s-k%d-db%d.log", argv[1], K, db);
  log = fopen(filename, "w");

	for(N = 100; N <= 1000000; N *= 10)
	{
		fprintf(fp, "%d", N);
		for(i = 0; i < NUM_METHODS; ++i)
		{
      rr[i] = 0.0;
      if (i < NUM_METHODS /2)
        times[i] = 0.0;
		}
		for(j = 0; j < DATAREPEATS; ++j)
		{
      p = new struct point[N];
      maxIndex = new int[K];
			sprintf(filename, "Data/%s-%d-%d.dat", argv[1], N, j + 1);
      cout << filename << endl;

      p = readPoints(filename);
      D = p[0].d;
      gettimeofday(&start, NULL);
      p = scale(D,p,N);
      pPrime = transformforth(db,D,p,N);

			// Cube algorithm
      cout<<"------------------------Transformed Cube-----------------------"<<j+1<<endl;
			cube(D, N, K, pPrime, maxIndex);
      gettimeofday(&end, NULL);

      i = 0;
      LIB = 0;
      times[i/2] += (end.tv_sec  - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;
			rr[i] += evaluateRandomLIB(D, N, K, pPrime, maxIndex, REPEATS, LIB, db, VERBOSE, M);
			printf("%s, n=%d, %lf s, %lf\n",methods[i], N, times[i/2]/(j+1),rr[i]/(j+1));
			fprintf(log, "%s, n=%d, %lf s, %lf\n",methods[i], N, times[i/2]/(j+1),rr[i]/(j+1));

      //Cube LIB
      cout<<"-------------------------Transformedback Cube-------------------------"<<j+1<<endl;
      i = 1;
      LIB = 1;
      rr[i] += evaluateRandomLIB(D, N, K, p, maxIndex, REPEATS, LIB, D, VERBOSE, M);

      printf("%s, n=%d, %lf\n",methods[i], N,  rr[i]/(j+1));
      fprintf(log, "%s, n=%d,%lf\n",methods[i], N, rr[i]/(j+1));

      // Sphere algorithm
      cout<<"--------------------Transformed Sphere------------------------"<<j+1<<endl;
      gettimeofday(&start, NULL);
      P = Cube2Sphere(D,pPrime,N);
      skyline = skyline_point(P);

      S = sphereWSImpLP(skyline,K);
			gettimeofday(&end, NULL);

      i = 2;
      LIB = 0;
      for (int x = 0; x < K; x++){
        maxIndex[x] = S->points[x]->id;
      }
      times[i/2] += (end.tv_sec  - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;
			rr[i] += evaluateRandomLIB(D, N, K, pPrime, maxIndex, REPEATS, LIB, db, VERBOSE, M);

			printf("%s, n=%d, %lf s, %lf\n",methods[i], N, times[i/2]/(j+1),rr[i]/(j+1));
			fprintf(log, "%s, n=%d %lf s, %lf\n", methods[i], N, times[i/2]/(j+1),rr[i]/(j+1));

      //Sphere LIB
      cout<<"---------------------Transformeback Sphere------------------------"<<j+1<<endl;
      i= 3;
      LIB = 1;
      rr[i] += evaluateRandomLIB(D, N, K, p, maxIndex, REPEATS, LIB, db, VERBOSE, M);
      printf("%s, n=%d, %lf\n",methods[i], N, rr[i]/(j+1));
      fprintf(log, "%s, n=%d, %lf\n", methods[i], N, rr[i]/(j+1));


      // Uniform direction solution
      cout<<"--------------------Transformed ImpGreedy-------------------"<<j+1<<endl;
      gettimeofday(&start, NULL);
      P = Cube2Sphere(D, pPrime, N);
			S = ImpGreedy(K, P);
			gettimeofday(&end, NULL);
      i = 4;
      LIB= 0;

      for (int x = 0; x < K; x++){
        maxIndex[x] = S->points[x]->id;
      }
      times[i/2] += (end.tv_sec  - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;
			rr[i] += evaluateRandomLIB(D, N, K, pPrime, maxIndex, REPEATS, LIB, db, VERBOSE, M);
			printf("%s, n=%d, %lf s, %lf\n", methods[i], N, times[i/2]/(j+1),rr[i]/(j+1));
			fprintf(log, "%s, n=%d, %lf s, %lf\n", methods[i], N, times[i/2]/(j+1),rr[i]/(j+1));

      // Uniform direction solution
      cout<<"--------------------Transformeback ImpGreedy----------------------"<<j+1<<endl;
      i = 5;
      LIB= 1;
			rr[i] += evaluateRandomLIB(D, N, K, p, maxIndex, REPEATS, LIB, db, VERBOSE, M);

			printf("%s, n=%d, %lf\n", methods[i], N, rr[i]/(j+1));
			fprintf(log, "%s, n=%d, %lf\n", methods[i], N, rr[i]/(j+1));

      delete[] p;
      delete[] maxIndex;
      delete[] pPrime;
		}
		printf("\n");
		for(i = 0; i < NUM_METHODS; ++i)
			fprintf(fp, "\t%lf", rr[i]/DATAREPEATS);
    for(i = 0; i < NUM_METHODS/2; ++i)
			fprintf(fp, "\t%lf", times[i]/DATAREPEATS);
		fprintf(fp, "\n");
		fflush(fp);
	}

	// free up memory
  cout << "END" << endl;
	fclose(fp); fclose(log);

	return 0;
}
