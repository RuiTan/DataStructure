//
// Created by tanrui on 17-11-2.
//

#ifndef HOMEWORK_SORTS_H
#define HOMEWORK_SORTS_H
#define MAXRADIX 10

#include <ctime>
#include <cmath>
#include <vector>
#include <fstream>
#include "Heap.h"
#include <iostream>
using namespace std;

static int MAXAMOUNT;

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
    void InsertSort(int left, int right);
    void FastSort(int* nums, int left, int right);
    void MergeSort(int left, int right);
    void Merge(int left, int flag, int right);
    void RadixSort(int * count, int radix, int left, int right);
    int *nums;
    int search_count, swap_count, sort_type;
    ofstream out_file;
    bool ifPrint;
};


Sorts::Sorts() {
    nums = nullptr;
    swap_count = search_count = 0;
    cout << "**\t\t排序算法比较\t\t\t**\n"
         << "=================================================\n"
         << "**\t\t1---冒泡排序\t\t\t**\n"
         << "**\t\t2---选择排序\t\t\t**\n"
         << "**\t\t3---直接插入排序\t\t**\n"
         << "**\t\t4---希尔排序\t\t\t**\n"
         << "**\t\t5---快速排序\t\t\t**\n"
         << "**\t\t6---堆排序\t\t\t**\n"
         << "**\t\t7---归并排序\t\t\t**\n"
         << "**\t\t8---基数排序\t\t\t**\n"
         << "**\t\t9---退出程序\t\t\t**\n"
         << "=================================================\n\n";
    out_file.open("out_file.txt", ios::ate);
    cout << "排序时是否需要将结果输出至文件(y-是)？";
    char flag;
    cin >> flag;
    cout << "请输入要排序的数据数量：";
    cin >> MAXAMOUNT;
    while (MAXAMOUNT <= 0){
        cout << "输入的数量有误，应该为正整数，请重新输入：";
    }
    ifPrint = (flag=='y');
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
            cout << "直接插入排序所用时间：\t\t" << _time << "秒\n";
            cout << "直接插入排序查找次数：\t\t" << search_count << "次\n";
            cout << "直接插入排序交换次数：\t\t" << swap_count << "次\n\n";
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
            cout << "基数排序查找次数：\t\t" << search_count << "次\n";
            cout << "基数排序交换次数：\t\t" << swap_count << "次\n\n";
            break;
        }
        default: {
            break;
        }
    }
}
void Sorts::SetOperate() {
//    int num[20] = {
//            123, 15, 105, 172, 1035, 2, 5, 23, 3124, 55, 1, 22345, 115, 234, 564448, 12331, 12, 156, 236, 88
//    };
    nums = (int*)malloc(sizeof(int) * MAXAMOUNT);
    for (int i = 0; i < MAXAMOUNT; i++) {
        nums[i] = (int)rand();
//        nums[i] = num[i];
    }
    swap_count = search_count = 0;
    cout << "请选择你要进行的排序算法：";
    cin >> sort_type;
    clock_t _start= clock();
    //计时开始
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
    //计时结束
    getResult(sort_type, (double)(_finish-_start)/CLOCKS_PER_SEC);
    if (ifPrint){
        for (int j = 0; j < MAXAMOUNT; ++j) {
            out_file << nums[j] << " ";
        }
        out_file << endl << endl;
    }
    delete(nums);
    SetOperate();
}
void Sorts::BubbleSort() {
    //  冒泡排序可以说是想法最简单的排序了，它重复的遍历序列，每次遍历将对每两个元素进行比较，较大的将
    //后移，一次遍历下来，最大的元素浮到序列顶端，其时间复杂度为O(n2)
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
    //  选择排序基本思想是将序号从i到n的元素序列中的具有最小排序码的元素上调，调至子序列首位，重复操作
    //直到i=n-1，排序即结束，其时间复杂度为O(n2)
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
    //  插入排序，个人认为与选择排序的算法思想相似，均是每次将子序列长度加1后，进行调整。时间复杂度也为O(n2)
    //基本思想是第i次插入元素时，后面i-1个元素已经是排好序的了（这里采用了倒序插入，即从大到小），此时将其插
    //入到其应该在的位置，如此反复n次序列就已经排好序了
    //  从输出可以看到选择排序查找次数大约为50005000次，而插入排序查找次数大约为25002500次，这是由于插入
    //排序的最内层循环还有个跳出语句，根据数的随机性，其跳出的概率大约是50%
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
    FastSort(nums, 0, MAXAMOUNT-1);
}
void Sorts::FastSort(int *nums, int left, int right) {
    //  快速排序的基本思想是对序列进行分层，以序列第一个元素为基准，将排序码大的元素后移，排序码小的
    //前移，此时该基准元素的位置已经是固定下来了，再对左右两个子序列递归前面的操作，最终即可得到排
    //好序的序列了
    if (left >= right){
        return;
    }
    int temp = nums[left];
    int flag = left;
    for (int i = left; i <= right; i++){
        search_count++;
        if (nums[i] < temp){
            //如果排序码比基准元素小，则将其移至基准元素前，若比基准元素大，则不需要移动
            swap_count++;
            if (flag == i - 1){
                //该元素与基准元素相邻时，直接调换二者位置
                nums[flag++] = nums[i];
                nums[i] = temp;
            }
            else{
                //该元素与基准元素不相邻时，则将该元素与基准元素后一位调换位置，而后再调换该元素与基准元素
                int temp2 = nums[i];
                nums[i] = nums[flag + 1];
                nums[flag + 1] = temp;
                nums[flag++] = temp2;
            }
        }
    }
    //对左右两个子序列递归调用FastSort操作
    FastSort(nums, left, flag-1);
    FastSort(nums, flag + 1, right);
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
void Sorts::MergeSort(int left, int right) {
    //  归并排序的基本思想时将序列不断折中，当某一序列折中为“1个元素”+“2个元素”或者“2个元素”+“1个元素”或
    //者“2个元素”+“2个元素”时为递归结束条件，此时对2个元素的进行排序，1个元素的无操作，而后调用Merge函数
    //将这两个子序列归并起来，如此反复递归便可最终得到有序序列
    search_count++;
    if (right == left){
        //1个元素的子序列直接返回不需要操作
        return;
    } else if (right - left == 1){
        //2个元素的子序列若有序则直接返回，否则交换后返回
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
    //分割出的两个子序列通过这个函数归并到一起
}
void Sorts::Merge(int left, int flag, int right) {
    //  归并函数是归并排序算法中的主要部分，其主要思想就是将逐个遍历两个子序列，依次选择较小的元素放入新开辟
    //的数组中去，直到某一子序列到了末尾位置，此时将另一个序列剩余的元素直接放入序列中，最后将该数组赋值回原
    //数组。即可得到两子序列归并后的序列
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
void Sorts::RadixSort() {
    int count[MAXAMOUNT];
    for (int i = 0; i < MAXAMOUNT; ++i) {
        count[i] = 0;
    }
    RadixSort(count, 1, 0, MAXAMOUNT-1);
}
void Sorts::RadixSort(int *count, int radix, int left, int right) {
    //  基数排序的主要思想是用若干个基数将序列区分为若干个类（形象来说，就是将相同类的元素放到同一个桶中），
    //而后对每类元素进行排序
    //  这里基数选用的是元素的位数，由于rand()随机函数产生的随机数范围在0-RAND_MAX之间，而RAND_MAX的最大
    //值为2147483647（此为stdlib.h中宏定义的一个字符常量），因此这里我定义的MAXRADIX为10
    //  基数排序每次递归仍然是对序列分层，而后将分好层的序列左子序列使用插入排序算法排序，右子序列继续递归分层，直到radix
    //取到MAXRADIX，此时对剩下的序列直接利用插入排序算法排序
    if (radix == MAXRADIX){
        InsertSort(left, right);
        return;
    }
    int tempLeft = left;
    for (int i = left; i <= right; ++i) {
        if ((int)(nums[i]/(pow(10, radix))) == 0){
            //10的radix次方为每次分层的依据，找到所有小于此值的元素，将其移动到序列的左边
            if (tempLeft != i){
                int temp = nums[tempLeft];
                nums[tempLeft] = nums[i];
                nums[i] = temp;
            }
            tempLeft++;
            count[radix]++;
        }
    }
    InsertSort(left, count[radix]+left-1);
    RadixSort(count, radix+1, left+count[radix], right);
}

#endif //HOMEWORK_SORTS_H