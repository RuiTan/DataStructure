//
// Created by tanrui on 17-11-2.
//

#include "Sorts.h"

Sorts::Sorts() {
    nums = nullptr;
    swap_count = search_count = 0;
    cout << "**\t\t排序算法比较\t\t\t**\n"
         << "===============================\n"
         << "**\t\t1---冒泡排序\t\t\t**\n"
         << "**\t\t2---选择排序\t\t\t**\n"
         << "**\t\t3---直接插入排序\t\t**\n"
         << "**\t\t4---希尔排序\t\t\t**\n"
         << "**\t\t5---快速排序\t\t\t**\n"
         << "**\t\t6---堆排序\t\t\t**\n"
         << "**\t\t7---归并排序\t\t\t**\n"
         << "**\t\t8---基数排序\t\t\t**\n"
         << "**\t\t9---退出程序\t\t\t**\n"
         << "===============================\n\n";
    out_file.open("out_file.txt", ios::ate);
    SetOperate();
}
Sorts::~Sorts() {
    delete(nums);
    out_file.close();
    nums = nullptr;
    swap_count = search_count = 0;
}
void Sorts::getResult(int operate, double _time) {
    switch (operate){
        case 1:{
            cout << "冒泡排序所用时间：\t\t" << _time << "秒\n";
            cout << "冒泡排序查找次数：\t\t" << search_count << "次\n";
            cout << "冒泡排序交换次数：\t\t" << swap_count << "次\n\n";
            break;
        }
        case 2:{
            cout << "选择排序所用时间：\t\t" << _time << "秒\n";
            cout << "选择排序查找次数：\t\t" << search_count << "次\n";
            cout << "选择排序交换次数：\t\t" << swap_count << "次\n\n";
            break;
        }
        case 3:{
            cout << "直接插入排序所用时间：\t" << _time << "秒\n";
            cout << "直接插入排序查找次数：\t" << search_count << "次\n";
            cout << "直接插入排序交换次数：\t" << swap_count << "次\n\n";
            break;
        }
        case 4:{
            cout << "希尔排序所用时间：\t\t" << _time << "秒\n";
            cout << "希尔排序查找次数：\t\t" << search_count << "次\n";
            cout << "希尔排序交换次数：\t\t" << swap_count << "次\n\n";
            break;
        }
        case 5:{
            cout << "快速排序所用时间：\t\t" << _time << "秒\n";
            cout << "快速排序查找次数：\t\t" << search_count << "次\n";
            cout << "快速排序交换次数：\t\t" << swap_count << "次\n\n";
            break;
        }
        case 6:{
            cout << "堆排序所用时间：\t\t" << _time << "秒\n";
            cout << "堆排序查找次数：\t\t" << search_count << "次\n";
            cout << "堆排序交换次数：\t\t" << swap_count << "次\n\n";
            break;
        }
        case 7:{
            cout << "归并排序所用时间：\t\t" << _time << "秒\n";
            cout << "归并排序查找次数：\t\t" << search_count << "次\n";
            cout << "归并排序交换次数：\t\t" << swap_count << "次\n\n";
            break;
        }
        case 8:{
            cout << "基数排序所用时间：\t\t" << _time << "秒\n";
            cout << "技术排序查找次数：\t\t" << search_count << "次\n";
            cout << "技术排序交换次数：\t\t" << swap_count << "次\n\n";
            break;
        }
        default: {
            break;
        }
    }
}
void Sorts::SetOperate() {
//    int num[10] = {1,8,4,3,7,6,9,2,5,10};
//    nums = (int*)malloc(sizeof(int) * 10);
    nums = (int*)malloc(sizeof(int) * MAXAMOUNT);
    for (int i = 0; i < MAXAMOUNT; i++) {
//    for (int i = 0; i < 10; i++){
        nums[i] = rand();
//        nums[i] = num[i];
    }
    swap_count = search_count = 0;
    cout << "请选择你要进行的排序算法：";
    cin >> sort_type;
    clock_t _start= clock();
    switch (sort_type){
        case 1:{
            BubbleSort();
            break;
        }
        case 2:{
            SelectSort();
            break;
        }
        case 3:{
            InsertSort();
            break;
        }
        case 4:{
            ShellSort();
            break;
        }
        case 5:{
            FastSort();
            break;
        }
        case 6:{
            HeapSort();
            break;
        }
        case 7:{
            MergeSort();
            break;
        }
        case 8:{
            RadixSort();
            break;
        }
        case 9:{
            cout << "sort finished!\n";
            exit(1);
        }
        default:{
            cout << "Bad operation, please input again!\n";
            break;
        }
    }
    clock_t _finish = clock();
    getResult(sort_type, (double)(_finish-_start)/CLOCKS_PER_SEC);
    for (int j = 0; j < MAXAMOUNT; ++j) {
        out_file << nums[j] << " ";
    }
    out_file << endl << endl;
    delete(nums);
    SetOperate();
}
void Sorts::BubbleSort() {
    for (int i = 0; i < MAXAMOUNT - 1; i++) {
        for (int j = 0; j < MAXAMOUNT - i - 1; j++) {
            search_count++;
            if (nums[j]>nums[j+1]){
                swap_count++;
                int temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
            }
        }
    }
}
void Sorts::SelectSort() {

}
int Sorts::FastSort(const int _left, const int _right) {
    if (_right - _left == 1){
        if (nums[_right] < nums[_left]) {
            int temp = nums[_right];
            nums[_right] = nums[_left];
            nums[_left] = temp;
        }
        return -1;
    }
    int flag = nums[_left];
    for (int i = 1; i < _right; ++i) {

    }
}

void Sorts::InsertSort() {
    for (int i = 1; i < MAXAMOUNT; i++) {
        int j = i-1, flag = nums[i];
        while (nums[j] > flag && j>=0){
            swap_count++;
            search_count++;
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = flag;
    }
}
void Sorts::ShellSort() {
    int flag = MAXAMOUNT, temp, j;
    while (flag!=1){
        flag = ceil(flag/3) + 1;//get int below
        for (int i = flag; i<MAXAMOUNT; i++){
            search_count++;
            if (nums[i]<nums[i-flag]){
                swap_count++;
                temp = nums[i], j = i-flag;
                while (j >= 0 && temp < nums[j]){
                    nums[j+flag] = nums[j];
                    j-=flag;
                }
                nums[j+flag] = temp;
            }
        }
    }
}
void Sorts::FastSort() {}
void Sorts::HeapSort() {
    Heap heap(nums, MAXAMOUNT);
//    Heap heap(nums, 10);
    for (int i = 1; i < heap.currentSize; ++i) {
        heap.swap(i, heap.currentSize);
    }
//    heap.printHeap();
    search_count = heap.getSearchCount();
    swap_count = heap.getSwapCount();
    for (int i = 0; i < heap.currentSize; ++i) {
        nums[i] = heap.elems[i];
    }
}
void Sorts::MergeSort() {}
void Sorts::RadixSort() {}