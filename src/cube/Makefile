#Makefile for Writing Make Files Example

#***************************************************
#Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -std=c++11
OBJ = LIBtest.o point.o LIB_Util.o
#***************************************************
#Targets needed to bring the executable up to date

all:	main

main: LIBtest.o point.o LIB_Util.o
		$(CXX) $(CXXFLAGS) -o main $(OBJ)

#the test_phere.o target can be written more simply
LIBtest.o:  LIBtest.cpp LIB_Util.h point.h
		$(CXX) $(CXXFLAGS) -c LIBtest.cpp

point.o: point.cpp point.h
	$(CXX) $(CXXFLAGS) -c point.cpp

LIB_Util.o: LIB_Util.cpp LIB_Util.h point.h
	$(CXX) $(CXXFLAGS) -c LIB_Util.cpp
