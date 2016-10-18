#pragma once

#define myheap

#ifdef stl
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

class MyHeap {
public:
	MyHeap(int size) {
		heap = new HeapNode[size];
		hcnt = 0;
	}
	MyHeap() {
		heap = new HeapNode[MAXHEAPSIZE+1];
		hcnt = 0;
	}

	~MyHeap() {
		if (heap != NULL)delete[] heap;
	}

	void insert(HeapNode hp) {
		int idx = ++hcnt;
		while (idx > 1) {
			if (heap[idx / 2].key > hp.key)heap[idx] = heap[idx / 2];
			else break;
			idx /= 2;
		}
		heap[idx] = hp;
	}

	bool isEmpty() {
		return !(hcnt > 0);
	}

	HeapNode getMin() {
		HeapNode result = heap[1]; 
		HeapNode tmp = heap[--hcnt];

		int i;
		i = 2;
		if (hcnt > 1) {
			while (i < hcnt) {
				if (i + 1 < hcnt && heap[i].key > heap[i + 1].key)i += 1;
				if (heap[i].key < tmp.key)heap[i / 2] = heap[i];
				else break;
				i *= 2;
			}
			heap[i / 2] = tmp;
		}
		return result;
	}

private:
	HeapNode* heap;
	int hcnt;
};
#endif

#ifdef boosttest
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