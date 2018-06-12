#include "data_utility.h"

#include "operation.h"
#include "sphere.h"
#include "lp.h"

int main(int argc, char *argv[])
{
	if (argc < 3)
		return 0;

	char* input = argv[1];
	point_set_t* P = read_points(input);
	point_set_t* skyline = skyline_point(P);

	for (int i = 2; i < argc; i++)
	{
		int k = atoi(argv[i]);
		double mrr;
		point_set_t* S;

		printf("------------k = %d------------\n", k);
		printf("    Algorithm         MRR     \n");

		// Sphere
		S = sphereWSImpLP(skyline, k);
		mrr = evaluateLP(skyline, S, 0);
		//print_point_set(S);
		printf("      Sphere        %f\n", mrr);
		release_point_set(S, false);

		// ImpGreedy
		S = ImpGreedy(k, skyline);
		mrr = evaluateLP(skyline, S, 0);
		//print_point_set(S);
		printf("    ImpGreedy       %f\n", mrr);
		release_point_set(S, false);
	}
	
	release_point_set(skyline, false);
	release_point_set(P, true);

	return 0;

}