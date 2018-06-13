//===================================================================
// This function implements the approximate algorithm for retrieving
// max-dominance representative skyline (Algorithm 1 in Lin et al. [ICDE'07])
// Coded by Danupon Nanongkai Nov. 16, 2009 
// MaxDom.h
//===================================================================

#ifndef MAXDOM
#define MAXDOM

void dominance_greedy(int D, int N, int K, struct point *s, int skylineSize, struct point *sky, int *maxIndex);

#endif
