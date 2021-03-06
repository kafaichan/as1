#pragma once
#include "edge.h"
#include "heap.h"
#include <stdio.h>
#include <time.h>
#include <unordered_map>
using namespace std; 
//#pragma warning(disable:4996)

class Dijkstra {
public:
	Dijkstra(char* filename, int maxnode);
	~Dijkstra();
	void construct_index();
	void create_query();
	int answer_query(int s, int t);
private:
	FILE* fin;
	EdgeList* graph;
	bool* visit;
	int* dist;
	int maxnode;
	void dropHeader();
	void timespec_diff(timespec* start, timespec* end, timespec* result);
};