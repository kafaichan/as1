#include "pll.h"
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <queue>
#include <vector>
#include <algorithm>
//#include <boost\heap\fibonacci_heap.hpp>
//#include <boost\container\vector.hpp>
using namespace std;

#define INF 40000000
#define bike 

//#define boosttest

PLL::PLL(char* filename, int maxnode) {
	fin = fopen(filename, "r");
	if (fin == NULL) {
		fprintf(stderr, "Error opening file\n");
		exit(-1);
	}
	this->maxnode = maxnode;
	this->graph = new EdgeList[maxnode + 1];
	this->reverse_graph = new EdgeList[maxnode + 1];
	this->visit = new bool[maxnode + 1];
	this->dist = new int[maxnode + 1];
	this->used = new bool[maxnode + 1];
	this->orderlist = new Order[maxnode + 1];
	this->label_in = new LabelList[maxnode + 1];
	this->label_out = new LabelList[maxnode + 1];

	for (int i = 0; i < maxnode + 1; ++i) {
		orderlist[i].idx = i;
		visit[i] = false;
		dist[i] = INF;
		used[i] = false;
		//label_out[i].begin = label_out[i].end = label_in[i].begin = label_in[i].end = NULL;
	}
}

void PLL::construct_index() {
	timespec start, stop, result;
	timespec_get(&start, TIME_UTC);

#ifdef roadnet
	dropHeader();
#endif

	char buffer[1024];
	int fromNodeId, toNodeId;
	int weight = 1;

	while (fgets(buffer, 1024, fin)) {
#ifdef test
		sscanf(buffer, "%d%d%d", &fromNodeId, &toNodeId, &weight);
#else
		sscanf(buffer, "%d%d", &fromNodeId, &toNodeId);
#endif
		AddEdge(graph, fromNodeId, toNodeId, weight);
		AddEdge(reverse_graph, toNodeId, fromNodeId, weight);

		//for simplicity, consider both indegree and outdegree
		orderlist[fromNodeId].degree++;
		orderlist[toNodeId].degree++;
	}
	//create order
	sort(orderlist, orderlist + maxnode + 1);
	construct_labels();

	timespec_get(&stop, TIME_UTC);
	timespec_diff(&start, &stop, &result);
	printf("%.9fms\n", (difftime(result.tv_sec, 0) * 1000000000 + result.tv_nsec) / 1000000.0);
}

void PLL::construct_label_in(EdgeList* g, int s, int iter) {
#ifndef boosttest
	vector<int> visit_idx;  //avoid o(n) time initiliazation
	priority_queue<HeapNode> pq;
#else
	boost::heap::fibonacci_heap<HeapNode, boost::heap::compare<decreaseHeapNode> > pq;
	boost::container::vector<int> visit_idx;
#endif
	//visit[s] = true;
	dist[s] = 0;
	HeapNode hnode = HeapNode(s, 0);
	pq.push(hnode);

	while (!pq.empty()) {
		HeapNode top = pq.top();
		int idx = top.idx;
		if (visit[idx]) {
			pq.pop();
			continue;
		}
		visit[idx] = true;
		visit_idx.push_back(idx);
		pq.pop();

		if (answer_by_label(s, idx) <= dist[idx])continue;
		insert_label(label_in, idx, iter, dist[idx]);

		EdgeList elist = g[idx];
		for (Edge* e = elist.begin; e != NULL; e = e->next) {
			if (!visit[e->end] && !used[e->end] && dist[idx] + e->weight < dist[e->end]) {
				dist[e->end] = dist[idx] + e->weight;
				HeapNode hn = HeapNode(e->end, dist[e->end]);
				pq.push(hn);
			}
		}
	}

	//do the initializaton again
#ifndef boosttest
	vector<int>::iterator it;
#else
	boost::container::vector<int>::iterator it;
#endif
	for (it = visit_idx.begin(); it != visit_idx.end(); ++it) {
		visit[*it] = false;
		dist[*it] = INF;
	}
}

void PLL::construct_label_out(EdgeList * g, int s, int iter)
{
#ifndef boosttest
	vector<int> visit_idx;  //avoid o(n) time initiliazation
	priority_queue<HeapNode> pq;
#else
	boost::heap::fibonacci_heap<HeapNode, boost::heap::compare<decreaseHeapNode> > pq;
	boost::container::vector<int> visit_idx;
#endif
	dist[s] = 0;
	HeapNode hnode = HeapNode(s, 0);
	pq.push(hnode);

	while (!pq.empty()) {
		HeapNode top = pq.top();
		int idx = top.idx;
		if (visit[idx]) {
			pq.pop();
			continue;
		}
		visit[idx] = true;
		visit_idx.push_back(idx);
		pq.pop();

		if (answer_by_label(idx, s) <= dist[idx])continue;
		insert_label(label_out, idx, iter, dist[idx]);

		EdgeList elist = g[idx];
		for (Edge* e = elist.begin; e != NULL; e = e->next) {
			if (!visit[e->end] && !used[e->end] && dist[idx] + e->weight < dist[e->end]) {
				dist[e->end] = dist[idx] + e->weight;
				HeapNode hn = HeapNode(e->end, dist[e->end]);
				pq.push(hn);
			}
		}
	}

	//do the initializaton again
#ifndef boosttest
		vector<int>::iterator it;
#else
		boost::container::vector<int>::iterator it;
#endif
		for (it = visit_idx.begin(); it != visit_idx.end(); ++it) {
			visit[*it] = false;
			dist[*it] = INF;
		}
}

