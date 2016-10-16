#include <stdio.h>
#include "dijkstra.h"
#include <iostream>
#include <memory.h>
#include <time.h>
#include <queue>
#include <stdlib.h>
	
using namespace std;
#define roadnet

#define INF 40000000

Dijkstra::Dijkstra(char* filename, int maxnode) {
	fin = fopen(filename, "r");
	if (fin == NULL) {
		fprintf(stderr, "Error opening file\n");
		exit(-1);
	}
	this->maxnode = maxnode;
	this->graph = new EdgeList[maxnode+1];
	this->visit = new bool[maxnode + 1];
	this->dist = new int[maxnode + 1];
}

Dijkstra::~Dijkstra() {
	if(fin != NULL)fclose(fin);
	for (int i = 0; i < maxnode + 1; ++i) {
		EdgeList* item = graph + i;
		if (item->begin != NULL) {
			Edge* tmp = item->begin; 
			while (tmp != NULL) {
				Edge* deleteEdge = tmp;
				tmp = tmp->next;
				delete deleteEdge;
			}
		}
		else {
			delete item->begin;
			delete item->end;
		}
	}
	if (visit != NULL)delete[] visit;
	if (dist != NULL)delete[] dist;
}

void Dijkstra::construct_index() {
	timespec start, stop, result;
	timespec_get(&start, TIME_UTC);

	char buffer[1024];
#ifdef roadnet
	dropHeader();
#endif
	
	int fromNodeId, toNodeId;
	while (fgets(buffer, 1024, fin)) {
		sscanf(buffer, "%d%d", &fromNodeId, &toNodeId);

#ifndef bike
		Edge* newEdge = new Edge(toNodeId, 1);
		if (graph[fromNodeId].end != NULL){
			graph[fromNodeId].end->next = newEdge;
			graph[fromNodeId].end = newEdge;
		}
		else {
			graph[fromNodeId].begin = graph[fromNodeId].end = newEdge;
		}
#else
		Edge* newEdge = new Edge(toNodeId, 1);
		Edge* newEdgeRev = new Edge(fromNodeId, 1);
		if (graph[fromNodeId].end != NULL) {
			graph[fromNodeId].end->next = newEdge;
			graph[fromNodeId].end = newEdge;
		}
		else {
			graph[fromNodeId].begin = graph[fromNodeId].end = newEdge;
		}

		if (graph[toNodeId].end != NULL) {
			graph[toNodeId].end->next = newEdgeRev;
			graph[toNodeId].end = newEdgeRev;
		}
		else {
			graph[toNodeId].begin = graph[toNodeId].end = newEdgeRev;
		}
#endif
	}
	timespec_get(&stop, TIME_UTC);
	timespec_diff(&start, &stop, &result);
	printf("the construct index time: %.6f milliseconds\n", difftime(result.tv_sec, 0)*1000+result.tv_nsec/1000000.0);
}

void Dijkstra::create_query()
{
	timespec start, stop, result;
	timespec_get(&start, TIME_UTC);
	
	int source, target;
	srand(1);

	for (int i = 0; i < 100; ++i) {
		source = (rand() % (maxnode - 0 + 1)) + 0;
		target = (rand() % (maxnode - 0 + 1)) + 0;
		//answer_query(source, target);
		printf("%d,%d:%d\n", source, target, answer_query(source, target));
	}
	timespec_get(&stop, TIME_UTC);
	timespec_diff(&start, &stop, &result);
	printf("the average query time in 100 queries: %.6f milliseconds\n", (difftime(result.tv_sec, 0) * 1000 + result.tv_nsec / 1000000.0)/100.0);
}

int Dijkstra::answer_query(int s, int t)
{	
	for (int i = 0; i < maxnode + 1; ++i) {
		visit[i] = false;
		dist[i] = INF;
	}
	visit[s] = true;
	dist[s] = 0;
	
	priority_queue<HeapNode> pq;
	HeapNode hnode = HeapNode(s, 0);
	pq.push(hnode);

	while (!pq.empty()) {
		HeapNode top = pq.top();
		pq.pop();
		visit[top.idx] = true;
		if (top.idx == t)break;
		EdgeList elist = this->graph[top.idx];
		for (Edge* e = elist.begin; e != NULL; e = e->next) {
			if (!visit[e->end] && dist[top.idx] + e->weight < dist[e->end]) {
				dist[e->end] = dist[top.idx] + e->weight;
				HeapNode hn = HeapNode(e->end, dist[e->end]);
				pq.push(hn);
			}
		}
	}
	return dist[t];
}


void Dijkstra::dropHeader() {
	char buffer[1024];
	for (int i = 0; i < 4; ++i) {
		fgets(buffer, 1024, fin);
	}
}

void Dijkstra::timespec_diff(timespec* start, timespec* stop, timespec* result) {
	if ((stop->tv_nsec - start->tv_nsec) < 0) {
		result->tv_sec = stop->tv_sec - start->tv_sec - 1;
		result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
	}
	else {
		result->tv_sec = stop->tv_sec - start->tv_sec;
		result->tv_nsec = stop->tv_nsec - start->tv_nsec;
	}
}
