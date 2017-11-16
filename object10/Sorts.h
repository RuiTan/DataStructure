//
// Created by tanrui on 17-11-2.
//

#ifndef HOMEWORK_SORTS_H
#define HOMEWORK_SORTS_H
#define MAXAMOUNT 10000

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include "Heap.h"

using namespace std;

class Sorts{
public:
    Sorts();
    ~Sorts();
    void getResult(int operate, double _time);
    void SetOperate();
    void BubbleSort();
    void SelectSort();
    void InsertSort();
    void ShellSort();
    void FastSort();
    void HeapSort();
    void MergeSort();
    void RadixSort();

protected:
    int FastSort(const int _left, const int _right);
    int *nums;
    int search_count, swap_count, sort_type;
    ofstream out_file;
};


#endif //HOMEWORK_SORTS_H
