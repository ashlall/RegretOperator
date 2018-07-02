#include "LIB_Util.h"

point* scale(int D, struct point* p, int N)
{
	int i,j = 0;
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
	struct point* pprime = new struct point[N];

	//do transformation
  for(int i = 0;i<N;i++)
	{
    pprime[i].a = new double[D];
		for(int j = 0;j<D;j++)
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
	struct point* pprime = new struct point[N];

	//do transformation
	for(i = 0;i<N;i++)
  {
    pprime[i].a = new double[D];
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
