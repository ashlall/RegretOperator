#include "point_cube.h"
#include <iostream>
#include <map>
#include <string>

#ifndef REGRETOPERATOR_MAX_HEAP_H
#define REGRETOPERATOR_MAX_HEAP_H

using namespace std;

class MaxHeap
{
private:
	int* bbound;
	std::string attToString(struct point p);

public:
	struct point* p;
	std::map<int, int> pos;
	int capacity;
	int heapsize;
	int t;      // the number of ranges to divide in each dimension
	int d;
	int d_comp; // dimension to compare

	MaxHeap();
	MaxHeap(int cap, int dimension, int dimension_comp);
	MaxHeap(int cap, struct point firstp, int dimension_comp);
	MaxHeap(int cap, int n, struct point* data, int dimension_comp);
	~MaxHeap();

	void clean();

	int leftchild  (int index);
	int rightchild (int index);
	int parent     (int index);

	bool empty();
	int  getIndex(struct point p);
	void setbound(int* bound);
	void setT    (int t_input);
	bool satisfy (struct point p);

	void heapify(int index);
	void buildheap();

	void swap(int i, int j);

	void insert(struct point p_new);
	void remove(struct point p_remov);
	void erase (int index);

	struct point& getmax();
	void pop();

	void print();
};

#endif
