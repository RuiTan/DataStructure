//
// Created by tanrui on 17-11-2.
//

#ifndef HOMEWORK_SORTS_H
#define HOMEWORK_SORTS_H
#define MAXAMOUNT 10000
#define MAXRADIX 10

#include <ctime>
#include <cmath>
#include <vector>
#include <fstream>
#include "Heap.h"
#include <iostream>
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
    void InsertSort(int left, int right);
    void FastSort(int* nums, int left, int right);
    void MergeSort(int left, int right);
    void Merge(int left, int flag, int right);
    void RadixSort(int * count, int radix, int left, int right);
    int *nums;
    int search_count, swap_count, sort_type;
    ofstream out_file;
};


Sorts::Sorts() {
    nums = nullptr;
    swap_count = search_count = 0;
    cout << "**\t\t�����㷨�Ƚ�\t\t\t**\n"
         << "===============================\n"
         << "**\t\t1---ð������\t\t\t**\n"
         << "**\t\t2---ѡ������\t\t\t**\n"
         << "**\t\t3---ֱ�Ӳ�������\t\t**\n"
         << "**\t\t4---ϣ������\t\t\t**\n"
         << "**\t\t5---��������\t\t\t**\n"
         << "**\t\t6---������\t\t\t**\n"
         << "**\t\t7---�鲢����\t\t\t**\n"
         << "**\t\t8---��������\t\t\t**\n"
         << "**\t\t9---�˳�����\t\t\t**\n"
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
            cout << "ð����������ʱ�䣺\t\t" << _time << "��\n";
            cout << "ð��������Ҵ�����\t\t" << search_count << "��\n";
            cout << "ð�����򽻻�������\t\t" << swap_count << "��\n\n";
            break;
        }
        case 2:{
            cout << "ѡ����������ʱ�䣺\t\t" << _time << "��\n";
            cout << "ѡ��������Ҵ�����\t\t" << search_count << "��\n";
            cout << "ѡ�����򽻻�������\t\t" << swap_count << "��\n\n";
            break;
        }
        case 3:{
            cout << "ֱ�Ӳ�����������ʱ�䣺\t" << _time << "��\n";
            cout << "ֱ�Ӳ���������Ҵ�����\t" << search_count << "��\n";
            cout << "ֱ�Ӳ������򽻻�������\t" << swap_count << "��\n\n";
            break;
        }
        case 4:{
            cout << "ϣ����������ʱ�䣺\t\t" << _time << "��\n";
            cout << "ϣ��������Ҵ�����\t\t" << search_count << "��\n";
            cout << "ϣ�����򽻻�������\t\t" << swap_count << "��\n\n";
            break;
        }
        case 5:{
            cout << "������������ʱ�䣺\t\t" << _time << "��\n";
            cout << "����������Ҵ�����\t\t" << search_count << "��\n";
            cout << "�������򽻻�������\t\t" << swap_count << "��\n\n";
            break;
        }
        case 6:{
            cout << "����������ʱ�䣺\t\t" << _time << "��\n";
            cout << "��������Ҵ�����\t\t" << search_count << "��\n";
            cout << "�����򽻻�������\t\t" << swap_count << "��\n\n";
            break;
        }
        case 7:{
            cout << "�鲢��������ʱ�䣺\t\t" << _time << "��\n";
            cout << "�鲢������Ҵ�����\t\t" << search_count << "��\n";
            cout << "�鲢���򽻻�������\t\t" << swap_count << "��\n\n";
            break;
        }
        case 8:{
            cout << "������������ʱ�䣺\t\t" << _time << "��\n";
            cout << "����������Ҵ�����\t\t" << search_count << "��\n";
            cout << "�������򽻻�������\t\t" << swap_count << "��\n\n";
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
    cout << "��ѡ����Ҫ���е������㷨��";
    cin >> sort_type;
    clock_t _start= clock();
    //��ʱ��ʼ
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
            cout << "�������!\n";
            exit(1);
        }
        default:{
            cout << "�����������������룡";
            break;
        }
    }
    clock_t _finish = clock();
    //��ʱ����
    getResult(sort_type, (double)(_finish-_start)/CLOCKS_PER_SEC);
    for (int j = 0; j < MAXAMOUNT; ++j) {
        out_file << nums[j] << " ";
    }
    out_file << endl << endl;
    delete(nums);
    SetOperate();
}
void Sorts::BubbleSort() {
    //  ð���������˵���뷨��򵥵������ˣ����ظ��ı������У�ÿ�α�������ÿ����Ԫ�ؽ��бȽϣ��ϴ�Ľ�
    //���ƣ�һ�α�������������Ԫ�ظ������ж��ˣ���ʱ�临�Ӷ�ΪO(n2)
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
    //  ѡ���������˼���ǽ���Ŵ�i��n��Ԫ�������еľ�����С�������Ԫ���ϵ���������������λ���ظ�����
    //ֱ��i=n-1�����򼴽�������ʱ�临�Ӷ�ΪO(n2)
    for (int i = 0; i < MAXAMOUNT; i++) {
        int min = i;
        for (int j = i; j < MAXAMOUNT; j++){
            search_count++;
            if (nums[min] > nums[j]){
                min = j;
            }
        }
        if (min != i){
            //����������С������Ԫ�ز�����Ԫ�ؼ���Ҫ���е�������
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
    //  �������򣬸�����Ϊ��ѡ��������㷨˼�����ƣ�����ÿ�ν������г��ȼ�1�󣬽��е�����ʱ�临�Ӷ�ҲΪO(n2)
    //����˼���ǵ�i�β���Ԫ��ʱ������i-1��Ԫ���Ѿ����ź�����ˣ���������˵�����룬���Ӵ�С������ʱ�����
    //�뵽��Ӧ���ڵ�λ�ã���˷���n�����о��Ѿ��ź�����
    //  ��������Կ���ѡ��������Ҵ�����ԼΪ50005000�Σ�������������Ҵ�����ԼΪ25002500�Σ��������ڲ���
    //��������ڲ�ѭ�����и�������䣬������������ԣ��������ĸ��ʴ�Լ��50%
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
    //  ��������Ļ���˼���Ƕ����н��зֲ㣬�����е�һ��Ԫ��Ϊ��׼������������Ԫ�غ��ƣ�������С��
    //ǰ�ƣ���ʱ�û�׼Ԫ�ص�λ���Ѿ��ǹ̶������ˣ��ٶ��������������еݹ�ǰ��Ĳ��������ռ��ɵõ���
    //�����������
    if (left >= right){
        return;
    }
    int temp = nums[left];
    int flag = left;
    for (int i = left; i <= right; i++){
        search_count++;
        if (nums[i] < temp){
            //���������Ȼ�׼Ԫ��С������������׼Ԫ��ǰ�����Ȼ�׼Ԫ�ش�����Ҫ�ƶ�
            swap_count++;
            if (flag == i - 1){
                //��Ԫ�����׼Ԫ������ʱ��ֱ�ӵ�������λ��
                nums[flag++] = nums[i];
                nums[i] = temp;
            }
            else{
                //��Ԫ�����׼Ԫ�ز�����ʱ���򽫸�Ԫ�����׼Ԫ�غ�һλ����λ�ã������ٵ�����Ԫ�����׼Ԫ��
                int temp2 = nums[i];
                nums[i] = nums[flag + 1];
                nums[flag + 1] = temp;
                nums[flag++] = temp2;
            }
        }
    }
    //���������������еݹ����FastSort����
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
    //  �鲢����Ļ���˼��ʱ�����в������У���ĳһ��������Ϊ��1��Ԫ�ء�+��2��Ԫ�ء����ߡ�2��Ԫ�ء�+��1��Ԫ�ء���
    //�ߡ�2��Ԫ�ء�+��2��Ԫ�ء�ʱΪ�ݹ������������ʱ��2��Ԫ�صĽ�������1��Ԫ�ص��޲������������Merge����
    //�������������й鲢��������˷����ݹ������յõ���������
    search_count++;
    if (right == left){
        //1��Ԫ�ص�������ֱ�ӷ��ز���Ҫ����
        return;
    } else if (right - left == 1){
        //2��Ԫ�ص���������������ֱ�ӷ��أ����򽻻��󷵻�
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
    //�ָ��������������ͨ����������鲢��һ��
}
void Sorts::Merge(int left, int flag, int right) {
    //  �鲢�����ǹ鲢�����㷨�е���Ҫ���֣�����Ҫ˼����ǽ�����������������У�����ѡ���С��Ԫ�ط����¿���
    //��������ȥ��ֱ��ĳһ�����е���ĩβλ�ã���ʱ����һ������ʣ���Ԫ��ֱ�ӷ��������У���󽫸����鸳ֵ��ԭ
    //���顣���ɵõ��������й鲢�������
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
    //  �����������Ҫ˼���������ɸ���������������Ϊ���ɸ��ࣨ������˵�����ǽ���ͬ���Ԫ�طŵ�ͬһ��Ͱ�У���
    //�����ÿ��Ԫ�ؽ�������
    //  �������ѡ�õ���Ԫ�ص�λ��������rand()��������������������Χ��0-RAND_MAX֮�䣬��RAND_MAX�����
    //ֵΪ2147483647����Ϊstdlib.h�к궨���һ���ַ�����������������Ҷ����MAXRADIXΪ10
    //  ��������ÿ�εݹ���Ȼ�Ƕ����зֲ㣬���󽫷ֺò��������������ʹ�ò��������㷨�����������м����ݹ�ֲ㣬ֱ��radix
    //ȡ��MAXRADIX����ʱ��ʣ�µ�����ֱ�����ò��������㷨����
    if (radix == MAXRADIX){
        InsertSort(left, right);
        return;
    }
    int tempLeft = left;
    for (int i = left; i <= right; ++i) {
        if ((int)(nums[i]/(pow(10, radix))) == 0){
            //10��radix�η�Ϊÿ�ηֲ�����ݣ��ҵ�����С�ڴ�ֵ��Ԫ�أ������ƶ������е����
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