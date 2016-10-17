#pragma once

#define myheap

#ifndef boosttest
class HeapNode {
public:
	int idx, key;
	HeapNode(int _idx, int _key) :idx(_idx), key(_key) {}
	bool operator < (const HeapNode& a) const {
		if (this->idx == a.idx)return this->key > a.key;
		return this->key > a.key;
	}
};
#endif

#ifdef myheap
#define MAXHEAPSIZE 6000000
class HeapNode {
public:
	int idx, key;
	HeapNode() {
		idx = key = 0;
	}
	HeapNode(int idx, int key) {
		this->idx = idx;
		this->key = key;
	}

	HeapNode(const HeapNode& hp) {
		idx = hp.idx; 
		key = hp.key;
	}
};

class Heap {
public:
	Heap(int size) {
		heap = new HeapNode[size];
		hcnt = 0;
	}
	Heap() {
		heap = new HeapNode[MAXHEAPSIZE+1];
		hcnt = 0;
	}

	~Heap() {
		if (heap != NULL)delete[] heap;
	}

	void insert(HeapNode& hp) {
		int idx = ++hcnt;
		
	}

	bool isEmpty() {
		return hcnt > 0;
	}

	HeapNode& getMin() {

	}
private:
	HeapNode* heap;
	int hcnt;
};
#else
class HeapNode {
public:
	int idx, key; 
	HeapNode(int _idx, int _key) :idx(_idx), key(_key) {}
};

struct decreaseOrderHeapNode {
	bool operator() (const HeapNode& a, const HeapNode& b)const {
		return a.key > b.key;
	}
};
#endif