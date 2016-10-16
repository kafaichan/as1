#pragma once

#include <stdio.h>
class Label {
public:
	int idx, value;
	//int real_idx;
	Label* next;
	Label() {
		idx = value = 0;
		//real_idx = -1;
		next = NULL;
	}
};

class LabelList {
public:
	Label* begin;
	Label* end;
	LabelList() {
		begin = end = NULL;
	}
};

class Order {
public:
	int idx, degree;
	bool operator< (const Order &a) const {
		return this->degree > a.degree;
	}
	Order() {
		degree = 0;
	}
};
