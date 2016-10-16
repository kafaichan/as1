#pragma once
#include <stdio.h>

class Edge {
public:
	int end;
	int weight;
	Edge* next;
	Edge(int _end, int _weight) :end(_end), weight(_weight),next(NULL) {}
};

class EdgeList {
public:
	Edge* begin; 
	Edge* end;
	EdgeList() {
		begin = end = NULL;
	}
};