//
// Created by tanrui on 17-11-16.
//

#include <cstdlib>
#include "Heap.h"

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

