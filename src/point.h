#ifndef POINT_H
#define POINT_H

struct point
{
    int d;
    double* a;
};

double dot(struct point, double*);
struct point maxPoint(int, struct point*, double*);
double print(struct point);
void sort(struct point*, int);
int equals(struct point, struct point);
int dominates(struct point, struct point);

#endif
