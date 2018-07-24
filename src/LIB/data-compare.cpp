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
	int NUM_METHODS = 9;
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
	double times[NUM_METHODS];
	char filename[1024];
	char *methods[] = {"CubeA        ", "CubeE        ","CubeC       ", "SphereA      ", "SphereE     ",
                    "SphereC     ", "ImpGreedyA      ", "ImpGreedyE       ","ImpGreedyC         "};
  char* dataType[] = {"a","e","c"};
	if (argc <= 4)
	{
		printf ("usage: ./data-compare K M db D\n");
		return 0;
	}

	if (argc > 4)
  {
		K = atoi(argv[1]);
    M = atof(argv[2]);
    db = atoi(argv[3]);
    D = atoi(argv[4]);
  }
	sprintf(filename, "Data/datacmpare-k%d-db%d-D%d", K, db, D);
	fp = fopen(filename, "w");

	sprintf(filename, "Data/datacompare-k%d-db%d-D%d.log", K, db, D);
  log = fopen(filename, "w");

	for(N = 100; N <= 100000; N *= 10)
	{
		fprintf(fp, "%d", N);
		for(i = 0; i < NUM_METHODS; ++i)
		{
			rr[i] = 0.0;
		}
		for(j = 0; j < DATAREPEATS; ++j)
		{
      p = new struct point[N];
      maxIndex = new int[K];

      for (i = 0; i<3; i++)
      {
        sprintf(filename, "Data/%s%d-%d-%d.dat", dataType[i], D, N, j + 1);
        cout << filename << endl;

        p = readPoints(filename);
        p = scale(D,p,N);

        // Cube algorithm
        pPrime = transformforth(db,D,p,N);
  			cube(D, N, K, pPrime, maxIndex);

        LIB = 0;
  			rr[i] += evaluateRandomLIB(D, N, K, pPrime, maxIndex, REPEATS, LIB, db, VERBOSE, M);

  			printf("%s, n=%d, %lf s, %lf\n", methods[i], N ,rr[i]/(j+1));
  			fprintf(log, "%s, n=%d, %lf s, %lf\n", methods[i], N, rr[i]/(j+1));

        P = Cube2Sphere(D,pPrime,N);
        skyline = skyline_point(P);
        S = sphereWSImpLP(skyline,K);

        LIB = 0;

        for (int x = 0; x < K; x++){
          maxIndex[x] = S->points[x]->id;
        }

  			rr[i+3] += evaluateRandomLIB(D, N, K, pPrime, maxIndex, REPEATS, LIB, db, VERBOSE, M);

  			printf("%s, n=%d, %lf s, %lf\n", methods[i+3], N, rr[i+3]/(j+1));
  			fprintf(log, "%s, n=%d, %lf s, %lf\n", methods[i+3], N, rr[i+3]/(j+1));

        if (skyline->numberOfPoints > D)
        {
    			S = ImpGreedy(K, skyline);
          LIB= 0;

          for (int x = 0; x < K; x++){
            maxIndex[x] = S->points[x]->id;
          }

    			rr[i+6] += evaluateRandomLIB(D, N, K, pPrime , maxIndex, REPEATS, LIB, db, VERBOSE, M);

    			printf("%s, n=%d, %lf s, %lf\n", methods[i+6], N, rr[i+6]/(j+1));
    			fprintf(log, "%s, n=%d, %lf s, %lf\n", methods[i+6], N, rr[i+6]/(j+1));
        }
      }
      delete[] p;
      delete[] maxIndex;
      delete[] pPrime;
	   }
     printf("\n");
 		for(i = 0; i < NUM_METHODS; ++i)
 			fprintf(fp, "\t%lf", rr[i]/DATAREPEATS);
 		fprintf(fp, "\n");
 		fflush(fp);
   }

	// free up memory
  cout << "END" << endl;
	fclose(fp); fclose(log);

	return 0;
}
