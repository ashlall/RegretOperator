#include "point.h"

#ifndef POINTCPP
#define POINTCPP

#include <iostream>
#include <stdio.h>

using namespace std;

double dot(struct point p, double* w)
{
	double product = 0.0;
	int i;

	for(i = 0; i < p.d; ++i)
		product += p.a[i] * w[i];

	return product;
}

// finds the point in p farthest in the direction v
struct point maxPoint(int N, struct point *p, double *v)
{
	int i, maxIndex = 0;
	double max = 0.0;
	
	for(i = 0; i < N; ++i)
		if (dot(p[i], v) > max)
		{
			maxIndex = i;
			max = dot(p[i], v);
		}

	return p[maxIndex];
}
		


double print(struct point p)
{
	int i;
	for(i = 0; i < p.d; ++i)
		printf("%lf ", p.a[i]);
	printf("\n");
	
	//Actually, what the heck should this return? Currently, I'm just placing an arbitrary value here, so note that THIS IS BROKEN
	return 0;
	
}

int pointcmp(const void *a, const void *b) 
{
	int i;

	for(i = 0; i < ((struct point*)a)->d; ++i)
	{ 
		if (((struct point*)a)->a[i] < ((struct point*)b)->a[i]) return -1;
		if (((struct point*)a)->a[i] > ((struct point*)b)->a[i]) return 1;
	}

	return 0;
}



/*
//This is commented out, because I implement a different sorting algorithm in newAlgorithmTest.cpp

void sort(struct point* p, int n)
{
	qsort(p, n, sizeof(struct point), pointcmp);
}*/



// checks if p1 dominates p2
// assumes p1.d == p2.d 
// points dominate themselves
int dominates(struct point p1, struct point p2)
{
	int i;

	for(i = 0; i < p1.d; ++i)
		if (p1.a[i] < p2.a[i])
			return 0;

	return 1;
}

// checks if two points are equal
int equals(struct point p1, struct point p2)
{
	return pointcmp(&p1, &p2) == 0;
}

#endif 
