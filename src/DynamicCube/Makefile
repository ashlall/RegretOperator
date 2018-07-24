# ---------Variables----------
CXX = g++
FLAGS = -std=c++0x -w
OBJ = cube.o point_cube.o cube_dynamic.o operation_cube.o lp_cube.o maxheap.o sphere.o data_utility.o lp.o operation.o impgreedy.o
OBJ_real = cube.o point_cube.o cube_dynamic.o operation_cube.o lp_cube.o maxheap.o

# ----------Compile-----------
all: varyn varym varyd varyk real makeplot

varyn: varyn.o cube.o point_cube.o cube_dynamic.o operation_cube.o lp_cube.o maxheap.o sphere.o data_utility.o lp.o operation.o impgreedy.o
	$(CXX) $(FLAGS) -o varyn varyn.o $(OBJ) -lglpk -lm
	
varym: varym.o cube.o point_cube.o cube_dynamic.o operation_cube.o lp_cube.o maxheap.o sphere.o data_utility.o lp.o operation.o impgreedy.o
	$(CXX) $(FLAGS) -o varym varym.o $(OBJ) -lglpk -lm
	
varyd: varyd.o cube.o point_cube.o cube_dynamic.o operation_cube.o lp_cube.o maxheap.o sphere.o data_utility.o lp.o operation.o impgreedy.o
	$(CXX) $(FLAGS) -o varyd varyd.o $(OBJ) -lglpk -lm

varyk: varyk.o cube.o point_cube.o cube_dynamic.o operation_cube.o lp_cube.o maxheap.o sphere.o data_utility.o lp.o operation.o impgreedy.o
	$(CXX) $(FLAGS) -o varyk varyk.o $(OBJ) -lglpk -lm
	
real: testrealdata.o cube.o point_cube.o cube_dynamic.o operation_cube.o lp_cube.o maxheap.o
	$(CXX) $(FLAGS) -o testrealdata testrealdata.o $(OBJ_real) -lglpk -lm
	
makeplot: makeplot.o
	$(CXX) $(FLAGS) -o makeplot makeplot.o

varyn.o: varyn.cpp cube.h cube_dynamic.h sphere.h impgreedy.h data_utility.h point_cube.h
	$(CXX) $(FLAGS) -c varyn.cpp
	
varym.o: varym.cpp cube.h cube_dynamic.h sphere.h impgreedy.h data_utility.h point_cube.h
	$(CXX) $(FLAGS) -c varym.cpp
	
varyd.o: varyd.cpp cube.h cube_dynamic.h sphere.h impgreedy.h data_utility.h point_cube.h
	$(CXX) $(FLAGS) -c varyd.cpp
	
varyk.o: varyk.cpp cube.h cube_dynamic.h sphere.h impgreedy.h data_utility.h point_cube.h
	$(CXX) $(FLAGS) -c varyk.cpp
	
testrealdata.o: testrealdata.cpp cube.h cube_dynamic.h point_cube.h
	$(CXX) $(FLAGS) -c testrealdata.cpp

cube.o: cube.cpp point_cube.h
	$(CXX) $(FLAGS) -c cube.cpp

point_cube.o: point_cube.cpp 
	$(CXX) $(FLAGS) -c point_cube.cpp

cube_dynamic.o: cube_dynamic.cpp lp_cube.h operation_cube.h point_cube.h maxheap.h
	$(CXX) $(FLAGS) -c cube_dynamic.cpp

operation_cube.o: operation_cube.cpp point_cube.h
	$(CXX) $(FLAGS) -c operation_cube.cpp

lp_cube.o: lp_cube.cpp point_cube.h
	$(CXX) $(FLAGS) -c lp_cube.cpp

maxheap.o: maxheap.cpp point_cube.h
	$(CXX) $(FLAGS) -c maxheap.cpp

sphere.o: sphere.cpp data_utility.h operation.h lp.h
	$(CXX) $(FLAGS) -c sphere.cpp

data_utility.o: data_utility.cpp 
	$(CXX) $(FLAGS) -c data_utility.cpp

lp.o: lp.cpp data_utility.h operation.h
	$(CXX) $(FLAGS) -c lp.cpp

operation.o: operation.cpp data_utility.h
	$(CXX) $(FLAGS) -c operation.cpp

impgreedy.o: impgreedy.cpp data_utility.h operation.h lp.h
	$(CXX) $(FLAGS) -c impgreedy.cpp
	
makeplot.o: makeplot.cpp
	$(CXX) $(FLAGS) -c makeplot.cpp
	
clean:
	rm *.o
