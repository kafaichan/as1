#pragma once
#include <stdio.h>
#include "edge.h"
#include "label.h"
#include "heap.h"
#include <time.h>

#pragma warning(disable:4996)

class PLL {
public:
	PLL(char* filename, int maxnode);
	~PLL();
	void construct_index();
	void create_query();
private:
	FILE* fin;
	int maxnode;
	bool* visit;
	int* dist;
	bool* used;
	Order* orderlist;
	LabelList* label_in, *label_out;
	EdgeList *graph, *reverse_graph;

	void AddEdge(EdgeList* elist, int from, int to, int weight);
	void construct_labels();
	void construct_label_in(EdgeList* elist, int source, int iter);
	void construct_label_out(EdgeList* elist, int source, int iter);
	void insert_label(LabelList* label, int idx, int iter, int val);
	int answer_by_label(int s, int t);
	void printGraph(EdgeList* elist);
	void printLabel(LabelList* list);
	void deleteGraph(EdgeList* elist);
	void dropHeader();
	void timespec_diff(timespec* start, timespec* end, timespec* result);
};
