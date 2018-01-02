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




//2.1-1��2 insertion - sort mode 0Ϊ����
template <typename T>
vector<T> insertion_sort( vector<T> &arr, int mode = 0)
{


	int len = arr.size();
	for (int i = 0; i < len; i++)
	{
		int origin_i = i;
		auto temp = arr[i];
		if (mode == 0)//�ǽ���
			while (i > 0 && temp < arr[i - 1])
				i--;
		if (mode == 1)//������
			while (i > 0 && temp > arr[i - 1])
				i--;
		arr.erase(begin(arr) + origin_i);
		arr.insert(begin(arr) + i, temp);
	}
	return arr;
}


//2.1-3 �������⣬������A���ҵ�v�������±ꡣ��������v������-1
template <typename T>
vector<int> find_out(vector<T> A, T v)
{
	int len = A.size();//����A����
	vector<int> result;//���ص��±�i
	for (int i = 0; i < len; i++)
	{
		if (v == A[i])
			result.push_back(i);
	}
	if (result.empty())
	{
		cout << "�����в�����v" << endl;
		return { -1 };
	}
	else
		return result;
}

//2.1-4��������ӣ�������������������ʾ
vector<int> binary_add(vector<int> a, vector<int> b);


//2.3-1��2�鲢����
template <typename T>
vector<T> merge_two(vector<T> vec1, vector<T> vec2)	//�������Ѿ��ź����ʸ���鲢
{
	vector<T> reverse_result;	//��ת�Ľ��
	vector<T> result;	//������������vectorֻ����β�������� ��merge�õ��Ľ��reverse_result��ʵ�Ƿ�ת�� �ٷ�תһ�μ��ɵõ���ȷ�Ľ����
	while (vec1.size() > 0 || vec2.size() > 0)	//û���ڱ��� �ȴ�С�����
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

		else if (vec1.size() == 0)	//vec1�����ڱ��� ��2
		{
			reverse_result.push_back(vec2.back());
			vec2.pop_back();
		}
		else if (vec2.size() == 0)	//vec2�����ڱ��� ��1
		{
			reverse_result.push_back(vec1.back());
			vec1.pop_back();
		}
		else
			cout << "something wrong!!!" << endl;

	}
	//���������ת���ɵõ���ȷ���
	while (reverse_result.size() != 0)
	{
		result.push_back(reverse_result.back());
		reverse_result.pop_back();
	}

	return result;
}
vector<int> merge(vector<int>arr = { 3,41,52,26,38,57,9,4,0 });	//�鲢 ��������һ������

//2.3-5 �������еĶ��ַ�����
vector<int> bisection_find_out(vector<int> A, int v);

//4.1-2 ���������������� ����ֵΪͷβ�����Լ�������Ԫ���ܺͣ������ڶ����������� �ҵ���ҵ��Ǹ���
vector<int> brainless_find_max_subarray(vector<int> arr = { 5,6,-1,2,-5,-9,-5,6,1,2,-2,-3,4 });

//4.1-3 ���������ݹ鷨
vector<int> find_max_crossing_subarray(vector<int> arr, int low, int mid, int high);	//	�ҵ����е�����������
vector<int> find_max_subarray(vector<int> arr, int low, int high);	//�ݹ������������

//4.2 ����˷�
//square matrix multiply
vector<vector<int>> matrix_multiply(vector<vector<int>> A, vector<vector<int>> B);
//����ӷ�
vector<vector<int>> matrix_add(vector<vector<int>> A, vector<vector<int>> B);
//����ķ��γ˷����ֿ�˷�����������Ϊ2^n
vector<vector<int>> square_matrix_multiply_recursive(vector<vector<int>> A, vector<vector<int>> B);


//������ �� 
/*
ֻʵ������������㷨
��С���޷Ǿ����հ���·���ĸ�����С��
����Ū�ˣ��Ժ�����Ҫ�ٲ���
*/
class Heap {
public:
	Heap(const vector<int> &arr);
	//��ȡ��ǰ�ڵ㣨��������Ӧ����Ϣ��������� �ӽڵ㣩
	int get_node_information(int index);
	//�ӽڵ�index��ʼά������
	int max_heapify(int index);
	//��������
	int build_max_heap();
	//������
	int heap_sort();
	//����ȥ�����������ֵ
	int heap_extract_max();
	//��������ĳԪ��
	int heap_increase_key(int index, int key);
	//���Ѳ���Ԫ��
	int max_heap_insert(int key);

	//�ѳߴ�
	int heap_size;
	//��ǰ��������0��ʼ
	int index;
	//��ǰ����������
	int left;
	//��ǰ����������
	int right;
	//��ǰ����������
	int parent;
	//��ǰ����
	int depth;
	//�Ѷ�Ӧ��vector
	vector<int> heap_vector;
};

//�����¿�������
/*
����Ҫ�ǳ�ע�⡰���֡�����ʷǳ�����������
����һ�����飬�����װ����ֲ������Ϊ��һ������Ʋ������
�����ڴ˴� ����Ԫ�ص�����˳�򶼱������� ������ӱ����׷ֽ������� �����Ǽ򵥵Ļ��ֳ�����
����֮��һ����ֵ��Ҳ��һ������Ԫ�أ��˴�ȡ�������һ��Ԫ�أ����뿪��
���� Ӧ�ù����С�������롱֮��ĸ�����
*/
//����ֵΪ��ֵ����λ��
int partition(vector<int> &arr, int p, int r);

//��������
int quick_sort(vector<int> &arr, int p, int r);
//����[a,b]���������
int randint(int a, int b);
//���partition ���ȡ��ֵ�����������һ����
int random_partition(vector<int> &arr, int p, int r);
//������ٷ��� �������partition
int random_quick_sort(vector<int> &arr, int p, int r);

