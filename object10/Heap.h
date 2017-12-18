#pragma once
//
// Created by tanrui on 17-11-16.
//

#ifndef CLION_OBJ10_HEAP_H
#define CLION_OBJ10_HEAP_H

#include <iostream>
using namespace std;

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

Heap::Heap(int *elem, int size) {
	currentSize = swap_count = search_count = 0;
	elems = (int *)malloc(sizeof(int)*size);
	for (int i = 0; i < size; i++) {
		insertHeap(elem[i]);
	}
}

void Heap::insertHeap(int elem) {
	elems[currentSize] = elem;
	if (currentSize != 0) {
		int parent = (currentSize - 1) / 2, temp = elems[currentSize], flag = currentSize;
		do {
			if (temp < elems[parent]) {
				elems[flag] = elems[parent];
				elems[parent] = temp;
				flag = (flag - 1) / 2;
				parent = (flag - 1) / 2;
			}
			else {
				break;
			}
		} while (flag != 0);
	}
	currentSize++;
}

void Heap::printHeap() {
	for (int i = 0; i < currentSize; i++) {
		cout << elems[i] << " ";
	}
	cout << endl;
}

void Heap::swap(const int start, const int end) {
	int _size = end - start;
	Heap *temp_heap = new Heap(elems + start, _size);
	for (int i = 0; i < _size; ++i) {
		elems[start + i] = temp_heap->elems[i];
	}
	search_count++;
	swap_count++;
	delete(temp_heap);
}



#endif //CLION_OBJ10_HEAP_H
