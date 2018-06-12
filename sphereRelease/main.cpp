//==========================================================================================
//Copyright 2018 ©, 2018 Minh Do, Hiep phan, Quang, Nguyen, Matthew Rinker, Ashwin Lall
//
//This file is a part of the RegretOperator project.
//
//The RegretOperator project is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    The RegretOperator project is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.
//==========================================================================================

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
