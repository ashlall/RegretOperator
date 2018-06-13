Readme (k-regret)
=========================
This package contains all source codes for 
1. Sphere
2. ImpGreedy

Usage Step
==========
a. Compilation
	make

	You will need to install the GLPK package (for solving LPs) at first.
	See GLPK webpage <http://www.gnu.org/software/glpk/glpk.html>.
    The Makefile should handle all compilation (once you get GLPK installed correctly).
	Note that "-lglpk" in the Makefile is the GLPK package and you may need to change it to the location where you installed the GLPK package.
	
b. Execution
	./run input.txt k ...
	where 
	input.txt - the input file which contains the data set (whose format will be described in Appendix A.)
	k - one or more parameter k for the k-regret query
	
	
c. Output
   1. The output will be shown on the console

Example
=======
Sample input are provided. Try:
./run dataset.txt 6 12 24 36 48 60

The output is 
------------k = 6------------
    Algorithm         MRR
      Sphere        0.260330
    ImpGreedy       0.260330
------------k = 12------------
    Algorithm         MRR
      Sphere        0.106567
    ImpGreedy       0.152576
------------k = 24------------
    Algorithm         MRR
      Sphere        0.050424
    ImpGreedy       0.050582
------------k = 36------------
    Algorithm         MRR
      Sphere        0.032160
    ImpGreedy       0.033953
------------k = 48------------
    Algorithm         MRR
      Sphere        0.026491
    ImpGreedy       0.027747
------------k = 60------------
    Algorithm         MRR
      Sphere        0.020462
    ImpGreedy       0.023104


Appendix A. Format of Input file
------------------------------------
The format of the first line is: n d
n - number of points in the data set, integer
d - dimensionality, integer
The format of the following n lines is
<dim 1> <dim 2> ... <dim d>.
Each line corresponds to a point.