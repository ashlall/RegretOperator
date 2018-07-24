#include "maxheap.h"

MaxHeap::MaxHeap()
{
	p = NULL;
	capacity = 0;
	heapsize = 0;
	d = 0;
	d_comp = 0;
}

MaxHeap::MaxHeap(int cap, int dimension, int dimension_comp)
{
	capacity = cap;
	heapsize = 0;
	d = dimension;
	d_comp = dimension_comp;
	p = new struct point[capacity];
	bbound = new int[d];

	for (int i = 0; i < capacity; ++i)
	{
		p[i].d = d;
		p[i].a = new double[d];
	}
}

MaxHeap::MaxHeap(int cap, struct point firstp, int dimension_comp)
{
	capacity = cap;
	heapsize = 1;
	d = firstp.d;
	d_comp = dimension_comp;
	p = new struct point[capacity];
	bbound = new int[d];

	for (int i = 0; i < capacity; ++i)
	{
		p[i].d = d;
		p[i].a = new double[d];
	}
	copypoint(p[0],firstp);
	pos[p[0].id] = 0;
}

MaxHeap::MaxHeap(int cap, int n, struct point* data, int dimension_comp)
{
	capacity = cap;
	heapsize = n;
	d = data[0].d;
	d_comp = dimension_comp;
	p = new struct point[capacity];
	bbound = new int[d];

	for (int i = 0; i < capacity; ++i)
	{
		p[i].d = d;
		p[i].a = new double[d];
	}

	for (int i = 0; i < n; ++i)
	{
		copypoint(p[i],data[i]);
		pos[p[i].id] = i;
	}

	buildheap();
}

MaxHeap::~MaxHeap()
{
	for (int i = 0; i < capacity; ++i)
		delete[] p[i].a;
	delete[] p;
	delete[] bbound;
}

void MaxHeap::clean()
{
	for (int i = 0; i < capacity; ++i)
		delete[] p[i].a;
	delete[] p;
	delete[] bbound;
}

std::string MaxHeap::attToString(struct point p)
{
	std::string s = "";
	for (int i = 0; i < d-1; ++i)
		s += std::to_string(p.a[i]) + ',';
	s += std::to_string(p.a[d-1]);
	return s;
}

int MaxHeap::leftchild(int index)
{
	return 2*index + 1;
}

int MaxHeap::rightchild(int index)
{
	return 2*index + 2;
}

int MaxHeap::parent(int index)
{
	return (index-1) / 2;
}

bool MaxHeap::empty()
{
	return heapsize == 0;
}

int MaxHeap::getIndex(struct point p)
{
	if (pos.find(p.id) != pos.end())
		return pos[p.id];
	return -1;
}

void MaxHeap::setbound(int* bound)
{
	for (int i = 0; i < d; ++i)
		bbound[i] = bound[i];
}

void MaxHeap::setT(int t_input)
{
	t = t_input;
}

bool MaxHeap::satisfy(struct point p)
{
	for (int i = 0; i < d; ++i)
	{
		int j = p.a[i] / t;
		if (t-1 < j)
			j = t - 1;

		if (j != bbound[i])
			return false;
	}
	return true;
}

void MaxHeap::swap(int i, int j)
{
	// switch position in the map
	pos[p[i].id] = j;
	pos[p[j].id] = i;

	struct point t;
	t.a = new double[p[i].d];
	copypoint(t,p[i]);
	copypoint(p[i],p[j]);
	copypoint(p[j],t);

	delete t.a;
}

void MaxHeap::heapify(int index)
{
	if (index < heapsize)
	{
		int maxIndex = index;
		int left = leftchild(index);
		int right = rightchild(index);

		// determine which node is the biggest: parent, left or right
		if (left < heapsize && p[maxIndex].a[d_comp] < p[left].a[d_comp])
			maxIndex = left;
		if (right < heapsize && p[maxIndex].a[d_comp] < p[right].a[d_comp])
			maxIndex = right;
		if (maxIndex != index)
		{
			swap(maxIndex,index);
			heapify(maxIndex);
		}
	}
}

void MaxHeap::buildheap()
{
	for (int i = heapsize/2; i >=0; --i)
		heapify(i);
}

void MaxHeap::insert(struct point p_new)
{
	copypoint(p[heapsize],p_new);
	pos[p[heapsize].id] = heapsize;
	++heapsize;
	int i = heapsize - 1;
	while (i != 0 && p[i].a[d_comp] > p[parent(i)].a[d_comp])
	{
		swap(i, parent(i));
		i = parent(i);
	}
}

void MaxHeap::remove(struct point p_remov)
{
	// find index of the point to remove
	int index_remov = getIndex(p_remov);

	if (index_remov != -1)
	{
		// switch with the last element
		swap(index_remov,heapsize-1);
		--heapsize;
		int i = index_remov;
		while (i != 0 && p[i].a[d_comp] > p[parent(i)].a[d_comp])
		{
			swap(i,parent(i));
			i = parent(i);
		}
	}
}

void MaxHeap::erase(int index)
{
	double largeNum = 10000000000;
	// increase key of the point to remove so it becomes root
	p[index].a[d_comp] = largeNum;
	int i = index;
	while (i != 0 && p[i].a[d_comp] > p[parent(i)].a[d_comp])
	{
		swap(i,parent(i));
		i = parent(i);
	}
	pop();
}

void MaxHeap::pop()
{
	copypoint(p[0],p[heapsize-1]);
	--heapsize;
	heapify(0);
}

struct point& MaxHeap::getmax()
{
	return p[0];
}

void MaxHeap::print()
{
	for (int i = 0; i < heapsize; ++i)
	{
		for (int j = 0; j < d; ++j)
			std::cout << p[i].a[j] << ' ';
		std::cout << '\n';
	}
}
