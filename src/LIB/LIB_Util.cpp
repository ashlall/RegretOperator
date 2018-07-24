#include "LIB_Util.h"


point_set_t* Cube2Sphere(int D, struct point* p, int N)
{
    point_set_t* Sp = alloc_point_set(N);
    for (int i = 0; i < N ;i++){
      Sp->points[i]= alloc_point(D,i);
      for(int j = 0; j < D; j++)
        Sp->points[i]->coord[j]= p[i].a[j];
    }
    return Sp;
}

point* scale(int D, struct point* p, int N)
{
	int i,j;
	double c[D];

	for(i = 0; i < D; ++i)
		c[i] = p[0].a[i]; // initialize with first point

  for(i = 0; i < N; ++i) //Find maximal points in each direction
		for(j = 0; j < D; ++j)
			if (p[i].a[j] > c[j])
				c[j] = p[i].a[j];

	//rescale all points in database
	for(i = 0;i<N;i++)
	{
		for(j = 0;j<D;j++)
		{
			p[i].a[j] = p[i].a[j] / c[j];
		}
	}
  return p;
}

point* transformforth(int db, int D, struct point *p, int N)
{
  int i,j;
	struct point* pprime = new struct point[N];

	//do transformation
  for(i = 0;i<N;i++)
	{
    pprime[i].a = new double[D];
    pprime[i].d = D;
		for(j = 0;j<D;j++)
		{
			if(j>db-1)
			{
				pprime[i].a[j] = 1-p[i].a[j];
			}
			else
			{
				pprime[i].a[j] = p[i].a[j];
			}
		}
	}
	return pprime;
}

point* transformback(int db, int D, struct point *p, int N)
{
  int i, j;
	struct point* pprime = new struct point[N];
	//do transformation
	for(i = 0;i<N;i++)
  {
    pprime[i].a = new double[D];
    pprime[i].d = D;
	   for(j = 0;j<D;j++)
     {
			if(j>db-1)
			{
				pprime[i].a[j] = (-1*p[i].a[j])+1;
			}
			else
			{
				pprime[i].a[j] = p[i].a[j];
			}
		}
	}
	return pprime;
}



double evaluateRandomLIB(int D, int N, int K, struct point *p, int *maxIndex, int REPEATS, int LIB, int db, int VERBOSE, double M)
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
    {
      if (j > db-1 && LIB == 1){
        sample[j] = -((double )rand()/RAND_MAX);
        // cout << sample[j]<< endl;
      }
      else
      {
			   sample[j] = ((double )rand()/RAND_MAX);
        //  cout << sample[j] << endl;
       }
    }

    //maxK: gain of a subset
		maxK = 0.0;
		for(j = 0; j < K; ++j){
      // cout << "Dot product: "<<dot(p[maxIndex[j]], sample) << endl;
			if (dot(p[maxIndex[j]], sample) > maxK){
        // cout << "update" <<endl;
				maxK = dot(p[maxIndex[j]], sample);
      }
    }
    //maxN: gain of a set p
		maxN = 0.0;
    for(j = 0; j < N; ++j)
			if (dot(p[j], sample) > maxN)
				maxN = dot(p[j], sample);

    // cout <<"maxK:" << maxK << endl;
    // cout << "maxK:" << maxK << endl;
    if (maxK < M )
    {
        maxK = M;
        // printf("MRR original set < M\n");
    }
    if (maxN < M)
    {
      // cout << "maxN:" << maxN << endl;
      maxN = M;
      // printf("MMR subset < M \n");
    }
		avgSum += 1.0 - maxK/maxN;
		if (1.0 - maxK/maxN > maxRegret)
			maxRegret = 1.0 - maxK/maxN;
	}

  if (maxRegret == 0){
    printf("THIS ONE HAS 0 REGRET RATIO\n");
  }
	if (VERBOSE)
		printf("Average/max regret ratio over %d random trials: %lf / %lf\n", REPEATS, (avgSum/REPEATS), maxRegret);

	return maxRegret;
}
