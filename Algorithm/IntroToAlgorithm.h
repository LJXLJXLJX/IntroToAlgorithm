#pragma once
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;



//2.1-1，2 insertion - sort mode 0为升序
vector<int> insertion_sort(vector<int> arr = { 31,26,41,41,59,58 ,0,55,36,55,0 }, int mode = 0);

//2.1-3 查找问题，在数组A中找到v，返回下标。若不存在v，返回-1
vector<int> find_out(vector<int> A, int v);

//2.1-4二进制相加，二进制数都用向量表示
vector<int> binary_add(vector<int> a, vector<int> b);

//2.3-1、2归并排序
vector<int> merge_two(vector<int> vec1, vector<int> vec2);	//将两组已经排好序的矢量归并
vector<int> merge(vector<int>arr = { 3,41,52,26,38,57,9,4,0 });	//归并 依赖于上一个函数

//2.3-5 有序数列的二分法查找
vector<int> bisection_find_out(vector<int> A, int v);

//4.1-2 暴力求解最大子数组 返回值为头尾索引以及子数组元素总和（当存在多个最大子数组 找到最靠右的那个）
vector<int> brainless_find_max_subarray(vector<int> arr = { 5,6,-1,2,-5,-9,-5,6,1,2,-2,-3,4 });

//4.1-3 最大子数组递归法
vector<int> find_max_crossing_subarray(vector<int> arr, int low, int mid, int high);	//	找到跨中点的最大子数列
vector<int> find_max_subarray(vector<int> arr, int low, int high);	//递归求最大子数列

//4.2 矩阵乘法
//square matrix multiply
vector<vector<int>> matrix_multiply(vector<vector<int>> A, vector<vector<int>> B);
//矩阵加法
vector<vector<int>> matrix_add(vector<vector<int>> A, vector<vector<int>> B);
//方阵的分治乘法（分块乘法）阶数必须为2^n
vector<vector<int>> square_matrix_multiply_recursive(vector<vector<int>> A, vector<vector<int>> B);


//第六章 堆
class Heap {
public:
	Heap(const vector<int> &arr);
	//获取当前节点（索引）对应的信息（所处深度 子节点）
	int get_node_information(int index);
	//从节点index开始维护最大堆
	int max_heapify(int index);
	//构建最大堆
	int build_max_heap();

	//堆尺寸
	int heap_size;
	//当前索引，从0开始
	int index;
	//当前索引左索引
	int left;
	//当前索引右索引
	int right;
	//当前层数
	int depth;
	//堆对应的vector
	vector<int> heap_vector;
};

