#pragma once

#define stl 

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

#ifdef boosttest
class HeapNode {
public:
	int idx, key; 
	HeapNode(int _idx, int _key) :idx(_idx), key(_key) {}
};

struct decreaseHeapNode {
	bool operator()(const HeapNode& a, const HeapNode& b)const {
		return a.key > b.key;
	}
};
#endif