void PLL::construct_labels() {
#ifdef test
	orderlist[0].idx = 7;
	orderlist[1].idx = 4;
	orderlist[2].idx = 2;
	orderlist[3].idx = 1;
	orderlist[4].idx = 6;
	orderlist[5].idx = 3;
	orderlist[6].idx = 5;
	orderlist[7].idx = 0;
#endif
	for (int i = 0; i < maxnode + 1; ++i) {
		int idx = orderlist[i].idx;
		construct_label_in(graph, idx, i);
		construct_label_out(reverse_graph, idx, i);
		this->used[idx] = true;
	}
#ifdef test
	printLabel(label_in);
	printLabel(label_out);
#endif
}

void PLL::insert_label(LabelList * label, int idx, int iter, int val)
{
	Label* newLabel = new Label;
	newLabel->idx = iter;
	newLabel->value = val;
	//newLabel->real_idx = orderlist[iter].idx;

	if (label[idx].end != NULL) {
		label[idx].end->next = newLabel;
		label[idx].end = newLabel;
	}
	else {
		label[idx].begin = label[idx].end = newLabel;
	}
}



int PLL::answer_by_label(int out, int in)
{
	Label* p = label_out[out].begin;
	Label* q = label_in[in].begin;
	int min = INF;

	while (p != NULL && q != NULL) {
		if (p->idx > q->idx)q = q->next;
		else if (p->idx < q->idx)p = p->next;
		else {
			if (min > p->value + q->value)min = p->value + q->value;
			p = p->next;
			q = q->next;
		}
	}
	return min;
}

void PLL::printLabel(LabelList* list) {
	for (int i = 0; i < maxnode + 1; ++i) {
		printf("%d: ", i);
		if (list[i].begin != NULL) {
			Label* tmp = list[i].begin;
			while (tmp != NULL) {
				//printf("(%d,%d), ", tmp->real_idx, tmp->value);
				tmp = tmp->next;
			}
		}
		printf("\n");
	}
	printf("\n");
}

void PLL::printGraph(EdgeList* elist) {
	for (int i = 0; i < maxnode + 1; ++i) {
		printf("%d: ", i);
		if (elist[i].begin != NULL) {
			Edge* tmp = elist[i].begin;
			while (tmp != NULL) {
				printf("%d,", tmp->end);
				tmp = tmp->next;
			}
		}
		printf("\n");
	}
}

void PLL::create_query() {
	timespec start, stop, result;
	timespec_get(&start, TIME_UTC);

	int source, target;
	srand(1);

#ifdef bike
        FILE* fin = fopen("../query/bike_input.txt","r");
#endif

#ifdef roadnet
        FILE* fin = fopen("../query/roadnet_input.txt","r");
#endif

#ifdef test
        FILE* fin = fopen("./query/pll_test_input.txt","r");
#endif
        char buffer[1024];
        while(fgets(buffer,1024,fin)){
             sscanf(buffer, "%d,%d",&source, &target);
             //answer_by_label(source, target);
             printf("%d,%d:%d\n", source, target, answer_by_label(source, target));
	}
	timespec_get(&stop, TIME_UTC);
	timespec_diff(&start, &stop, &result);
	printf("%.9fms\n", ((difftime(result.tv_sec, 0) * 1000000000 + result.tv_nsec) / 1000000.0) / 100.0);
}


void PLL::AddEdge(EdgeList * elist, int from, int to, int weight)
{
	Edge* e = new Edge(to, weight);
	if (elist[from].end != NULL) {
		elist[from].end->next = e;
		elist[from].end = e;
	}
	else {
		elist[from].begin = elist[from].end = e;
	}

}

void PLL::deleteGraph(EdgeList *elist) {
	for (int i = 0; i < maxnode + 1; ++i) {
		EdgeList* item = elist + i;
		if (item->begin != NULL) {
			Edge* tmp = item->begin;
			while (tmp != NULL) {
				Edge* e = tmp;
				tmp = tmp->next;
				delete e;
			}
		}
		else {
			delete item->begin;
			delete item->end;
		}
	}
}

void PLL::dropHeader()
{
	char buffer[1024];
	for (int i = 0; i < 4; ++i) {
		fgets(buffer, 1024, fin);
	}
}

PLL::~PLL() {
	if (fin != NULL)fclose(fin);
	deleteGraph(graph);
	deleteGraph(reverse_graph);
	if (visit)delete[] visit;
	if (used)delete[] used;
	if (dist)delete[]dist;
}

void PLL::timespec_diff(timespec* start, timespec* stop, timespec* result) {
	if ((stop->tv_nsec - start->tv_nsec) < 0) {
		result->tv_sec = stop->tv_sec - start->tv_sec - 1;
		result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
	}
	else {
		result->tv_sec = stop->tv_sec - start->tv_sec;
		result->tv_nsec = stop->tv_nsec - start->tv_nsec;
	}
}
