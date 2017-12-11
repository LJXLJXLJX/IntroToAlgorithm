#pragma once
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;



//2.1-1��2 insertion - sort mode 0Ϊ����
vector<int> insertion_sort(vector<int> arr = { 31,26,41,41,59,58 ,0,55,36,55,0 }, int mode = 0);

//2.1-3 �������⣬������A���ҵ�v�������±ꡣ��������v������-1
vector<int> find_out(vector<int> A, int v);

//2.1-4��������ӣ�������������������ʾ
vector<int> binary_add(vector<int> a, vector<int> b);

//2.3-1��2�鲢����
vector<int> merge_two(vector<int> vec1, vector<int> vec2);	//�������Ѿ��ź����ʸ���鲢
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
class Heap {
public:
	Heap(const vector<int> &arr);
	//��ȡ��ǰ�ڵ㣨��������Ӧ����Ϣ��������� �ӽڵ㣩
	int get_node_information(int index);
	//�ӽڵ�index��ʼά������
	int max_heapify(int index);
	//��������
	int build_max_heap();

	//�ѳߴ�
	int heap_size;
	//��ǰ��������0��ʼ
	int index;
	//��ǰ����������
	int left;
	//��ǰ����������
	int right;
	//��ǰ����
	int depth;
	//�Ѷ�Ӧ��vector
	vector<int> heap_vector;
};

