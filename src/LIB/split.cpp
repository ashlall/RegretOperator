/* split.c
This program takes a point data file of size N and splits it k ways
Assumes that number of points is a multiple of k
*/

#include <stdio.h>

int main(int argc, char** argv)
{
	int i, j, l, size, k;
	int N, D;
	FILE* in;
	FILE* out;
	char filename[1024];
	double num;

	if (argc < 2)
	{
		printf("Usage: split filename num-split\n");
		return -1;
	}

	k = atoi(argv[2]);

	// read points from file
	sprintf(filename, "Data/%s", argv[1]);
	in = fopen(filename, "r");

	if (in == NULL)
	{
		printf("File %s not found.\n", filename);
		return -1;
	}

	fscanf(in, "%d %d\n", &N, &D);

	if (N % k != 0)
	{
		printf("Number of points %d should be a multiple of %d\n", N, k);
		return -1;
	}

	size = N / k;
	printf("Creating %d files each with %d points (%d dimensions)\n", k, size, D);

	for(i = 0; i < k; ++i)
	{
		if (argc > 3)
			sprintf(filename, "Data/%s-%d.dat", argv[3], i + 1);
		else
			sprintf(filename, "Data/%d-%s", i + 1, argv[1]);
		out = fopen(filename, "w");
		fprintf(out, "%d %d\n", size, D);

		for(j = 0; j < size; ++j)
		{
			for(l = 0; l < D; ++l)
			{
				fscanf(in, "%lf", &num);
				fprintf(out, "%lf ", num);
			}
			fprintf(out, "\n");
		}

		fclose(out);
	}

	fclose(in);

	return 0;
}
