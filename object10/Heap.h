#pragma once
//
// Created by tanrui on 17-11-16.
//

#ifndef CLION_OBJ10_HEAP_H
#define CLION_OBJ10_HEAP_H

#include "Sorts.h"

class Heap {
	friend class Sorts;
public:
	Heap() {};
	Heap(int *elem, int size);
	inline int getSearchCount() { return search_count; }
	inline int getSwapCount() { return swap_count; }
protected:
	int *elems;
	int search_count, swap_count;
	int currentSize;
	void insertHeap(int elem);
	void printHeap();
	void swap(const int start, const int end);
};


#endif //CLION_OBJ10_HEAP_H
