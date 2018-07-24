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

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

const string dir = "Results/";
const string input_ins_files[3] = {"varyn.log","varyd.log","varyk.log"};
const string input_del_files[3] = {"varyn-del.log","varyd-del.log","varyk-del.log"};

enum {RRATIO, RTIME};

void makeplot(char test_type, int plot_type, string filename);

// Usage: ./makeplot <N|D|K> <(I)nsert|(D)elete>
int main(int argc, char* argv[])
{
	int index;

	int info1, info2;
	int tests;
	
	if (argc != 2 && argc != 3)
	{
		cout << "Usage: ./makeplot <N|D|K> <(I)nsert|(D)elete>\n";
		cout << "   or: ./makeplot <input>\n";
		cout << "Inputs include: varym, realdataset\n";
		return 0;
	}
	
	if (argc == 2)
	{
		string inputname = argv[1];
		if (inputname == "varym")
		{
			ifstream input("Results/varym.log");
			ofstream output_rt("varym_rt.txt");
			ofstream output_rr("varym_rr.txt");
			int info3;
			input >> info1;
			input >> info2;
			input >> info3;
			input >> tests;
			for (int i = 0; i < tests; ++i)
			{
				double m;
				double xvalue;
				input >> m;
				output_rt << m << ' ';
				output_rr << m << ' ';
				
				input >> xvalue;
				output_rt << xvalue << endl;
				
				input >> xvalue;
				output_rr << xvalue*100 << endl;
				
				// discard unused inputs
				for (int j = 0; j < 5; ++j)
					input >> xvalue;
			}
			input.close();
			output_rt.close();
			output_rr.close();
			
			makeplot('m', RRATIO, "varym_rr");
			makeplot('m', RTIME, "varym_rt");
			
			system("gnuplot varym_rr.plot");
			system("gnuplot varym_rt.plot");
		}
		system("rm *.plot");
		system("rm *.txt");
		return 0;
	}

	switch(argv[1][0])
	{
		case 'n':
		case 'N':
			index = 0;
			break;
		case 'd':
		case 'D':
			index = 1;
			break;
		case 'k':
		case 'K':
			index = 2;
			break;
		default:
			index = 0;
	};

	char test_type = argv[2][0];
	char test_att = argv[1][0];
	if (test_type == 'i' || test_type == 'I')
	{
		int ALGO_NUM = 4;
		ifstream input(dir + input_ins_files[index]);

		if (test_att == 'N')
			test_att = 'n';
		else if (test_att == 'D')
			test_att = 'd';
		else if (test_att == 'K')
			test_att = 'k';

		string outputname = "vary";
		outputname += test_att;

		ofstream output_rt(outputname + "_rt.txt");
		ofstream output_rr(outputname + "_rr.txt");

		input >> info1;
		input >> info2;
		input >> tests;

		for (int i = 0; i < tests; ++i)
		{
			int xvalue;
			input >> xvalue;
			output_rt << xvalue << ' ';
			output_rr << xvalue << ' ';
			double running_time;
			double avg_rr;

			for (int algo = 0; algo < ALGO_NUM; ++algo)
			{
				input >> running_time;
				output_rt << running_time << ' ';

				input >> avg_rr;
				output_rr << avg_rr*100 << ' ';

				// discard other inputs
				for (int j = 0; j < 5; ++j)
					input >> running_time;
			}

			output_rt << endl;
			output_rr << endl;
		}

		input.close();
		output_rt.close();
		output_rr.close();

		makeplot(test_type, RTIME, outputname + "_rt");
		makeplot(test_type, RRATIO, outputname + "_rr");

		string command_rt = "gnuplot " + outputname + "_rt.plot";
		string command_rr = "gnuplot " + outputname + "_rr.plot";
		system(command_rt.c_str());
		system(command_rr.c_str());
	}

	// Deletion
	if (test_type == 'd' || test_type == 'D')
	{
		int ALGO_NUM = 2;
		ifstream input(dir + input_del_files[index]);

		if (test_att == 'N')
			test_att = 'n';
		else if (test_att == 'D')
			test_att = 'd';
		else if (test_att == 'K')
			test_att = 'k';

		string outputname = "vary";
		outputname += test_att;

		ofstream output_rt(outputname + "_del_rt.txt");
		ofstream output_rr(outputname + "_del_rr.txt");

		input >> info1;
		input >> info2;
		input >> tests;

		for (int i = 0; i < tests; ++i)
		{
			int xvalue;
			input >> xvalue;
			output_rt << xvalue << ' ';
			output_rr << xvalue << ' ';
			double running_time;
			double avg_rr;

			for (int algo = 0; algo < ALGO_NUM; ++algo)
			{
				input >> running_time;
				output_rt << running_time << ' ';

				input >> avg_rr;
				output_rr << avg_rr*100 << ' ';

				// discard other inputs
				for (int j = 0; j < 5; ++j)
					input >> running_time;
			}

			output_rt << endl;
			output_rr << endl;
		}

		input.close();
		output_rt.close();
		output_rr.close();

		makeplot(test_type, RTIME, outputname + "_del_rt");
		makeplot(test_type, RRATIO, outputname + "_del_rr");

		string command_rt = "gnuplot " + outputname + "_del_rt.plot";
		string command_rr = "gnuplot " + outputname + "_del_rr.plot";
		system(command_rt.c_str());
		system(command_rr.c_str());
	}

	system("rm *.txt");
	system("rm *.plot");

	return 0;
}

// plot_type: regret ratio (RRATIO) or time (RTIME)
void makeplot(char test_type, int plot_type, string filename)
{
	string file = filename + ".txt";
	ofstream output(filename + ".plot");

	char att = filename[4];

	output << "set term postscript eps color\n";
	output << "set output \"Plots/" << filename << ".eps\"\n";
	output << "set size 0.5,0.5\n";
	output << "set key top left\n";
	output << "set xlabel \"" << att << "\"\n";

	if (plot_type == 0)
	{
		output << "set ylabel \"Average MRR\"\n";
		output << "set format y \"%2.0f%%\"\n";
	}
	else
	{
		output << "set ylabel \"Time (seconds)\"\n";
		output << "set logscale y\n";
	}

	if (att == 'n')
	{
		output << "set xtics (100, 1000, 10000)\n";
		output << "set logscale x\n";
	}
	else if (att == 'd')
	{
		output << "set xtics (2,3,4,5,6)\n";
	}
	else if (att == 'k')
	{
		output << "set xtics (20, 25, 30, 35, 40)\n";
	}
	else if (att == 'm')
	{
		//output << "set logscale x\n";
	}

	if (test_type == 'i')
	{
		output << "plot \"" << file << "\" using  1:2 title 'Cube' with linespoints lw 2, \""
			   << file << "\" using 1:3 title 'Dynamic Cube' with linespoints lw 2, \""
			   << file << "\" using 1:4 title 'Sphere' with linespoints lw 2, \""
			   << file << "\" using 1:5 title 'ImpGreedy' with linespoints lw 2\n";
	}
	else if (test_type == 'd')
	{
		output << "plot \"" << file << "\" using  1:2 title 'Cube' with linespoints lw 2, \""
			   << file << "\" using 1:3 title 'Dynamic Cube' with linespoints lw 2\n";
	}
	else if (test_type == 'm')
	{
		if (plot_type == 0)
			output << "plot \"" << file << "\" using 1:2 title 'Average MRR' with linespoints lw 2\n";
		else
			output << "plot \"" << file << "\" using 1:2 title 'Running Time' with linespoints lw 2\n";
	}

	output.close();
}
