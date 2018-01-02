#pragma once
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <limits>
#include <random>

#ifndef INTROTOALGORITHM_H
#define INTROTOALGORITHM_H
#endif

using namespace std;




//2.1-1，2 insertion - sort mode 0为升序
template <typename T>
vector<T> insertion_sort( vector<T> &arr, int mode = 0)
{


	int len = arr.size();
	for (int i = 0; i < len; i++)
	{
		int origin_i = i;
		auto temp = arr[i];
		if (mode == 0)//非降序
			while (i > 0 && temp < arr[i - 1])
				i--;
		if (mode == 1)//非升序
			while (i > 0 && temp > arr[i - 1])
				i--;
		arr.erase(begin(arr) + origin_i);
		arr.insert(begin(arr) + i, temp);
	}
	return arr;
}


//2.1-3 查找问题，在数组A中找到v，返回下标。若不存在v，返回-1
template <typename T>
vector<int> find_out(vector<T> A, T v)
{
	int len = A.size();//容器A长度
	vector<int> result;//返回的下标i
	for (int i = 0; i < len; i++)
	{
		if (v == A[i])
			result.push_back(i);
	}
	if (result.empty())
	{
		cout << "序列中不存在v" << endl;
		return { -1 };
	}
	else
		return result;
}

//2.1-4二进制相加，二进制数都用向量表示
vector<int> binary_add(vector<int> a, vector<int> b);


//2.3-1、2归并排序
template <typename T>
vector<T> merge_two(vector<T> vec1, vector<T> vec2)	//将两组已经排好序的矢量归并
{
	vector<T> reverse_result;	//反转的结果
	vector<T> result;	//输出结果（由于vector只能在尾端做操作 该merge得到的结果reverse_result其实是反转的 再反转一次即可得到正确的结果）
	while (vec1.size() > 0 || vec2.size() > 0)	//没到哨兵牌 比大小后插入
	{
		if (vec1.size() > 0 && vec2.size() > 0)
		{
			if (vec1.back() > vec2.back())
			{
				reverse_result.push_back(vec1.back());
				vec1.pop_back();
			}
			else
			{
				reverse_result.push_back(vec2.back());
				vec2.pop_back();
			}
		}

		else if (vec1.size() == 0)	//vec1到了哨兵牌 插2
		{
			reverse_result.push_back(vec2.back());
			vec2.pop_back();
		}
		else if (vec2.size() == 0)	//vec2到了哨兵牌 插1
		{
			reverse_result.push_back(vec1.back());
			vec1.pop_back();
		}
		else
			cout << "something wrong!!!" << endl;

	}
	//最后做个反转即可得到正确结果
	while (reverse_result.size() != 0)
	{
		result.push_back(reverse_result.back());
		reverse_result.pop_back();
	}

	return result;
}
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
/*
只实现了最大堆相关算法
最小堆无非就是照搬套路，改个大于小于
懒得弄了，以后有需要再补上
*/
class Heap {
public:
	Heap(const vector<int> &arr);
	//获取当前节点（索引）对应的信息（所处深度 子节点）
	int get_node_information(int index);
	//从节点index开始维护最大堆
	int max_heapify(int index);
	//构建最大堆
	int build_max_heap();
	//堆排序
	int heap_sort();
	//最大堆去掉并返回最大值
	int heap_extract_max();
	//增大最大堆某元素
	int heap_increase_key(int index, int key);
	//最大堆插入元素
	int max_heap_insert(int key);

	//堆尺寸
	int heap_size;
	//当前索引，从0开始
	int index;
	//当前索引左索引
	int left;
	//当前索引右索引
	int right;
	//当前索引父索引
	int parent;
	//当前层数
	int depth;
	//堆对应的vector
	vector<int> heap_vector;
};

//第七章快速排序
/*
这里要非常注意“划分”这个词非常容易引起误导
划分一个数组，很容易把这种操作理解为把一根棍子撇成两半
但是在此处 数组元素的整个顺序都被打乱了 这根棍子被彻底分解重组了 而不是简单的划分成两半
打乱之后按一个阈值（也是一个数组元素，此处取的是最后一个元素）隔离开来
所以 应该管他叫“重组隔离”之类的更合理
*/
//返回值为阈值的新位置
int partition(vector<int> &arr, int p, int r);

//快速排序
int quick_sort(vector<int> &arr, int p, int r);
//生成[a,b]的随机整数
int randint(int a, int b);
//随机partition 随机取阈值，而不是最后一个了
int random_partition(vector<int> &arr, int p, int r);
//随机快速分类 基于随机partition
int random_quick_sort(vector<int> &arr, int p, int r);

