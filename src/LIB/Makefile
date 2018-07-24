#Makefile for Writing Make Files Example

#***************************************************
#Variables to control Makefile operation

CXX = g++
CXXFLAGS = -w -std=c++11
OBJ = point.o cube.o LIB_Util.o sphere.o data_utility.o operation.o lp.o
#***************************************************
#Targets needed to bring the executable up to date

all:	nba_vary-K	datacompare	vary-D	vary-M	vary-db	vary-N	vary-K	generatedata split clean

datacompare: data-compare.o point.o cube.o LIB_Util.o sphere.o data_utility.o operation.o lp.o
		$(CXX) $(CXXFLAGS) -o datacompare $(OBJ) data-compare.o -lglpk -lm

generatedata: generatedata.o
		$(CXX) $(CXXFLAGS) -o generatedata generatedata.o

split: split.o
		$(CXX) $(CXXFLAGS) -o split split.o

nba_vary-K: nba_vary-K.o point.o cube.o LIB_Util.o sphere.o data_utility.o operation.o lp.o
		$(CXX) $(CXXFLAGS) -o nba_vary-K $(OBJ) nba_vary-K.o -lglpk -lm


vary-D: vary-D.o point.o cube.o LIB_Util.o sphere.o data_utility.o operation.o lp.o
		$(CXX) $(CXXFLAGS) -o vary-D $(OBJ) vary-D.o -lglpk -lm

vary-M:  vary-M.o point.o cube.o LIB_Util.o sphere.o data_utility.o operation.o lp.o
		$(CXX) $(CXXFLAGS) -o vary-M $(OBJ) vary-M.o -lglpk -lm

vary-N:  vary-N.o point.o cube.o LIB_Util.o sphere.o data_utility.o operation.o lp.o
		$(CXX) $(CXXFLAGS) -o vary-N $(OBJ) vary-N.o -lglpk -lm

vary-db:  vary-db.o point.o cube.o LIB_Util.o sphere.o data_utility.o operation.o lp.o
		$(CXX) $(CXXFLAGS) -o vary-db $(OBJ) vary-db.o -lglpk -lm

vary-K:  vary-K.o point.o cube.o LIB_Util.o sphere.o data_utility.o operation.o lp.o
		$(CXX) $(CXXFLAGS) -o vary-K $(OBJ) vary-K.o -lglpk -lm
#the test_phere.o target can be written more simply

generatedata.o:
	$(CXX) $(CXXFLAGS) -c generatedata.cpp

split.o:
	$(CXX) $(CXXFLAGS) -c split.cpp

nba_vary-K.o: nba_vary-K.cpp
	$(CXX) $(CXXFLAGS) -c nba_vary-K.cpp

data-compare.o: data-compare.cpp
	$(CXX) $(CXXFLAGS) -c data-compare.cpp

vary-K.o: vary-K.cpp
	$(CXX) $(CXXFLAGS) -c vary-K.cpp

vary-M.o: vary-M.cpp
	$(CXX) $(CXXFLAGS) -c vary-M.cpp


vary-N.o: vary-N.cpp
	$(CXX) $(CXXFLAGS) -c vary-N.cpp


vary-db.o: vary-db.cpp
	$(CXX) $(CXXFLAGS) -c vary-db.cpp

vary-D.o: vary-D.cpp
	$(CXX) $(CXXFLAGS) -c vary-D.cpp

point.o: point.h

cube.o: cube.h point.h

LIB_Util.o: LIB_Util.h point.h data_utility.h

data_utility.o: data_utility.cpp
	$(CXX) $(CXXFLAGS) -c data_utility.cpp

lp.o: data_utility.h operation.h lp.cpp
	$(CXX) $(CXXFLAGS) -c lp.cpp

operation.o: data_utility.h operation.cpp
	$(CXX) $(CXXFLAGS) -c operation.cpp

sphere.o: data_utility.h operation.h lp.h sphere.cpp
	$(CXX) $(CXXFLAGS) -c sphere.cpp

clean:
	rm *.o
