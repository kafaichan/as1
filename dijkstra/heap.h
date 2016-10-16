#pragma once

class HeapNode {
public:
	int idx, key;
	HeapNode(int _idx, int _key) :idx(_idx), key(_key) {}
	bool operator < (const HeapNode& a) const{
		if (this->idx == a.idx)return this->key > a.key;
		return this->key > a.key;
	}
};