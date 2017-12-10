//
// Created by tanrui on 17-11-2.
//

#include <vector>
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
    int num[10] = {123, 15, 105, 172, 1035, 2, 5, 23};
//    int num[10] = {1,8,4,3,7,6,9,2,5,10};
    nums = (int*)malloc(sizeof(int) * 10);
//    nums = (int*)malloc(sizeof(int) * MAXAMOUNT);
//    for (int i = 0; i < MAXAMOUNT; i++) {
    for (int i = 0; i < 10; i++){
//        nums[i] = rand();
        nums[i] = num[i];
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
            cout << "排序完成!\n";
            exit(1);
        }
        default:{
            cout << "输入有误，请重新输入！";
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
    //选择排序基本思想是将序号从i到n的元素序列中的具有最小排序码的元素上调，调至子序列顶端，重复操作直到i=n-1，排序即结束，其时间复杂度为O(n2)
    for (int i = 0; i < MAXAMOUNT; i++) {
        int min = i;
        for (int j = i; j < MAXAMOUNT; j++){
            search_count++;
            if (nums[min] > nums[j]){
                min = j;
            }
        }
        if (min != i){
            //当子序列最小排序码元素不是首元素即需要进行调整交换
            swap_count++;
            int temp = nums[min];
            nums[min] = nums[i];
            nums[i] = temp;
        }
    }
}
void Sorts::InsertSort() {
    InsertSort(1, MAXAMOUNT-1);
}
void Sorts::InsertSort(int left, int right) {
    //插入排序，个人认为与选择排序的算法思想相似，均是每次将子序列长度加1后，进行调整。时间复杂度也为O(n2)
    //而从输出可以看到选择排序查找次数大约为50005000次，而插入排序查找次数大约为25002500次，这是由于插入排序的最内层循环还有个跳出语句，根据数的随机性，其跳出的概率大约是50%
    for (int i = left; i <= right; i++) {
        int j = i-1;
        for (; j >= 0; j--) {
            swap_count++;
            search_count++;
            if (nums[j] <= nums[j+1]){
                break;
            }
            int temp = nums[j];
            nums[j] = nums[j+1];
            nums[j+1] = temp;
        }
    }
}
void Sorts::ShellSort() {
    int flag = MAXAMOUNT, temp, j;
    while (flag!=1){
        flag = (int)(ceil(flag/3) + 1);
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
void Sorts::FastSort() {
    FastSort(0, MAXAMOUNT-1);
}
void Sorts::FastSort(int left, int right) {
    if (left >= right){
        return;
    }
    int flag = left;
    int temp = nums[flag];
    for (int i = left+1; i <= right; ++i) {
        search_count++;
        if (nums[i] < nums[flag]){
            flag++;
            if(flag != i){
                swap_count++;
                int swap = nums[i];
                nums[i] = nums[flag];
                nums[flag] = swap;
            }
        }
    }
    nums[left] = nums[flag];
    nums[flag] = temp;

    FastSort(left, flag);
    FastSort(flag + 1, right);
}
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
void Sorts::MergeSort() {
    MergeSort(0, MAXAMOUNT-1);
}
void Sorts::Merge(int left, int flag, int right) {
    int temp = left, tempFlag = flag;
    int *copyNums = (int*)malloc(sizeof(int) * (right - left + 1));
    for (int i = 0; i < right-temp+1; i++) {
        if ((nums[left] < nums[flag+1] || flag == right)&&(left != tempFlag+1)){
            copyNums[i] = nums[left];
            left++;
        } else{
            copyNums[i] = nums[flag+1];
            flag++;
        }
    }
    for (int j = temp; j <= right; j++) {
        nums[j] = copyNums[j-temp];
    }
    free(copyNums);
}
void Sorts::MergeSort(int left, int right) {
    search_count++;
    if (right == left){
        return;
    } else if (right - left == 1){
        if (nums[left] > nums[right]){
            swap_count++;
            int temp = nums[left];
            nums[left] = nums[right];
            nums[right] = temp;
        }
        return;
    }
    int flag = (right + left)/2;
    MergeSort(left, flag);
    MergeSort(flag+1, right);
    Merge(left, flag, right);
}
void Sorts::RadixSort() {
    int count[10];
    for (int i = 0; i < 10; ++i) {
        count[i] = 0;
    }
    RadixSort(count, 1, 0, MAXAMOUNT-1);
}
void Sorts::RadixSort(int *count, int radix, int left, int right) {
    if (radix == 11){
        return;
    }
    int tempLeft = left;
    for (int i = left; i <= right; ++i) {
        if ((int)(nums[i]/(pow(10, radix))) == 0){
            int temp = nums[tempLeft];
            nums[tempLeft] = nums[i];
            nums[i] = temp;
            tempLeft++;
            count[radix]++;
        }
    }
    InsertSort(left, count[radix]+left);
    RadixSort(count, radix+1, left+count[radix]+1, right);
}